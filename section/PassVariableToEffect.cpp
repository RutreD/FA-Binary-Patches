#include "include/moho.h"
#include "include/mohoFuncs.h"

constexpr long D3D_OK = 0l;
namespace Effect
{

    uintptr_t *vtbl;

    enum SCFAEffect // the effects loads alphabetically
    {
        cartographic,
        frame,
        mesh,
        particle,
        primbatcher,
        range,
        sky,
        terrain,
        ui,
        vision,
        water2
    };

    using CreateEffect = long(__stdcall *)(uintptr_t pDevice, uintptr_t pSrcData, unsigned int SrcDataLen, const uintptr_t *pDefines, uintptr_t pInclude, long Flags, uintptr_t pPool, uintptr_t *ppEffect, uintptr_t *ppCompilationErrors); // HRESULT(__stdcall *)(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataLen, const D3DXMACRO *pDefines, LPD3DXINCLUDE pInclude, DWORD Flags, LPD3DXEFFECTPOOL pPool, LPD3DXEFFECT *ppEffect, LPD3DXBUFFER *ppCompilationErrors)
    
    using Begin = long(__stdcall *)(uintptr_t pEffect, unsigned int *pPasses, long Flags);                                                                                                                                                   // HRESULT(__stdcall *)(LPD3DXEFFECT pEffect, UINT *pPasses, DWORD Flags)
    using SetFloatArray = long(__stdcall *)(uintptr_t pEffect, const void* hParameter, float *pf, unsigned int Count);                                                                                                                  // HRESULT SetFloatArray(D3DXHANDLE hParameter, const FLOAT *pf, UINT Count);
} // namespace SCFAEffect

template <std::size_t N, class T>
constexpr size_t count_of(T (&)[N]) { return N; }

uintptr_t pEffects[11];

Effect::Begin originalBegin;
long __stdcall BeginHooked(uintptr_t pEffect, unsigned int *pPasses, long Flags);

long __stdcall OnCreateEffect(uintptr_t pDevice, uintptr_t pSrcData, unsigned int SrcDataLen, const uintptr_t *pDefines, uintptr_t pInclude, long Flags, uintptr_t pPool, uintptr_t *ppEffect, uintptr_t *ppCompilationErrors)
{
    static int i = 0;
    if (i == count_of(pEffects))
        AbortF(L"ERROR in patch %s: uintptr_t pEffects[%d] overflow", L""__FILE__, count_of(pEffects));
 
    auto originalCreateEffect = *reinterpret_cast<uintptr_t *>(0x00C0F9D4);
    auto res = reinterpret_cast<Effect::CreateEffect>(originalCreateEffect)(pDevice, pSrcData, SrcDataLen, pDefines, pInclude, Flags, pPool, ppEffect, ppCompilationErrors);

    auto pEffect = *ppEffect;
    pEffects[i++] = pEffect;

    if (i == count_of(pEffects)) // last effect -> install vmt hook
    {
        auto VirtualProtect = reinterpret_cast<int(__stdcall *)(void *, int, long, long *)>(GetProcAddress(GetModuleHandle("KERNEL32"), "VirtualProtect"));
        Effect::vtbl = *reinterpret_cast<uintptr_t **>(pEffect);

        long oldProt;
        VirtualProtect(Effect::vtbl, 4 * 78, 0x04, &oldProt);
        originalBegin = reinterpret_cast<Effect::Begin>(Effect::vtbl[63]);
        Effect::vtbl[63] = reinterpret_cast<uintptr_t>(BeginHooked);
        // VirtualProtect(Effect::vtbl, 4 * 78, oldProt, &oldProt);
    }
    return res;
}

long __stdcall BeginHooked(uintptr_t pEffect, unsigned int *pPasses, long Flags)
{
    if (pEffects[Effect::mesh] == pEffect)
    {
        auto SetFloatArray = reinterpret_cast<Effect::SetFloatArray>(Effect::vtbl[32]);
        auto camera = getCamera("WorldCamera");
        auto pos = reinterpret_cast<float*>(camera + 0x1BC);

        SetFloatArray(pEffect, "CameraPosition", pos, 3);
        // if (SetFloatArray(pEffect, "CameraPosition", pos, 3) != D3D_OK) {
        //     WarningF("Fail mesh.fx SetFloatArray CameraPosition");
        // }
    }
    return originalBegin(pEffect, pPasses, Flags);
}

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
BOOL, IsParameterUsed	62
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
