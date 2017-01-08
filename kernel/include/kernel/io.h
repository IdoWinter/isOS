#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

//gets a byte from the given port.
unsigned char inb(unsigned short port);

//outputs a byte to the given port.
unsigned char outb(unsigned short port, char b);


void enable_interrupts();


#endif
