#include <string.h>

void strcat(char *destination, const char *source)
{
  size_t len = strlen(destination);
  size_t source_len = strlen(source);
  for(size_t i = 0; i < source_len; i++)
  {
    destination[len + i] = source[i];
  }
  destination[len + source_len] = 0;
}
