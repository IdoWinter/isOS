i686-elf-gcc -c kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc
if grub-file --is-x86-multiboot myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
mkdir -p bin
cp myos.bin bin/myos.bin
cp build/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir
