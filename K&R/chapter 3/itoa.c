#include <stdio.h>

void testITOA(int n);

int getChar(int n);
void itobW(int n, char s[], int b, int w);
void itob(int n, char s[], int b);
void itoa(int n, char s[]);
void itoaPlus(int n, char s[]);
int reverse(char s[]);

int fasterBitcount(unsigned x);
int possibleBitcount();
void displayBinary(int n, int size);
double power(double n, double m);

int main()
{

  int thatNumb = -(~0 >> possibleBitcount() << (possibleBitcount() - 1));
  testITOA(thatNumb);
  testITOA(5);
  testITOA(-5);
  testITOA(0);

  int w = 16;
  char itobStr[100];
  itobW(-55555, itobStr, 16,w);

  printf("\t\t\t\t|");
  for (int i = 0; i < w; i++) {
    printf("%d", i % 10);
  }
  printf("\n");
  printf("Result:\t\t\t|%s\n", itobStr);
  return 0;
}

void testITOA(int n)
{
  char itoaStr[100];
  char itoaPlusStr[100];

  printf("Expected:\t\t\t%d\n", n);
  printf("In binary:\t\t\t");
  displayBinary(n, possibleBitcount());

  itoa(n, itoaStr);
  printf("Result from itoa:\t%s\n", itoaStr);

  itoaPlus(n, itoaPlusStr);
  printf("Result from itoa+:\t%s\n\n", itoaPlusStr);
}

int getChar(int n)
{
    if (n < 10) {
      return n + '0';
    } else {
      return (n - 10) + 'a';
    }
}

/* same as iotab, w specifies width to pad to with blanks  */
void itobW(int n, char s[], int b, int w)
{
  int i, sign;
  if ((sign = n) < 0)
    n = ~n;
  i = 0;

  if (sign < 0) {
    if ((n % b) < (b - 1)) {
      s[i++] = getChar((n % b) + 1);
      --w;
      (n /= b);
    } else {
      s[i++] = '0';
      --w;
      (n /= b);
      ++n;
    }
  } else {
    s[i++] = getChar(n % b);
    --w;
    (n /= b);
  }

  while (n > 0) {
    s[i++] = getChar(n % b);
    --w;
    (n /= b);
  }

  if (sign < 0) {
    s[i++] = '-';
    --w;
  }
  for (; w > 0; w--, i++) {
    s[i] = ' ';
  }
  s[i] = '\0';
  reverse(s);
}

/* works for b < 37, 0 to 9 then a to z  */
void itob(int n, char s[], int b)
{
  int i, sign;
  if ((sign = n) < 0)
    n = ~n;
  i = 0;

  if (sign < 0) {
    if ((n % b) < (b - 1)) {
      s[i++] = getChar((n % b) + 1);
      (n /= b);
    } else {
      s[i++] = '0';
      (n /= b);
      ++n;
    }
  } else {
    s[i++] = getChar(n % b);
    (n /= b);
  }

  while (n > 0) {
    s[i++] = getChar(n % b);
    (n /= b);
  }

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0) /* record sign */
    n = -n; /* make n positive */
  i = 0;
  do { /* generate digits in reverse order */
    s[i++] = n % 10 + '0'; /* get next digit */
  } while ((n /= 10) > 0); /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

/* itoaplus: convert n to characters in s
   rather than use - use ~ to flip bits.
   then, negative needs to be increase by one.
   so special first case.
   hence, do while is no longer ideal, instead while
*/
void itoaPlus(int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0)
    n = ~n;
  i = 0;

  if (sign < 0) {
    if (n % 10 < 9) {
      s[i++] = n % 10 + '1';
      (n /= 10);
    } else {
      s[i++] = '0';
      (n /= 10);
      ++n;
    }
  } else {
    s[i++] = n % 10 + '0';
    (n /= 10);
  }

  while (n > 0) {
    s[i++] = n % 10 + '0';
    (n /= 10);
  }

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}


/* my reverse from c1 */
int reverse(char s[])
{
  int left = 0;
  int right = 0;
  char swap;

  for (right = 0; s[right] != '\0'; right++) {}
  --right;

  while (right - left > 0) {
    swap = s[left];
    s[left] = s[right];
    s[right] = swap;
    ++left;
    --right;
  }
  return 1;
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
