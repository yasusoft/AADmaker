#include "crc.h"

unsigned long crcTable[256];
int crcComputed = 0;

void crcMakeTable()
{
  unsigned long c;
  int n, k;

  for (n = 0; n < 256; n ++)
  {
    c = (unsigned long) n;
    for (k = 0; k < 8; k ++)
    {
      if (c & 1)
        c = 0xedb88320L ^ (c >> 1);
      else
        c = c >> 1;
    }
    crcTable[n] = c;
  }
  crcComputed = 1;
}

unsigned long crcUpdate(unsigned long crc, unsigned char *buf, int len)
{
  unsigned long c = crc;
  int n;

  if (!crcComputed)
    crcMakeTable();
  for (n = 0; n < len; n ++)
    c = crcTable[(c ^ buf[n]) & 0xff] ^ (c >> 8);

  return c;
}

unsigned long crc(unsigned char *buf, int len)
{
  return crcUpdate(0xffffffffL, buf, len) ^ 0xffffffffL;
}
