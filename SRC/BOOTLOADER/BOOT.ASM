global _small_code_
extern KERNEL_

segment _TEXT use16 class=CODE         	; code segment (16bit code)
_small_code_:                          	; watcom linker needs this label
..start:                              	; .. denotes the label to be used as the entry point

mov [BOOT_LOCATION + BOOT_DISK], dl

mov ah, 0
mov al, 3
int 0x10

xor ax, ax
mov ds, ax
mov ss, ax
mov sp, BOOT_LOCATION

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
mov al, 0x0A
int 0x10
mov al, 0x0D
int 0x10

reset:

    xor ax,ax
    int 0x13
    jc reset

    mov ax, KERNEL_LOCATION
    mov es,ax
    xor bx,bx

floppy:
    mov ah,0x2
    mov al, 30
    mov ch,0x0
    mov cl,0x2
    mov dh,0x0
    mov dl, [BOOT_LOCATION + BOOT_DISK]
    int 0x13
    jc floppy

mov ax, BOOT_LOCATION_SEG
mov ds, ax
mov ss, ax
mov sp, stack_top

jmp KERNEL_LOCATION:0

BOOT_DISK:		db	0
BOOT_LOCATION:        	equ	0x7c00
BOOT_LOCATION_SEG:    	equ	0x7c0
KERNEL_LOCATION:      	equ	0x7e0

times 510-($-$$) db 0
dw 0xaa55

call KERNEL_                       	; Hand over control to the C Kernel
jmp $ 

segment _STACK STACK class=STACK      	; 8KB stack segment
resb 8 * 1024
stack_top: