global _small_code_
extern KERNEL_

segment _TEXT use16 class=CODE         	; code segment (16bit code)
_small_code_:                          	; watcom linker needs this label
..start:                              	; .. denotes the label to be used as the entry point

mov [BOOT_ORIGIN + BOOT_DISK], dl     	; dl stores the disk number right after boot

xor ax, ax                            	; int 13h needs segment registers to be set to 0, which is not the default on (some?) real hardware
mov ds, ax
mov ss, ax
mov sp, BOOT_ORIGIN 

mov ah, 0
mov al, 3
int 0x10

mov ah, 0x0e

mov al, 'L'
int 0x10
mov al, 'o'
int 0x10
mov al, 'a'
int 0x10
mov al, 'd'
int 0x10
mov al, 'i'
int 0x10
mov al, 'n'
int 0x10
mov al, 'g'
int 0x10
mov al, ' '
int 0x10
mov al, 'K'
int 0x10
mov al, 'e'
int 0x10
mov al, 'r'
int 0x10
mov al, 'n'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10
mov al, '.'
int 0x10
mov al, 0x0A
int 0x10
mov al, 0x0D
int 0x10

floppy:
    mov ah, 2
    mov al, 30
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [BOOT_ORIGIN + BOOT_DISK]      	; drive number
    mov bx, KERNEL_ORIGIN                	; es:bx = pointer to buffer (where to load)
    mov es, bx
    xor bx, bx
    int 0x13

mov ax, BOOT_ORIGIN_SEG            	; finally we can set these to get the full 64KiB of code, data and stack experience
mov ds, ax
mov ss, ax
mov sp, stack_top

jmp KERNEL_ORIGIN:0

BOOT_DISK:		db	0
BOOT_ORIGIN:        	equ	0x7c00
BOOT_ORIGIN_SEG:    	equ	0x7c0
KERNEL_ORIGIN:      	equ	0x7e0

times 510-($-$$) db 0
dw 0xaa55

call KERNEL_                       	; hand over execution to the kernel
jmp $                                	; fail safe

segment _STACK STACK class=STACK      	; stack segment 8KiB in size
resb 8 * 1024
stack_top: