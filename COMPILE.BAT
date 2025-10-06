call "C:\WATCOM\owsetenv.bat"

nasm -f obj SRC\BOOTLOADER\BOOT.ASM -o BUILD\BOOT.O
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o BUILD\KERNEL.O SRC\KERNEL\MAIN.C
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o BUILD\STDIO.O SRC\KERNEL\STDIO.C
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o BUILD\INPUT.O SRC\KERNEL\INPUT.C
owcc -c -bdos -fno-stack-check -Os -s -march=i86 -o BUILD\GFX.O SRC\KERNEL\GFX.C

wlink form raw bin file BUILD\BOOT.O, BUILD\KERNEL.O, BUILD\STDIO.O, BUILD\INPUT.O, BUILD\GFX.O name BUILD\OS.BIN OPTION MAP=KERNEL.MAP

dd if=BUILD\OS.BIN of=floppy.img conv=notrunc