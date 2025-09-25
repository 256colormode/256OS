#include <i86.h>
#include "IMPORTANT.H"
#include "STDIO.H"

UINT8 far *VGA;
UINT8 far *VGA_BACKBUFFER;
unsigned short offset;

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

void *MEMCPY(void *dest, const void *src, unsigned n) {
    if (n == 0) return dest;

    __asm {
        push ds
        push si
        push di

        mov bx, dest
        mov es, word ptr [bx+2]
        mov di, word ptr [bx]

        mov bx, src
        mov ds, word ptr [bx+2]
        mov si, word ptr [bx]

        mov cx, n
        shr cx, 1
        rep movsw
        jc has_byte
        jmp done

    has_byte:
        movsb

    done:
        pop di
        pop si
        pop ds
    }
    return dest;
}


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
    int row;
    int xy = sprite->x * sprite->y;
    offset = (sprite->y<<8) + (sprite->y<<6) + sprite->x;
    for (row = 0; row < sprite->h; row++)
    {
        int a = row * 320;
        MEMCPY(VGA + offset + a, sprite->sprite_data + row * sprite->w, sprite->w);
    }
}

void _cdecl k_main() {
    sprite.w = 2;
    sprite.h = 1;
    sprite.x = 100;
    sprite.y = 100;
    sprite.sprite_data = &sprite_data;
    GFX_INIT();
    while (1)
    {
        GFX_DRAW_SPRITE(&sprite);
    }
    
    
}