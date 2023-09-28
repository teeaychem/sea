#include <stdio.h>

void displayBinary(int n, int size);
double power(double n, double m);

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned replaceBits(unsigned x, int p, int n, unsigned y);

unsigned invert(unsigned x, int p, int n);

unsigned rotright(unsigned x, int n);

int bitcount(unsigned x);
int fasterBitcount(unsigned x);
int possibleBitcount();

void learning();
void learning2();

int main()
{
  // learning();
  learning2();

  /* for (int i = 55; i < 65; ++i) { */
  /*   // printf("%d:\t%d,\t%d\n", i, bitcount(i), fasterBitcount(i)); */
  /*   displayBinary(i, 8); */
  /*   displayBinary(~i << 1 >> 1, 8); */
  /*   displayBinary(invert(i,3,1), 8); */
  /*   printf("\n\n"); */
  /* } */


  /* unsigned o = 101; */
  /* unsigned ones = 255; */
  /* displayBinary(o, 8); */
  /* displayBinary(setbits(o,5,1,ones), 8); */

  return 0;
}

/* prints binary represenation of whole numbers
   negatives don't work.
   size sets the number of bits.
   optionally -1 size resizes bits to fit representation */
void displayBinary(int n, int size)
{
  if (n >= 0) {
    if (size < 0) {
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
	n -= power(2,size);
      }
    }
    putchar('\n');
  }
  if (n < 0) {
    if (size < 0) {
      while (-power(2,size) > n) {
	++size;
      }
    }
    --size;
    for ( ; size >= 0; --size) {
      if (-power(2,size) > n) {
	putchar('0');
	n += power(2,size);
      } else {
	putchar('1');
      }
    }
    putchar('\n');
  }
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


/* bitcount: count 1 bits in x */

int bitcount(unsigned x)
{
  int b;

  for (b = 0; x != 0; x >>=1)
    if (x & 01)
      b++;
  return b;
}

int fasterBitcount(unsigned x)
{
  int b = 0;

  while (x) {
    x &= (x - 1);
    b++;
  }
  return b;
}

int possibleBitcount()
{
  return fasterBitcount(~0);
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

/* like setbits, but instead of the rightmost n of y, take n from y at p
 key difference is first mask, which now shifts back to position. */
unsigned replaceBits(unsigned x, int p, int n, unsigned y)
{
  unsigned YMask1 = ~((~0 >> n) << p);
  unsigned YMask2 = ((~0 >> n) << (p - n));
  unsigned YMask = YMask1 & YMask2;
  unsigned rightmostNofYatP = YMask & y;
  unsigned XwithoutP = (x >> p) << p;
  unsigned XwithNfromY = XwithoutP | rightmostNofYatP;
  unsigned leftoverPMask = ~(~0 >> (p - n) << (p - n));
  unsigned leftoverP = x & leftoverPMask;
  unsigned replacement = XwithNfromY | leftoverP;

  return replacement;
}

/* to invert n bits from p replace n bits from p with complement */
unsigned invert(unsigned x, int p, int n)
{
  return replaceBits(x, p, n, ~x);
}


unsigned rotright(unsigned x, int n)
{
  int totalBits = possibleBitcount();
  int reducedN = n % totalBits;
  unsigned newLeft = x << (totalBits - reducedN);
  unsigned newRightMask = ~((~0 >> (totalBits - reducedN)) << (totalBits - reducedN));
  unsigned newRight = (x >> reducedN) & newRightMask;
  unsigned newBits = newLeft | newRight;

  return newBits;
}

/* some printouts with annotation from learning */
void learning2() {

  int testN = 343;
  displayBinary(testN,32);
  displayBinary(rotright(testN,34), 32);

  /* for (int i = 0; i < 64; ++i) */
  /*   displayBinary(i, 8); */
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



