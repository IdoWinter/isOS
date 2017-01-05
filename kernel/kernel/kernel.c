#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/descriptors.h>


void kernel_main(void *mbd, int magic) {
	setup_gdt();
	terminal_initialize();
	unsigned char ch = 0;
	while(1)
	{
		ch = getCharFromKeyboard();
		printf("%c", ch);
	}
	printf("Hello, kernel World!\n");
}
