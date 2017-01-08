#include <kernel/io.h>
#include <kernel/irq.h>

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
  enable_interrupts();
}

void irq_handler(registers_t regs)
{
  printf("irq 0x%x detected!!!!\n", regs.int_no);
  acknowledge_IRQ(regs.int_no);

}
