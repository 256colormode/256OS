#include "IMPORTANT.H"

UINT16 offset;
UINT8 far *VGA;

typedef struct SPRITE
{
    SINT16 w, h;
    UINT16 x, y;
    UINT8 *sprite_data;
} SPRITE;

void GFX_INIT();

void GFX_PUT_PIXEL(int x, int y, UINT8 color);

void GFX_DRAW_SPRITE(SPRITE *sprite);