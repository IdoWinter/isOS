#include <string.h>

void itoa(int num, char* buffer)
{
  *buffer = 0;
  if(num < 0) {
    *buffer++ = '-';
    *buffer = 0;
    num = -num;
  }
  else if(!num) {
    *buffer++ = '0';
    *buffer = 0;
  }
  while(num) {
    char digit[2] = { num % 10 + '0', 0 };
    strcat(buffer, digit);
    num /= 10;
  }
  strrev(buffer);
}
