#include <kernel/irq.h>
#include <kernel/io.h>
#include <kernel/time.h>
#include <stdio.h>

void acknowledge_IRQ(char interrupt)
{
    if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_START_INTERRUPT + 8)
    {
      return;
    }
    if(interrupt > PIC2_START_INTERRUPT)
    {
      outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}


//Setup the two PICs.
void setup_irq()
{
  outb(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);
  outb(PIC1_DATA, PIC1_START_INTERRUPT); //Master interrupts start at 32
  outb(PIC2_DATA, PIC2_START_INTERRUPT); //Slave interrupts start at 40
  outb(PIC1_DATA, 4); //Tell master that slave is at the second place.
  outb(PIC2_DATA, 2);
  outb(PIC1_DATA, ICW4_8086); //Set up the correct mode.
  outb(PIC2_DATA, ICW4_8086);
  outb(PIC1_DATA, 0x00); //Do not ignore interrupts.
  outb(PIC2_DATA, 0x00); //Do not ignore interrupts.
  timer_phase(1000);
  add_callback(&handleTime, 0);
  enable_interrupts();
}


void (*isr_callbacks[16])() = { 0 };

void irq_handler(registers_t regs)
{
  acknowledge_IRQ(regs.int_no);
  if(isr_callbacks[regs.int_no - PIC1_START_INTERRUPT] != 0)
  {
    isr_callbacks[regs.int_no - PIC1_START_INTERRUPT]();
  }
  else
  {
    printf("IRQ %x detected!!\n", regs.int_no - PIC1_START_INTERRUPT);
  }
}

void add_callback(void (*callback)(), uint8_t index)
{
    isr_callbacks[index] = callback;
}
