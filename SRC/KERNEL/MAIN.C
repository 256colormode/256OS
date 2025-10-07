#include "IMPORTANT.H"
#include <i86.h>

#include "INPUT.H"
#include "STDIO.H"
#include "VGADEMO.H"

void SET_CURSOR_POS(UINT8 col, UINT8 row) {
    __asm {
        mov ah, 02h
        mov bh, 00h
        mov dl, col
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
                buffer[i] = '\0';
                
                printf("\n");
                if (strcmp(buffer, "vga") == 0)
                {
                    printf("vga!\n");
                    VGAMAIN();
                }
                printf("256OS>");
                i = 0;
                buffer == 0;
                break;
            case 0x08:
                if (CURSORPOSX >= 7)
                {
                    i--;
                    buffer[i] = ' ';
                    printf("\b");
                    print_char(' ');
                    CURSORPOSX--;
                    SET_CURSOR_POS(CURSORPOSX, CURSORPOSY);
                }   
                break;
            default:
                buffer[i] = KEY;
                print_char(buffer[i]);
                i++;
                break;
        }
    }
    
    return 0;
}