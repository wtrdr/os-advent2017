#include "defines.h"
#include "serial.h"
#include "lib.h"

volatile int value = 10;

int main(void)
{
  serial_init(SERIAL_DEFAULT_DEVICE);
  puts("Hello World!\n");

  putxval(0x10, 0);   puts("\n");
  putxval(0xffff, 0); puts("\n");

  putxval(value, 0);   puts("\n");
  value = 20;
  putxval(value, 0); puts("\n");

  while(1)
    ;
  return 0;
}
