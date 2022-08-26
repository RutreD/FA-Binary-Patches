#include <cstdint>

float MinCHeight, MaxCHeight;

void* _thiscall HeightCylinders(char* this_)
{
    auto Sim = reinterpret_cast<char* (_thiscall *)(void*)>(0x7433B0)(this_);
    auto STIMap = *(uint32_t*)(Sim + 0x8CC);
    auto MapData = *(uint32_t*)STIMap;
    auto Heights = (uint16_t*)*(uint32_t*)MapData;
    auto SizeX = *(int*)(MapData + 0x4);
    auto SizeY = *(int*)(MapData + 0x8);
    uint16_t MinH = -1, MaxH = 0;
    for (auto I = 0; I < SizeX * SizeY; I++) {
        if (*Heights < MinH) MinH = *Heights;
        if (*Heights > MaxH) MaxH = *Heights;
        Heights++;
    }
    MinCHeight = MinH * 0.0078125f - 5.f;
    MaxCHeight = MaxH * 0.0078125f;
    this_ = (char*)*(uint32_t*)(0x10C7C28);
    reinterpret_cast<void (_thiscall *)(void*)>(0x7EDFE0)(this_ + 0x37C);
    reinterpret_cast<void (_thiscall *)(void*)>(0x81C0C0)(this_ + 0x410);
    return Sim;
}