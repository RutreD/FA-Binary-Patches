#include "include/ImVector.h"
#include "include/magic_classes.h"
#include "include/moho.h"
#include <d3dx9.h>

const char *WINAPI DXGetErrorString(HRESULT hr) asm("0xB50FD8");
namespace Effects {
    LPDIRECT3DDEVICE9 device;
    uintptr_t *vtbl;

    ImVector<pair<char[20], LPD3DXEFFECT>> effectPool; //{.effectName, .pEffect}
    ImVector<LPDIRECT3DBASETEXTURE9> texturePool;
    ImVector<D3DXHANDLE> overwrittenTextureHandles;

    HRESULT WINAPI SetTextureHooked(LPD3DXEFFECT pEffect, D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
    decltype(&SetTextureHooked) originalSetTexture;

    HRESULT WINAPI SetTextureHooked(LPD3DXEFFECT pEffect, D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture) {
        if (overwrittenTextureHandles.contains(hParameter))
            return D3D_OK;
        return originalSetTexture(pEffect, hParameter, pTexture);
    }

    void Reset() {
        if (vtbl[52] == reinterpret_cast<uintptr_t>(SetTextureHooked)) // uninstall hook
            vtbl[52] = reinterpret_cast<uintptr_t>(originalSetTexture);
        overwrittenTextureHandles.clear();
        for (const auto &texture : texturePool)
            texture->Release();
        texturePool.clear();
    }
} // namespace Effects

void RegisterLuaFunctions(lua_State *L);
void __thiscall OnStart(uintptr_t this_) {
    Effects::Reset();

    RegisterLuaFunctions(g_Sim->LState->m_state);
    RegisterLuaFunctions(g_CWldSession->LState->m_state);

    reinterpret_cast<void(__thiscall *)(uintptr_t)>(0x86A6D0)(this_);
}

void __thiscall OnEffectD3D9Contruct(uintptr_t this_, uintptr_t effectContext, LPD3DXEFFECT pEffect) {
    reinterpret_cast<decltype(&OnEffectD3D9Contruct)>(0x942E50)(this_, effectContext, pEffect);

    string *effectPath = reinterpret_cast<string *>(effectContext + 0xC);
    auto getName = [](const char *begin, const char *end) {
        string effectName;
        for (const char *dotPos; begin != end; end--) {
            if (*end == '.')
                dotPos = end;
            else if (*end == '\\') {
                AssignString(&effectName, end + 1, dotPos - end - 1);
                break;
            }
        }
        return effectName;
    };
    string effectName = getName(effectPath->data(), effectPath->data() + effectPath->strLen);

    if (Effects::effectPool.empty()) {
        pEffect->GetDevice(&Effects::device);
        Effects::vtbl = *reinterpret_cast<uintptr_t **>(pEffect);
        Effects::originalSetTexture = reinterpret_cast<decltype(Effects::originalSetTexture)>(Effects::vtbl[52]);
        DWORD oldProt;
        VirtualProtect(Effects::vtbl, 4 * 78, PAGE_READWRITE, &oldProt);
        // Effects::vtbl[52] = reinterpret_cast<uintptr_t>(Effects::SetTextureHooked);
    }

    decltype(Effects::effectPool)::value_type pairNameEffect;
    size_t len = effectName.strLen > sizeof(pairNameEffect.first) ? sizeof(pairNameEffect.first) : effectName.strLen;
    memset(pairNameEffect.first, '\0', sizeof(pairNameEffect.first));
    memcpy(pairNameEffect.first, effectName.data(), len);
    pairNameEffect.second = pEffect;
    Effects::effectPool.push_back(pairNameEffect);
}

/////////////////////// LUA ///////////////////////

void *getLightCObject(lua_State *L, int n) {
    if (!lua_istable(L, n))
        return nullptr;
    lua_pushvalue(L, n);
    lua_pushstring(L, s_c_object);
    lua_rawget(L, -2);
    void *res = lua_islightuserdata(L, -1) ? lua_tolightuserdata(L, -1) : nullptr;
    lua_pop(L, 1);
    return res;
}

int ResetEffects(lua_State *L) {
    // EffectController.ResetEffects()
    Effects::Reset();
    return 0;
}

int CreateTextureFromFile(lua_State *L) {
    // EffectController.CreateTextureFromFile("/maps/map/texture.dds")
    if (lua_gettop(L) != 1)
        L->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 1, lua_gettop(L));
    auto fileTexturePath = lua_tostring(L, 1);
    auto path = CVirtualFileSystem::getInstance()->getAbsolutePath(fileTexturePath);
    if (path.strLen == 0)
        L->LuaState->Error("Cannot load texture `%s', doesnt exists", fileTexturePath);

    struct MemBuffer_char {
        void *raw_buf;
        uintptr_t vtable; // 00E03828	4		boost::detail::sp_counted_impl_pd<void *,void (__cdecl*)(void *)>	boost::detail::sp_counted_impl_pd<void *,void (__cdecl*)(void *)>: boost::detail::sp_counted_base;
        char *begin;      // = raw_buf
        char *end;

        size_t size() {
            return begin - end;
        }
        // ~MemBuffer_char() {
        //     free(raw_buf);
        // }
    } membuffer;

    auto readFileToMemBuffer = [](void *membuffer, const char *path) {
        reinterpret_cast<void(__stdcall *)(int self, void *membufer, const char *path)>(0x4596C0)(*reinterpret_cast<uintptr_t *>(0x10A6374), membuffer, path);
    };
    readFileToMemBuffer(&membuffer, path.data());

    LPDIRECT3DTEXTURE9 texture;
    auto res = D3DXCreateTextureFromFileInMemoryEx(Effects::device, membuffer.begin, membuffer.size(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);
    if (res != D3D_OK)
        L->LuaState->Error("Code error: %d | %s", res, DXGetErrorString(res));
    Effects::texturePool.push_back(texture);
    lua_pushlightuserdata(L, static_cast<void *>(texture));
    return 1;
}

int SaveTextureToFile(lua_State *L) {
    // EffectController.terrain:SaveTextureToFile('albedo.dds', 'DecalAlbedoTexture')
    if (lua_gettop(L) != 3)
        L->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 3, lua_gettop(L));

    auto effect = static_cast<LPD3DXEFFECT>(getLightCObject(L, 1));
    if (effect == nullptr)
        L->LuaState->Error("%s", s_ExpectedAGameObject);
    auto destFile = lua_tostring(L, 2);
    auto textureName = lua_tostring(L, 3);

    D3DXIMAGE_FILEFORMAT destFormat = D3DXIFF_DDS;
    const char *destFileFormat = destFile + strlen(destFile) - 4;
    if (strcmp(destFileFormat, ".bmp") == 0)
        destFormat = D3DXIFF_BMP;
    else if (strcmp(destFileFormat, ".jpg") == 0)
        destFormat = D3DXIFF_JPG;
    else if (strcmp(destFileFormat, ".png") == 0)
        destFormat = D3DXIFF_PNG;
    else if (strcmp(destFileFormat, ".dds") == 0)
        destFormat = D3DXIFF_DDS;
    else if (strcmp(destFileFormat, ".dib") == 0)
        destFormat = D3DXIFF_DIB;
    else if (strcmp(destFileFormat, ".hdr") == 0)
        destFormat = D3DXIFF_HDR;
    else if (strcmp(destFileFormat, ".pfm") == 0)
        destFormat = D3DXIFF_PFM;
    else
        WarningF(
            "SaveTextureToFile: destFile should contain the file "
            "extension(.bmp, .jpg, .png, .dds, .dib, .hdr, .pfm).\n"
            "\ndds file format applied by default");
    LPDIRECT3DBASETEXTURE9 pTexture;
    if (effect->GetTexture(textureName, &pTexture) == D3D_OK) {
        lua_pushboolean(L, D3DXSaveTextureToFileA(destFile, destFormat, pTexture, 0) == D3D_OK);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

int SetTexture(lua_State *L) {
    // texture = EffectController.CreateTextureFromFile("/maps/map/Stratum0AlbedoTexture.dds")
    // EffectController.terrain:SetTexture("Stratum0AlbedoTexture", texture)
    if (lua_gettop(L) != 3)
        L->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 3, lua_gettop(L));
    if (!lua_islightuserdata(L, 3))
        L->LuaState->Error("%s", "The texture must be obtained by calling CreateTextureFromFile");
    if (Effects::vtbl[52] != reinterpret_cast<uintptr_t>(Effects::SetTextureHooked)) // lazy hook
        Effects::vtbl[52] = reinterpret_cast<uintptr_t>(Effects::SetTextureHooked);

    auto effect = static_cast<LPD3DXEFFECT>(getLightCObject(L, 1));
    if (effect == nullptr)
        L->LuaState->Error("%s", s_ExpectedAGameObject);
    auto textureName = lua_tostring(L, 2);
    auto texture = static_cast<LPDIRECT3DTEXTURE9>(lua_tolightuserdata(L, 3));
    auto hParameter = effect->GetParameterByName(NULL, textureName);
    if (hParameter != NULL && !Effects::overwrittenTextureHandles.contains(hParameter)) {
        Effects::overwrittenTextureHandles.push_back(hParameter);
    }
    auto res = Effects::originalSetTexture(effect, textureName, texture);
    lua_pushboolean(L, res == D3D_OK);
    return 1;
}

#define lua_tregister(L, f)   \
    (lua_pushstring(L, #f),   \
     lua_pushcfunction(L, f), \
     lua_settable(L, -3))
void RegisterLuaFunctions(lua_State *L) {
    // EffectController.ResetEffects()
    // texture = EffectController.CreateTextureFromFile('/maps/map/texture.dds')
    // EffectController.terrain:SetTexture('textureName', texture)
    // EffectController.terrain:SaveTextureToFile('file.dds', 'textureName') // file creates in exe folder
    lua_newtable(L);

    lua_tregister(L, ResetEffects);
    lua_tregister(L, CreateTextureFromFile);
    for (const auto &[effectName, pEffect] : Effects::effectPool) {
        lua_pushstring(L, effectName);
        lua_newtable(L);
        lua_pushstring(L, s_c_object);
        lua_pushlightuserdata(L, pEffect);
        lua_settable(L, -3);
        lua_tregister(L, SaveTextureToFile);
        lua_tregister(L, SetTexture);
        lua_settable(L, -3);
    }
    lua_setglobal(L, "EffectController");
}
#undef lua_tregister

/*vtbl Effect
QueryInterface	0
AddRef	1
Release	2
GetDesc	3
GetParameterDesc	4
GetTechniqueDesc	5
GetPassDesc	6
GetFunctionDesc	7
GetParameter	8
GetParameterByName	9
GetParameterBySemantic	10
GetParameterElement	11
GetTechnique	12
GetTechniqueByName	13
GetPass	14
GetPassByName	15
GetFunction	16
GetFunctionByName	17
GetAnnotation	18
GetAnnotationByName	19
SetValue	20
GetValue	21
SetBool	22
GetBool	23
SetBoolArray	24
GetBoolArray	25
SetInt	26
GetInt	27
SetIntArray	28
GetIntArray	29
SetFloat	30
GetFloat	31
SetFloatArray	32
GetFloatArray	33
SetVector	34
GetVector	35
SetVectorArray	36
GetVectorArray	37
SetMatrix	38
GetMatrix	39
SetMatrixArray	40
GetMatrixArray	41
SetMatrixPointerArray	42
GetMatrixPointerArray	43
SetMatrixTranspose	44
GetMatrixTranspose	45
SetMatrixTransposeArray	46
GetMatrixTransposeArray	47
SetMatrixTransposePointerArray	48
GetMatrixTransposePointerArray	49
SetString	50
GetString	51
SetTexture	52
GetTexture	53
GetPixelShader	54
GetVertexShader	55
SetArrayRange	56
GetPool	57
SetTechnique	58
GetCurrentTechnique	59
ValidateTechnique	60
FindNextValidTechnique	61
IsParameterUsed	62
Begin	63
BeginPass	64
CommitChanges	65
EndPass	66
End	67
GetDevice	68
OnLostDevice	69
OnResetDevice	70
SetStateManager	71
GetStateManager	72
BeginParameterBlock	73
EndParameterBlock	74
ApplyParameterBlock	75
DeleteParameterBlock	76
CloneEffect	77
SetRawValue	78
*/
