#include <string.h>

void itoa(int num, char* buffer, char base)
{
  *buffer = 0;
  if (base < 2 || base > 36)
  {
    return;
  }

  if(num < 0) {
    *buffer++ = '-';
    *buffer = 0;
  }
  else if(!num) {
    *buffer++ = '0';
    *buffer = 0;
  }

  while(num) {

    char digit[2] = {"ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + num % base], 0 };
    strcat(buffer, digit);
    num /= base;
  }
  strrev(buffer);
}
