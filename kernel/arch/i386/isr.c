#include <kernel/isr.h>
#include <stdio.h>
#include <kernel/io.h>

void isr_handler(registers_t regs)
{
  if(regs.int_no == 0x0D)
  {
    //printf("0x%x, %x\n", regs.int_no, regs.err_code);
  }
  else
  {
    printf("0x\n", regs.int_no);
  }
}
