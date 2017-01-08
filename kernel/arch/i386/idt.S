.intel_syntax noprefix
.global idt_write

# idt_write - write the interrupt descriptor table
# stack: [esp + 4] - The address of the IDT.

idt_write:
  mov eax,  [esp+4]
  lidt [eax]
  ret
