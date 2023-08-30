#include "include/moho.h"
#include <type_traits>

using TConFunction = void(vector<string> *);
template <typename T>
class ConDescReg
{
    uintptr_t vftable;
    const char *name;
    const char *description;
    T *value;
public:
    constexpr ConDescReg(const char *name, const char *description, T *value) : 
        vftable(0x0E01700 /*Moho::CConCommand::`vftable'*/), name(name), description(description), value(value) {}

    void Register()
    {
        reinterpret_cast<void(__thiscall *)(void *, ConDescReg *)>(0x41E390)(reinterpret_cast<void *(__stdcall *)()>(0x41BEB0)(), this);
        if constexpr (std::is_same_v<T, bool>)
            vftable = 0xE01790; // Moho::TConVar<bool>::`vftable'
        else if constexpr (std::is_same_v<T, unsigned char>)
            vftable = 0xE017A0; // Moho::TConVar<unsigned char>::`vftable'
        else if constexpr (std::is_same_v<T, int>)
            vftable = 0xE01798; // Moho::TConVar<int>::`vftable'
        else if constexpr (std::is_same_v<T, unsigned int>)
            vftable = 0xE40BB0; // Moho::TConVar<unsigned int>::`vftable'
        else if constexpr (std::is_same_v<T, float>)
            vftable = 0xE017A8; // Moho::TConVar<float>::`vftable'
        else if constexpr (std::is_same_v<T, string>)
            vftable = 0xE017B0; // Moho::TConVar<std::string>::`vftable'
        else if constexpr (std::is_same_v<T, TConFunction>)
            vftable = 0xE01708; // Moho::CConFunc::`vftable'
        else
            static_assert(!std::is_same_v<T, T>, "Not supported type!");
    }
};
VALIDATE_SIZE(ConDescReg<TConFunction>, 0x10)

ConDescReg myConFunction{"name", "description", +[](vector<string> *vec_) {
                                           auto &vec = *vec_;
                                           WarningF("Command: %s", vec[0].data());
                                           if (vec.size() >= 2)
                                               for (auto it = vec.begin + 1; it != vec.end; it++)
                                                   WarningF("param[%d]: %s", it - vec.begin, it->data());
                                       }};

int v;
ConDescReg myConIntV{"name2", "description", &v};

void OnRegisterTCon()
{
    myConIntV.Register();
    myConFunction.Register();
}
