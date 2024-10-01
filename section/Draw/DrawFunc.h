#include "moho.h"
namespace Moho::CPrimBatcher {
__stdcall void *FlushBatcher(void *batcher) asm("0x0043A140");

struct Texture {
  int a;
  int b;
};

void FromSolidColor(Texture *t, unsigned int color) asm("0x4478C0");
SHARED {
  void ReleaseTexture(Texture*t);
  void __stdcall SetTexture(void *batcher, Texture *texture);
  void __stdcall SetViewProjMatrix(void *batcher, void *matrix);
}
} // namespace Moho::CPrimBatcher

struct Vertex
{
  Vector3f v;
  unsigned int color;
  float scaleX;
  float scaleY;
};

SHARED {

  void _DrawCircle(void *batcher, Vector3f *pos, float radius, float thickness,
                   uint32_t color, Vector3f *orientation);
  void __thiscall CustomDraw(void *_this, void *batcher);
  void _DrawRect(Vector3f * v1, Vector3f * v2, unsigned int color,
                 float thickness, void *batcher, Vector3f *v3, void *heightmap,
                 float f2);
  char *DRAW_WireBox(VMatrix4 * a1, /*CD3DPrimBatcher*/ void *batcher);
  char *DrawLine(Vertex *v1, void *batcher, Vertex *v2);
  char *DrawQuad(Vertex *a1, void *batcher, Vertex *a3, Vertex *a4, Vertex *a5);
}