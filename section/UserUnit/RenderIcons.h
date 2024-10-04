#include "../Draw/DrawFunc.h"
#include "GenericStructures.h"
#include "UserUnit.h"

struct UserUnitIconsTextures {
  Moho::UserEntity *entity;
  signed __int32 field_0;
  signed __int32 field_8;
  signed __int32 field_C;
  signed __int32 field_10;
  Moho::CPrimBatcher::Texture field_14;
  Moho::CPrimBatcher::Texture field_1C;
  Moho::CPrimBatcher::Texture field_24;
  int field_2C[2];
};

VALIDATE_SIZE(UserUnitIconsTextures, 0x34);

struct struct_IconAux // sizeof=0xAC
{
  Vector4f v0;
  Moho::CWldSession *session;
  /*Moho::CD3DPrimBatcher*/ void **batcher;
  /*Moho::GeomCamera3*/ void **cam;
  /*Moho::CWldMap*/ void **map;
  Moho::CPrimBatcher::Texture v8;
  FastVector<void *> genericIconList;
  Moho::CPrimBatcher::Texture pauseRest;
  Moho::CPrimBatcher::Texture stunnedRest;
  FastVector<UserUnitIconsTextures> vec1;
  FastVector<UserUnitIconsTextures> vec2;
  FastVector<UserUnitIconsTextures> vec3;
  FastVector<UserUnitIconsTextures> vec4;
  FastVector<UserUnitIconsTextures> vec5;
  unsigned int selfColor;
  unsigned int neutralColor;
  unsigned int allyColor;
  unsigned int enemyColor;
  unsigned int unidentifiedCOlor;
};

VALIDATE_SIZE(struct_IconAux, 0xAC);

SHARED {
  void __stdcall ExtendRenderUserUnitIcon(UserUnitIconsTextures * unit_textures,
                                          struct_IconAux * aux,
                                          const Vector2f *pos);
}