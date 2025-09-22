typedef signed __int8		SINT8;
typedef unsigned __int8		UINT8;
typedef signed __int16		SINT16;
typedef unsigned __int16	UINT16;
typedef signed __int32		SINT32;
typedef unsigned __int32	UINT32;

UINT8 far *VGA;
UINT8 far *VGA_BACKBUFFER;

void GFX_INIT() {
    __asm {
        mov al, 13h
        mov ah, 0
        int 10h
    }
    VGA = (unsigned char far*)0xA000;
}

void GFX_PUT_PIXEL(int x, int y, UINT8 color) {
    offset = (y<<8) + (y<<6) + x;
    VGA[offset] = color;
}

void main() {
    GFX_INIT();

    while (1)
    {
        GFX_PUT_PIXEL(100, 100, 4);
    }
}