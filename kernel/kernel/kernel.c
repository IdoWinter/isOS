#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/descriptors.h>
#include <kernel/irq.h>

void kernel_main(void *mbd, int magic) {
	terminal_initialize();
	printf("Setting up GDT...\n");
	setup_gdt();
	printf("GDT set!\nSetting up IDT...\n");
	setup_idt();
	setup_irq();
	printf("IDT set!\n");
	unsigned char ch = 0;
	while(1)
	{
		ch = getCharFromKeyboard();
		printf("%c", ch);
	}
	printf("Hello, kernel World!\n");
	for(;;)
	{
		asm("hlt");
	}
}
