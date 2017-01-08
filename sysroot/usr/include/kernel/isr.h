#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H

typedef struct registers
{
  unsigned int ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int int_no, err_code;
  unsigned int eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t regs);

#endif
