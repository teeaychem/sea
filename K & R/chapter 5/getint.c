#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

#define SIZE 10

int main()
{
  int n, array[SIZE], getint(int *);

  for (int i = 0; i < SIZE; i++)
    array[i] = '\0';

  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    ;

  printf("Recap!\n\t[");
  for (int i = 0;  i < n - 1; i++)
    printf("%d, ", array[i]);
  printf("%d]\n", array[n - 1]);

  return 0;
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
