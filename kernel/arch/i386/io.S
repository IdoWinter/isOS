.intel_syntax noprefix
.global inb
# inb - returns a byte from the given I/O port.
# stack: [esp+4] The address of the I/O port.
#        [esp  ] The return address.
inb:
  mov dx, [esp+4]
  in al, dx
  ret

.global outb
# outb - outputs a byte to the given I/O port.
# stack: [esp+8] The byte to output.
#        [esp+4] The address of the I/O port.
#        [esp  ] The return address.

outb:
  mov dx, [esp+4]
  mov al, [esp+8]
  out dx, al
  ret

.global enable_interrupts
enable_interrupts:
  sti
  ret
