@echo off
C:\Users\N0t-PC\Downloads\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6\mingw64\bin\gcc -m32 -ffreestanding -nostdlib -fno-builtin -c kernel.c -o kernel.o
C:\Users\N0t-PC\Downloads\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6\mingw64\bin\ld -m elf_i386 -T kernel.ld kernel.o -o kernel.elf
C:\Users\N0t-PC\Downloads\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6\mingw64\bin\objcopy -O binary kernel.elf kernel.bin

C:\Users\N0t-PC\Downloads\fasmw17335\FASM.exe boot.asm boot.bin

copy /b boot.bin + kernel.bin os.img
echo Готово!
pause