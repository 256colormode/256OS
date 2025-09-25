[bits 16]
[extern _k_main]

global entry

section stack stack
    resb 16384
stack_top:

section _ENTRY code
entry:
    ; setup the stack segment
    cli ; disable interrupts so that they wouldn't fuck up our stack segment while mofifying it
    xor ax, ax
    mov ds, ax
    mov es, ax
    
    push cs
    pop ax
    mov ss, ax
    mov sp, stack_top

    sti ; enable back interrupts

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
    jmp _k_main
    jmp $