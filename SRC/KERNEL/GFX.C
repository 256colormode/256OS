#include "IMPORTANT.H"
#include "GFX.H"

#include <i86.h>

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