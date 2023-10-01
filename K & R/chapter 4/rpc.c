#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP     100  /* max size of operand or operator */
#define NUMBER    'n'  /* signal that a number was found */
#define VARIABLE  'v'  /* signal that a variable was found */
#define LAST      'l'  /* signal that a variable for last pop was found */

int getop(char []);
void push(double);
double pop(void);

#define MAXVAL  100  /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */
double vars[6] = {0,0,0,0,0,0}; /* variable store */
int vp; /* pointer to current variable */

/* reverse Polish calculator */
int main()
{
  int type;
  double op1, op2;
  char s[MAXOP];

  while ((type = getop(s)) != ' ') {

    int swap;

    switch (type) {

    case NUMBER:
      push(atof(s));
      break;

    case VARIABLE:
      vp = s[0] - 'v';
      printf("variable vp: %d\n", vp);
      push(vars[vp]);
      break;

    case LAST:
      push(vars[5]);
      break;

    case '=':
      pop(); // ignore variable value
      vars[vp] = pop();
      push(vars[vp]); // evalute var immediately
      break;

    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
	push(pop() / op2);
      else
	printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      op1 = pop();
      while (op1 >= op2)
	op1 -= op2;
      push(op1);
      break;

    case 'e':
      push(exp(pop()));
      break;

    case '\n':
      printf("\t%.8g\n", pop());
      break;

    case '?': /* print top two elements, though top is popped if \n is required for input to be processed */
      if (sp == 0)
	printf("The stack is empty\n");
      if (sp > 0)
	printf("Top:\t%g\n", val[sp - 1]);
      if (sp > 1)
	printf("Below:\t%g\n", val[sp - 2]);
      break;
    case 'd':
      push(val[sp - 1]);
      break;
    case 's':
      swap = val[sp - 1];
      val[sp - 1] = val[sp - 2];
      val[sp - 2] = swap;
      break;
    case 'c':
      sp = 0;
      break;

    default:
      printf("error: unknown command:%s\n", s);
      break;
    }
  }
  return 0;
}


/* push:  push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
  if (sp > 0) {
    vars[5] = val[--sp];
    return vars[5];
  }
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getch(void);
void ungetch(int);

/* getop:  get next character or numeric operand */
int getop(char s[])
{
  int getopbystr(char s[]);
  return getopbystr(s);

  /* int getopbych(char s[]); */
  /* return getopbych(s); */
}


/* outside of function for persistence */
char line[MAXOP]; /* line buffer */
int lp = 0; /* line pointer, ++lp is unparsed */


int getopbystr(char s[])
{
  int getlinealt(char s[], int lim);
  void copyab(char to[], char from[], int a, int b);

  if (line[lp] == '\0') {
    getlinealt(line, MAXOP);
    lp = 0;
  }

  while (line[lp] == ' ' || line[lp] == '\t')
    lp++; // point smth after b/t

  if (!isdigit(line[lp]) &&
      line[lp] != '.' &&
      line[lp] != '-' &&
      line[lp] != '+') {
    copyab(s, line, lp, lp + 1);
    ++lp;
    if ('v' < line[lp - 1] && line[lp - 1] <= 'z') {
      return VARIABLE;
    }
    else if (line[lp - 1] == 'l') {
      return LAST;
    }
    return line[lp - 1]; /* not a number */
  }

  int i = lp + 1; /* always capture next symbol */

  /* if digit, gather */
  while (isdigit(line[i])) {
    ++i;
  }

  /* collect fraction part if present */
  if (line[i + 1] == '.') {
    ++i;
    while (isdigit(line[i + 1]))
      ++i;
  }

  /* update s
   this could be skipped if not digit, but then need to consider lp update
   and contrast to getopbych */
  copyab(s, line, lp, i);
  /* update unprocessed */
  lp = i;

  if (!isdigit(line[i - 1])) {
    return line[i - 1];
  }
  else {
    return NUMBER;
  }
}


/* fill op string by getch and return type info */
int getopbych(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0'; /* what is the purpose of this? s[i] is always set below */

  if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
    if ('v' < c && c <= 'z')
      return VARIABLE;
    else if (c == 'l')
      return LAST;
    return c;      /* not a number */
  }

  i = 0;

  if (isdigit(c) || c == '-' || c == '+')    /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;

  if (c == '.')      /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';

  /* Put char in the buffer */
  if (c != EOF)
    ungetch(c);

  if (i > 0 && !isdigit(s[i - 1])) {
    return s[i - 1];
  }
  return NUMBER;
}


#define BUFSIZE 100
int buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

int getch(void)  /* get a (possibly pushed-back) result of getchar */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)   /* push result of getchar back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void ungets(char s[])   /* push string back on input */
{
  for (int i = 0; s[i] != '\0'; i++) {
    if (bufp >= BUFSIZE)
      printf("ungets: too many characters\n");
    else
      buf[bufp++] = s[i];
  }
}


/* For reference
   getlinealt: get line into s, return length
   renamed getline from the book, as getline is in some header
*/
int getlinealt(char s[], int lim)
{
  int c, i;
  i = 0;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;

  if (c == '\n')
    s[i++] = c;

  s[i] = '\0';

  return i;
}

/* copy: copies 'from' between (inlc.) a and b into 'to'.
   assumes to is big enough */
void copyab(char to[], char from[], int a, int b)
{
  int i = 0;

  while (a < b) {
    to[i++] = from[a++];
  }
  to[i] = '\0';
}
