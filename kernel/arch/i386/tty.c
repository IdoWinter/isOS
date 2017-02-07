#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/io.h>

#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
char text_buffer[VGA_WIDTH*VGA_HEIGHT] = { 0 };

static size_t terminal_row;
static size_t terminal_column;
static uint16_t cursor_position;
static uint16_t text_position;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

/*
initialize the frame buffer.
*/
void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	cursor_position = 0;
	text_position = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	draw_buffer();
	draw_cursor();
}

/*
Set the color of the terminal.
*/
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

/*
Advance the cursor by a given number of steps.
*/
void advanceCursor(short steps)
{
		cursor_position += steps;
		if(cursor_position > VGA_HEIGHT*VGA_WIDTH)
		{
			cursor_position = 0;
		}
		terminal_row =  cursor_position / VGA_WIDTH;
		terminal_column =  cursor_position % VGA_WIDTH;
}


/*
Put a character at a certain location.
*/
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


/*
Draw the entire text buffer.
*/
void draw_buffer()
{
	cursor_position = 0;
	terminal_column = 0;
	terminal_row = 0;
	for(size_t i = 0; i < text_position; i++)
	{
		switch (text_buffer[i]) {
			case '\n':
				advanceCursor(80-terminal_column);
				break;
			case '\t':
				advanceCursor(4);
				break;
			default:
				terminal_putentryat(text_buffer[i], terminal_color, terminal_column, terminal_row);
				advanceCursor(1);
				break;
		}
	}
	for(size_t i = cursor_position; i < VGA_WIDTH*VGA_HEIGHT; i++)
	{
		terminal_putentryat(' ', terminal_color, i % VGA_WIDTH, i / VGA_WIDTH);
	}
}

void draw_cursor()
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, (cursor_position >> 8) & 0xFF);
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, cursor_position & 0xFF);
}

/*
Put a character in the terminal.
*/
void terminal_putchar(char c)
{
	if(c == 8)
	{
		terminal_deletechar();
	}
	else
	{
		text_buffer[text_position] = c;
		text_position++;
	}
	draw_buffer();
	draw_cursor();
}


void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_deletechar()
{
	if(text_position <= 0)
		return;
	size_t len = strlen(text_buffer);
	for(size_t i = text_position - 1; i < len; i++)
	{
		text_buffer[i] = text_buffer[i+1];
	}
	text_position--;
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
