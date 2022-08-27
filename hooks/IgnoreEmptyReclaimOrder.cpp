#include "../define.h"
asm(
    ".section h0; .set h0,0x008B06FD;"
    "call " QU(IgnoreEmptyReclaimOrder) ";");
