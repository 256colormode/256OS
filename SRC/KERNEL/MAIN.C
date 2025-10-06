#include "IMPORTANT.H"
#include <i86.h>

#include "GFX.H"
#include "INPUT.H"
#include "STDIO.H"

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

int KERNEL() {
    printf("The Kernel has been successfully loaded!\n");
    printf("256OS>");

    while (1)
    {
        UINT8 KEY = READ_SCANCODE();
        switch (KEY)
        {
            case '\r':
                printf("\n");
                printf("256OS>");
                break;
            default:
                print_char(KEY);
                break;
        }
    }
    
    return 0;
}