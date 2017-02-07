#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/descriptors.h>
#include <kernel/irq.h>
#include <kernel/time.h>

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
		long my_time = time();
		printf("time: %d\n", my_time);
		wait(1000);
	}
	printf("Hello, kernel World!\n");
	for(;;)
	{
		asm("hlt");
	}
}
