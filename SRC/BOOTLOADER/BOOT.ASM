[org 0x7c00]

[bits 16]

xor ax, ax
mov ds, ax

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

    mov ax,0x07e0
    mov es,ax
    xor bx,bx

floppy:
    mov ah,0x2
    mov al, 33
    mov ch,0x0
    mov cl,0x2
    mov dh,0x0
    int 0x13
    jc floppy

    jmp 0x07e0:0x0000

times 510-($-$$) db 0
dw 0xaa55