bits 16

global _small_code_
extern KERNEL_

segment _TEXT use16 class=CODE         	; code segment (16bit code)
_small_code_:                          	; watcom linker needs this label
..start:

call KERNEL_                       	; hand over execution to the kernel
jmp $                                	; fail safe

segment _STACK STACK class=STACK      	; stack segment 8KiB in size
resb 8 * 1024
stack_top:

BOOT_ORIGIN_SEG:    	equ	0x7c0

entry:
    mov ax, BOOT_ORIGIN_SEG            	; finally we can set these to get the full 64KiB of code, data and stack experience
    mov ds, ax
    mov ss, ax
    mov sp, stack_top
    
    ; printing hello world so that we can know if the kernel has been loaded
    mov ah, 0x0e

    mov al, 'h'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 'w'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, 'r'
    int 0x10
    mov al, 'l'
    int 0x10
    mov al, 'd'
    int 0x10
    mov al, 0x0A
    int 0x10
    mov al, 0x0D
    int 0x10
    
    ; loads our c code
    call KERNEL_
    jmp $