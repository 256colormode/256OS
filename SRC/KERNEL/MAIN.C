#include <i86.h>
#include "IMPORTANT.H"
#include "STDIO.H"

UINT8 far *VGA;
UINT8 far *VGA_BACKBUFFER;

typedef struct SPRITE
{
    SINT16 w, h;
    UINT16 x, y;
    UINT8 *sprite_data;
} SPRITE;

UINT8 sprite_data[2 * 1] = {
    4,4
};

SPRITE sprite;

void GFX_INIT() {
    __asm {
        mov al, 13h
        mov ah, 0
        int 10h
    }
    VGA = (UINT8 __far *)MK_FP(0xA000, 0x0000);
}

void GFX_PUT_PIXEL(int x, int y, UINT8 color) {
    unsigned short offset = (y<<8) + (y<<6) + x;
    VGA[offset] = color;
}

void GFX_DRAW(SPRITE sprite) {
    int i;
    
    for (i = 0; i < sprite.w; i++)
    {
        UINT8 clr = sprite.sprite_data[i];
        GFX_PUT_PIXEL(sprite.x + i, sprite.y, clr);
    }
    
}

void _cdecl cmain_() {
    sprite.w = 2;
    sprite.h = 1;
    sprite.x = 100;
    sprite.y = 100;
    sprite.sprite_data = &sprite_data;
    GFX_INIT();

    while (1)
    {
        GFX_PUT_PIXEL(100, 100, 52);
    }
}