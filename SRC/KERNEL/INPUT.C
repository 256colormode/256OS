#include "IMPORTANT.H"
#include "INPUT.H"

UINT8 READ_SCANCODE() {
    UINT8 Scancode;
    __asm {
        mov ah, 00h
        int 16h
        mov Scancode, al
    }
    return Scancode;
}