asm(
    // Moho::CAiTransportImpl::"GetAttachPointsFor"+0xAA (switch case Moho::ETransportClass::TRANSPORTCLASS_4)  
    ".section h0; .set h0,0x5E6BDA;"
    "jmp .+0x1F; nop;" // add break to case so it doesn't fall-through and get overriden by TRANSPORTCLASS_SPECIAL
    // by utilizing output assignment of case TRANSPORTCLASS_3/TRANSPORTCLASS_SPECIAL to make room for the jump
);