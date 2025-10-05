#include <i86.h>
#include "IMPORTANT.H"
#include "STDIO.H"

unsigned short offset;
UINT8 far *VGA;

typedef struct SPRITE
{
    SINT16 w, h;
    UINT16 x, y;
    UINT8 *sprite_data;
} SPRITE;

SPRITE sprite;

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

int KEY_ARR_RIGHT = 0x4d;
int KEY_ARR_LEFT = 0x4b;
int KEY_ARR_UP = 0x48;
int KEY_ARR_DOWN = 0x50;
int KEY_ESC = 0x01;

void GFX_INIT() {
    __asm {
        mov al, 13h
        mov ah, 0
        int 10h
    }
    VGA = (UINT8 __far *)MK_FP(0xA000, 0x0000);
}

void GFX_PUT_PIXEL(int x, int y, UINT8 color) {
    offset = (y<<8) + (y<<6) + x;
    VGA[offset] = color;
}

void GFX_DRAW_SPRITE(SPRITE *sprite) {
    int i;
    int j;
    for (i = 0; i < sprite->w; i++)
    {
        for (j = 0; j < sprite->h; j++)
        {
            GFX_PUT_PIXEL(sprite->x + i, sprite->y + j, sprite->sprite_data[j * sprite->w + i]);
        }
    }
}

int KERNEL() {
    printf("The Kernel has been successfully loaded!\n");
    printf("256OS>");
    return 0;
}