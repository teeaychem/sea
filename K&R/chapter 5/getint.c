#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

#define SIZE 10

int main()
{
  void testint();
  void testfloat();

  testfloat();

  return 0;
}

void testint()
{
  int n, intarray[SIZE], getint(int *);

  for (int i = 0; i < SIZE; i++)
    intarray[i] = '\0';

  for (n = 0; n < SIZE && getint(&intarray[n]) != EOF; n++)
    ;

  printf("Recap!\n\t[");
  for (int i = 0;  i < n - 1; i++)
    printf("%d, ", intarray[i]);
  printf("%d]\n", intarray[n - 1]);
}

void testfloat()
{
  int getfloat(float *), f;
  float floatarray[SIZE];


  for (int i = 0; i < SIZE; i++)
    floatarray[i] = '\0';

  for (f = 0; f < SIZE && getfloat(&floatarray[f]) != EOF; f++)
    ;

  printf("Recap!\n\t[");
  for (int i = 0;  i < f - 1; i++)
    printf("%g, ", floatarray[i]);
  printf("%g]\n", floatarray[f - 1]);

}



/* getint: get next integer from input into *pn */
int getint(int *pn)
{
  int c, d, sign;

  while (isspace(c = getch())) /* skip white space */
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if (c == '+' || c == '-') {
    d = getch();
    if (!isdigit(d)) {
      if (d != EOF) {
	ungetch(d); /* wait to see what comes next */
      }
      ungetch(c); /* not an int, return sign */
      return c;
    }
    else {
      c = d; /* d is the next c */
    }
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;

  if (c != EOF)
    ungetch(c);
  return c;
}


/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
  int c, d, sign;
  float power(int n, int m);

  while (isspace(c = getch())) /* skip white space */
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* it is not a number */
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if (c == '+' || c == '-') {
    d = getch();
    if (!isdigit(d)) {
      if (d != EOF) {
	ungetch(d); /* wait to see what comes next */
      }
      ungetch(c); /* not an int, return sign */
      return c;
    }
    else {
      c = d; /* d is the next c */
    }
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  if (c == '.') {
    c = getch();
    int dec = 1;
    for (; isdigit(c); c = getch()) {
      *pn = (*pn + ((float) (c - '0') / power(10, dec)));
      ++dec;
    }
  }

  *pn *= sign;

  if (c != EOF)
    ungetch(c);
  return c;
}



#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed−back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

float power(int n, int m)
{
  float r = n;
  while (--m > 0)
    r *= n;
  return r;
}
