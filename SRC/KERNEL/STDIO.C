#include "IMPORTANT.H"

int _PIA = 0;

UINT8 strlen(const char* string) {
    UINT8 len = 0;
    while (*string != '\0')
    {
        len++;
        string++;
    }
    return len;
}

void printf(const char* string) {
    int i;
    UINT8 len = strlen(string);
    __asm {
        mov ah, 0x0e
    }

    for (i = 0; i < len; i++)
    {
        char c = string[i];
        __asm {
            mov al, c
            int 0x10
        }
    }
    
}