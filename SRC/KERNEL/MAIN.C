#include "IMPORTANT.H"
#include <i86.h>

#include "GFX.H"
#include "INPUT.H"
#include "STDIO.H"

void SET_CURSOR_POSX(UINT8 col) {
    __asm {
        mov ah, 02h
        mov bh, 00h
        mov dl, col
        INT 10h
    }
}

void SET_CURSOR_POSY(UINT8 row) {
    __asm {
        mov ah, 02h
        mov bh, 00h
        mov dh, row
        INT 10h
    }
}

UINT8 READ_CURSOR_POSX() {
    UINT8 CURSORPOS;
    __asm {
        mov ah, 03h
        mov bh, 0
        int 10h
        mov CURSORPOS, dl
    }
    return CURSORPOS;
}

UINT8 READ_CURSOR_POSY() {
    UINT8 CURSORPOS;
    __asm {
        mov ah, 03h
        mov bh, 0
        int 10h
        mov CURSORPOS, dh
    }
    return CURSORPOS;
}

SPRITE sprite;
char buffer[128];
int i = 0;

UINT8 sprite_data[] = {
    4, 15, 4, 15, 4, 15, 4, 15, 
    15, 4, 15, 4, 15, 4, 15, 4,
    4, 15, 4, 15, 4, 15, 4, 15,
    15, 4, 15, 4, 15, 4, 15, 4,
    4, 15, 4, 15, 4, 15, 4, 15,
    15, 4, 15, 4, 15, 4, 15, 4,
    4, 15, 4, 15, 4, 15, 4, 15,
    15, 4, 15, 4, 15, 4, 15, 4
};

int KERNEL() {
    printf("The Kernel has been successfully loaded!\n");
    printf("256OS>");

    while (1)
    {
        UINT8 KEY = READ_SCANCODE();
        UINT8 CURSORPOSX = READ_CURSOR_POSX();
        UINT8 CURSORPOSY = READ_CURSOR_POSY();
        switch (KEY)
        {
            case '\r':
                printf("\n");
                printf("256OS>");
                break;
            case 0x08:
                printf("\b");
                print_char(' ');
                CURSORPOSX--;
                SET_CURSOR_POSX(CURSORPOSX);
                SET_CURSOR_POSY(CURSORPOSY);
                break;
            default:
                buffer[i] = KEY;
                buffer[i]++;
                print_char(buffer[i]);
                break;
        }
    }
    
    return 0;
}