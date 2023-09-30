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

  while ((type = getop(s)) != EOF) {

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
      printf("error: unknown command %s\n", s);
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
  if (c != EOF)
    ungetch(c);
  if (s > 0 && !isdigit(s[i - 1])) {
    return s[i - 1];
  }
  return NUMBER;
}

#define BUFSIZE 100
int buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(void)  /* get a (possibly pushed−back) result of getchar */
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
