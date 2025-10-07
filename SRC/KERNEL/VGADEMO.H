#include "GFX.H"

void VGAMAIN() {
    GFX_INIT();
    while (1)
    {
        GFX_PUT_PIXEL(100, 100, 52);
    }
    __asm {
        mov ah, 0
        mov al, 3
        int 0x10
    }
}