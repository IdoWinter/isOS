#include <kernel/keyboard.h>
#include <kernel/io.h>


unsigned char isKeyPressed[16] = { 0 };
unsigned char flags = 0;

unsigned char noShift[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', \
'-', '=', 8, '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 10, 0,\
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x',\
'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' '};

unsigned char shiftCodes[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',\
'_', '+', 8, '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 10, 0,\
'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 'X',\
'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' '};


unsigned char getScanCode()
{
  unsigned char code = inb(KEYBOARD_PORT);
  if(code > 0x80)
  {
    isKeyPressed[(code - 0x80) / 8] &= ~(1 << (7 - code % 8)); //write only code.
  }
  else
  {
    isKeyPressed[code / 8] |= 1 << (7 - code % 8);
  }
  if(code == 0x3A)
  {
    flags ^= CAPSLOCK_MASK;
  }
  return code;
}

unsigned char isKeyPressedByCode(unsigned char scanCode)
{
  return (isKeyPressed[scanCode / 8] >> (7 - scanCode % 8)) & 1;
}

unsigned char scanCode2Ascii(unsigned char scanCode)
{
  if(scanCode < 0x02 || scanCode > 0x39)
  {
    return 0;
  }
  unsigned char isShiftPressed = isKeyPressedByCode(0x36) || isKeyPressedByCode(0x2A);
  unsigned char isCapsLockPressed = (flags & CAPSLOCK_MASK) >> 6;
  if (noShift[scanCode - 0x2] <= 'z' && noShift[scanCode - 0x2] >= 'a')
  {
    return noShift[scanCode - 0x2] + ('A'-'a')*(isCapsLockPressed ^ isShiftPressed);
  }
  if (isShiftPressed)
  {
    return shiftCodes[scanCode-0x2];
  }
  return noShift[scanCode-0x2];
}

unsigned char getCharFromKeyboard()
{
  static unsigned sc = 0;
  unsigned char ch = 0;
  do {
    if(getScanCode() != sc)
    {
      sc = getScanCode();
      if(ch = scanCode2Ascii(sc))
      {
        return ch;
      }
    }
  } while(1);
}
