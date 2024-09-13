#pragma once
#include "moho.h"

void* GetCScriptType() asm("0x4C8530");
RRef* __cdecl REF_UpcastPtr(RRef*out, RRef *ref, void *sctype) asm("0x8D9590");

RRef REF_UpcastPtr(RRef *ref, void *sctype)
{
    RRef p;
    REF_UpcastPtr(&p, ref, sctype);
    return p;
}

void *GetCObject(lua_State *l, int index)
{
    lua_pushvalue(l, index);
    if (lua_istable(l, -1))
    {
        lua_pushstring(l, s_c_object);
        lua_rawget(l, -2);
    }
    if (lua_isuserdata(l, -1))
    {
        RRef udata;
        lua_touserdata(&udata, l, -1);
        void *sctype = GetCScriptType();
        RRef p = REF_UpcastPtr(&udata, sctype);
        lua_pop(l, 1);
        return p.d;
    }
    lua_pop(l, 1);
    return nullptr;
}


RRef* __cdecl  __CastObj(RRef* rref, void *obj) asm("0x4C9030");

RRef CastObj(void *obj)
{
    RRef res;
    __CastObj(&res, obj);
    return res;
}

void* LookupRType(void *typeinfo) asm("0x8E0750");

template <class CScriptClass>
Result<CScriptClass> GetCScriptObject(lua_State *l, int index)
{
    using CScriptType = typename CScriptClass::Type;
    using TResult = Result<CScriptClass>;
    void **obj =reinterpret_cast<void**>(GetCObject(l, index));
    if (obj == nullptr)
    {
        return TResult::Fail(s_ExpectedAGameObject);
    }
    if (*obj == nullptr)
    {
        return TResult::Fail(s_GameObjectHasBeenDestroyed);
    }
    RRef o = CastObj(*obj);

    void **type_ = (void **)CScriptType::Type;
    if (*type_ == nullptr)
    {
        *type_ = LookupRType((void *)CScriptType::Info);
    }
    RRef p = REF_UpcastPtr(&o, *type_);
    if (p.d == nullptr)
    {
        return TResult::Fail(s_IncorrectTypeOfGameObject);
    }
    return TResult::Success(p.d);
}