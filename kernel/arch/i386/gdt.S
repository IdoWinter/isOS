.intel_syntax noprefix
.global gdt_write

# gdt_write: writes the gdt and initializes the segment registers.
# stack: [esp+4] The address of the gdt table.

gdt_write:
	mov eax, [esp+4]
	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush
flush:
		ret
