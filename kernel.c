/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint16_t vga_entry(uint8_t uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static inline uint8_t vga_color_entry(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

size_t strlen(char *str)
{
	int count = 0;
	while(str[count])
	{
		++count;
	}
	return count;	
}


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 

static inline size_t get_index(size_t row, size_t column)
{
	return row*VGA_WIDTH + column;
} 

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_color_entry(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000; //Magic number
	for (size_t row = 0; row < VGA_HEIGHT; row++)
	{
		for (size_t column = 0; column < VGA_WIDTH;  column++)
		{
			size_t index = get_index(row, column);
			terminal_buffer[index] = vga_entry(' ',  terminal_color);
		}
	}	
}


void putCharInPlace(char ch)
{
	size_t index = get_index(terminal_row, terminal_column);
	terminal_buffer[index] = vga_entry(ch, terminal_color);
	terminal_column = (terminal_column + 1) % VGA_WIDTH;
	if (terminal_column == 0)
	{
		++terminal_row;
	}
}

void put_char(char ch, uint8_t color, int x, int y)
{
	size_t index = get_index(x, y);
	terminal_buffer[index] = vga_entry(ch, color);
}

void print_string(char *str)
{
	size_t length = strlen(str);
	for(size_t i = 0; i < length; i++)
	{
		putCharInPlace(str[i]);
	}
}


void kernel_main()
{
	terminal_initialize();
	print_string("Hello, OS!");
}
