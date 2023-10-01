#include <stdio.h>

void test(int n);

int getChar(int n);

int fasterBitcount(unsigned x);
int possibleBitcount();
void displayBinary(int n, int size);
double power(double n, double m);

void itobrecursive(int n, char s[], int b);

int main()
{

  int thatNumb = -(~0 >> possibleBitcount() << (possibleBitcount() - 1));
  test(thatNumb);
  test(5);
  test(-5);
  test(0);
  test(1);
  test(2);
  test(9);
  test(10);
  test(11);
}

void test(int n)
{
  char itoaPlusStr[100];
  for (int i = 0; i < 100; i++)
    itoaPlusStr[i] = '\0';

  printf("Expected:\t\t\t%d\n", n);
  printf("In binary:\t\t\t");
  displayBinary(n, possibleBitcount());

  itobrecursive(n, itoaPlusStr, 10);
  printf("Result from itobrecursive:\t%s\n\n", itoaPlusStr);
}

int getChar(int n)
{
    if (n < 10) {
      return n + '0';
    } else {
      return (n - 10) + 'a';
    }
}

void itobrecursive(int n, char s[], int b)
{
  int itobrecursiveHelper(int n, char s[], int b, int sign);

  int sign;
  char saved;

  if ((sign = n) < 0)
    n = ~n;

  if (sign < 0) {
    if ((n % b) < (b - 1)) {
      saved = getChar((n % b) + 1);
    } else {
      saved = '0';
      ++n;
    }
  } else {
    saved = getChar(n % b);
  }

  s[itobrecursiveHelper(n / b, s, b, sign)] = saved;
}

/* same as iotab, w specifies width to pad to with blanks  */
int itobrecursiveHelper(int n, char s[], int b, int sign)
{
  if (n == 0) {
    if (sign < 0) {
      s[0] = '-';
      return 1;
    } else {
      return 0;
    }
  }
  else if (n > 0) {
    // sign isn't used again, so overwrite to save space
    sign = itobrecursiveHelper((n / b), s, b, sign);
    s[sign] = getChar(n % b);
    return sign + 1;
  } else {
    return EOF; /* to ensure a return */
  }
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
