#include <stdio.h>

void learning();
void displayBinary(int n, int size);
double power(double n, double m);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
  // learning();

  unsigned o = 101;
  unsigned ones = 255;
  displayBinary(o, 8);
  displayBinary(setbits(o,5,1,ones), 8);

  return 0;
}

/* prints binary represenation of whole numbers
   negatives don't work.
   size sets the number of bits.
   optionally -1 size resizes bits to fit representation */
void displayBinary(int n, int size)
{
  if (size < 1) {
    while (power(2,size) < n) {
      ++size;
    }
  }
  --size;
  for ( ; size >= 0; --size) {
    if (power(2,size) > n) {
      putchar('0');
    } else {
      putchar('1');
      n = n - power(2,size);
    }
  }
  putchar('\n');
}

/* basic power func */
double power(double n, double m)
{
  if (m == 0) {
    return 1;
  }
  else {
    double base = n;
    for (int i = 1; i < m; i++) {
      base *= n;
    }
    return base;
  }
}

/* getbits: get n bits from position p
   from the book */
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits with the process worked through slowly */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned rightmostYMask = ~((~0 >> n) << n);
  unsigned rightmostNofY = rightmostYMask & y;
  unsigned rightmostNofYatP = rightmostNofY << (p - n);
  unsigned XwithoutP = (x >> p) << p;
  unsigned XwithNfromY = XwithoutP | rightmostNofYatP;
  unsigned leftoverPMask = ~(~0 >> (p - n) << (p - n));
  unsigned leftoverP = x & leftoverPMask;
  unsigned replacement = XwithNfromY | leftoverP;

  return replacement;
}

/* some printouts with annotation from learning */
void learning() {

  printf("Learning!\n");

  displayBinary(0177, -1); // 0177 is seven 1s
  displayBinary(177, -1); // different to 0177 (mixed)
  displayBinary(077, -1); // 077 is six 1s
  displayBinary(0177700, 16); // ten 1s and six 0s.

  printf("%d\n", getbits(2,3,4));
  printf("%d\n", getbits(3,3,4));
  printf("%d\n", getbits(4,5,4));
  printf("%d\n", 2 << 1); // 10 to 100
  printf("%d\n", 2 >> 1); // 10 to 1
  printf("%d\n", 2 | 1); // 10 or 01 so 11
  printf("%d\n", 2 & 1); // 10 and 01, so 00

  /* 0 gets 0s, but to ensure size doesn't matter, make sure everything is 1
     and then change everything to 0s with ~

     In other words, ~0 should fill everything with 1s and then ~ again changes
     all the 1s to 0s */
  unsigned m = 2;
  printf("%d\n", ~(~0 << m));
  displayBinary(~(~0 << m), -1);

  printf("---\n");

}
