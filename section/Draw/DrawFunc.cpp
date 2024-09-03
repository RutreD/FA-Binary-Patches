#include "CObject.h"
#include "magic_classes.h"
#include "moho.h"
#include "DrawFunc.h"
#include "utility.h"
#include <cmath>

#define NON_GENERAL_REG(var_) [var_] "g"(var_)

SHARED void _DrawRect(
    Vector3f *v1,
    Vector3f *v2,
    unsigned int color,
    float thickness,
    void *batcher,
    Vector3f *v3,
    void *heightmap,
    float f2)
{
    asm(
        "push %[f2];"
        "push %[heightmap];"
        "push %[v3];"
        "push %[batcher];"
        "movss xmm0, %[thickness];"
        "call 0x00455480;"
        "add esp, 0x10;"
        :
        : "c"(v2),
          "D"(color),
          "a"(v1),
          [thickness] "m"(thickness),
          NON_GENERAL_REG(f2),
          NON_GENERAL_REG(batcher),
          NON_GENERAL_REG(v3),
          NON_GENERAL_REG(heightmap)
        : "xmm0");
}

float THICKNESS = 0.1;
extern unsigned int CIRCLE_COLOR;
SHARED void _DrawCircle(void *batcher, Vector3f *pos, float radius, float thickness, uint32_t color, Vector3f *orientation)
{
    THICKNESS = thickness;
    CIRCLE_COLOR = color;
    asm(
        "push %[radius];"
        "push %[pos];"
        "push %[batcher];"
        "call 0x00456200;"
        "add esp, 0xC;"
        :
        : "c"(orientation),
          NON_GENERAL_REG(batcher),
          NON_GENERAL_REG(pos),
          NON_GENERAL_REG(radius)
        : "eax");
}

namespace Moho
{
    namespace CPrimBatcher
    {
       SHARED void __stdcall SetTexture(void *batcher, Texture *texture)
        {
            asm(
                "call 0x4386A0;"
                :
                : "D"(batcher),
                  "b"(texture)
                : "edx", "ecx", "eax");
        }

       SHARED void __stdcall SetViewProjMatrix(void *batcher, void *matrix)
        {
            asm(
                "push %[matrix];"
                "call 0x438640;"
                :
                : "b"(batcher),
                  NON_GENERAL_REG(matrix)
                : "edx", "eax");
        }
    } // namespace CPrimBatcher

} // namespace Moho




SHARED float delta_frame;

// offset +284 from CUIWorldView
SHARED void __thiscall CustomDraw(void *_this, void *batcher);


void CustomDrawEnter()
{
    asm(
        "push edi;"
        "mov ecx, esi;"
        "call %[CustomDraw];"
        "pop     edi;" // as done in original code
        "pop     esi;"
        "pop     ebx;"
        "mov     esp, ebp;"
        "jmp     0x86EF30;" // jump back
        :
        : [CustomDraw] "i"(CustomDraw)
        :);
}

void StoreFPS()
{
    asm(
        "movss  xmm0, dword ptr [esp+0x78-0x68];"
        "movss ds:%[delta_frame], xmm0;"
        "jmp 0x8D1A8B;"
        :
        : [delta_frame] "i"(&delta_frame)
        :);
}