#include "../define.h"

asm(".section h0; .set h0, 0x8C6718;"
    "CALL " QU(OnInitializeConsole) ";"
    ".section h1; .set h1, 0x7433F3;"
    "CALL " QU(OnCreateSim) ";"
    ".section h2; .set h2, 0x88C1E2;"
    "CALL " QU(OnCreateWldSession) ";");
