#include "RenderIcons.h"

void __stdcall ExtendRenderUserUnitIcon(UserUnitIconsTextures *unit_textures,
                                        struct_IconAux *aux,
                                        const Vector2f *pos) {
  using namespace Moho;
  UserEntity *entity = unit_textures->entity;
  UserUnit *unit = GetVTable(entity)->IsUserUnit2(entity);
  if (!unit)
    return;

  CPrimBatcher::Texture *texture = Offset<CPrimBatcher::Texture *>(unit, 1000);
  if (!texture->data) {
    return;
  }

  void *batcher = aux->batcher;
  CPrimBatcher::SetTexture(batcher, texture);

  Vector3f v34;
  Vector3f esi0;
  Vector3f a6;
  Vector3f ecx0;

  float half_width = 100;
  float half_height = 100;
  v34.x = pos->x + half_width;
  v34.y = pos->z - half_height;
  v34.z = 0.0;
  ecx0.x = pos->x + half_width;
  ecx0.y = pos->z + half_height;
  ecx0.z = 0.0;
  a6.x = pos->x - half_width;
  a6.y = pos->z + half_height;
  a6.z = 0.0;
  esi0.x = pos->x - half_width;
  esi0.y = pos->z - half_height;
  esi0.z = 0.0;
  DrawQuad2(0xFFFFFFFF, &ecx0, &v34, &a6, batcher, &esi0);
}