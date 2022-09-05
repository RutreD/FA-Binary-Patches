// #include <cstdint>
// #include "include/LuaAPI.h"
// #include "include/moho.h"
// #include "include/mohoFuncs.hpp"


// uintptr_t __cdecl OnInitializeConsole()
// {
//     auto LPlus = reinterpret_cast<LuaState *>(0x1104410);
    
//     return 0x1104410;
// }

// Sim *__stdcall OnCreateSim(void *a1, void *a2)
// {
//     auto Sim = reinterpret_cast<struct Sim *(__stdcall *)(void *, void *)>(0x7434D0)(a1, a2);
//     // auto LPlus = *reinterpret_cast<LuaState **>(Sim + 0x8D8);
//     auto LPlus = Sim->LPlus;

//     return Sim;
// }

// CWldSession* __cdecl OnCreateWldSession(void *a1, void *a2, void *a3, void *a4)
// {
//     auto WldSession = reinterpret_cast<CWldSession*(__cdecl *)(void *, void *, void *, void *)>(0x897220)(a1, a2, a3, a4);
//     // auto LPlus = *reinterpret_cast<LuaState **>(WldSession + 0x10);
//     auto LPlus = WldSession->LPlus;

//     return WldSession;
// }
