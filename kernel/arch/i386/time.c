#include <kernel/time.h>
#include <kernel/io.h>

long ticks = 0;
int frequency = 0;


void timer_phase(int hz)
{
  frequency = hz;
  int divisor = PIT_MAX_FREQUENCY / hz;       /* Calculate our divisor */
  outb(PIT_COMMAND_PORT, PIT_SET_FREQ);             /* Set our command byte 0x36 */
  outb(PIT_DATA_PORT, divisor & 0xFF);   /* Set low byte of divisor */
  outb(PIT_DATA_PORT, divisor >> 8);     /* Set high byte of divisor */
}


long time()
{
  long my_time;
  clear_interrupts();
  my_time = ticks * 1000 / frequency;
  enable_interrupts();
  return my_time;
}

void handleTime()
{
  ticks++;
}

void wait(long milliseconds)
{
  long start_time = time();
  while (1){
    if (time() - start_time >= milliseconds)
    {
      break;
    }
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
  }

}
