wcc -4 -d3 -s -wx -ms -zl -zq -fo=BUILD\KERNEL.OBJ SRC\KERNEL\MAIN.C
wcc -4 -d3 -s -wx -ms -zl -zq -fo=BUILD\STDIO.OBJ SRC\KERNEL\STDIO.C
nasm SRC\KERNEL\MAIN.ASM -f obj -o BUILD\KERNELASM.OBJ
nasm SRC\BOOTLOADER\BOOT.ASM -f bin -o BUILD\BOOT.BIN

wlink NAME BUILD\KERNEL.BIN FILE { BUILD\KERNELASM.OBJ BUILD\KERNEL.OBJ BUILD\STDIO.OBJ } @linker.lnk

dd if=BUILD\BOOT.BIN of=floppy.img

dd if=BUILD\KERNEL.BIN of=floppy.img bs=512 seek=1 count=33