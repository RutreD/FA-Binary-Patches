
#include "RenderIcons.h"

void __stdcall ExtendUserUnitCtor(Moho::UserUnit *uunit) {
  GetField<void *>(uunit, 1000) = nullptr;
  GetField<void *>(uunit, 1004) = nullptr;
}

void __stdcall ExtendUserUnitDtor(Moho::UserUnit *uunit) {
  Moho::CPrimBatcher::ReleaseTexture(
      Offset<Moho::CPrimBatcher::Texture *>(uunit, 1000));
}

void ExtendCtor() {
  asm("push ebp;"
      "call %[ExtendUserUnit];"
      "pop    edi;"
      "pop    esi;"
      "mov    eax, ebp;"
      "pop    ebp;"
      "jmp    0x008BF97E;"
      :
      : [ExtendUserUnit] "i"(ExtendUserUnitCtor)
      :);
}

void ExtendDtor() {
  asm("push esi;"
      "push esi;"
      "call 0x8BF9B0;"
      "call %[ExtendUserUnitDtor];"
      "ret 4;"
      :
      : [ExtendUserUnitDtor] "i"(ExtendUserUnitDtor));
}

void __stdcall ExtendRenderUserUnitIcon(UserUnitIconsTextures *unit_textures,
                                        struct_IconAux *aux, const Vector2f *pos) {
                                            
}

void ExtendRenderIcon() {

  asm("lea  edi, [ebp-0x84];"
      "push edi;"
      "push [ebp+0xC];"
      "push [ebp+0x8];"
      "call %[ExtendRenderUserUnitIcon];"
      "mov     ecx, [esp+0xC0-0xC];"
      "jmp 0x0085E083;"
      :
      : [ExtendRenderUserUnitIcon] "i"(ExtendRenderUserUnitIcon)
      :);
}