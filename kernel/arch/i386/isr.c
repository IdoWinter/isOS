#include <kernel/isr.h>
#include <stdio.h>
#include <kernel/io.h>

void isr_handler(registers_t regs)
{
  printf("0x%x\n", regs.int_no);
}
