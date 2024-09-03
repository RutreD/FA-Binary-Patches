namespace Moho::CPrimBatcher {
__stdcall void *FlushBatcher(void *batcher) asm("0x0043A140");

struct Texture {
  int a;
  int b;
};

void FromSolidColor(Texture *t, unsigned int color) asm("0x4478C0");
} // namespace Moho::CPrimBatcher