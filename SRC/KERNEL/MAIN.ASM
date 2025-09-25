[bits 16]
[extern _cmain_]

global entry

section stack stack
    resb 16384
stack_top:

section _ENTRY code
entry:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax

    ; set stack segment to same as code / kernel segment
    push cs
    pop ax        ; ax = CS
    mov ss, ax
    mov sp, stack_top

    sti
    
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
    mov al, 0x0A ; line feed
    int 0x10
    mov al, 0x0D ; carriage return
    int 0x10
    
    jmp _cmain_
    jmp $