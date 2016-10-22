#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H


#define KEYBOARD_PORT  0x60
#define SHIFT_MASK    0b10000000
#define CAPSLOCK_MASK 0b01000000
#define NUMLOCK_MASK  0b00100000
#define CONTROL_MASK  0b00010000
#define ALT_MASK      0b00001000

unsigned char getScanCode();
unsigned char scanCode2Ascii(unsigned char scanCode);
unsigned char getCharFromKeyboard();

#endif
