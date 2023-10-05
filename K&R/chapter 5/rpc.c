/*
 A reverse polish calculator that processes arguments.
 You'll probably need to escape various characters.
 E.g. use '\*' for multiplication.
 */

#include <stdio.h>
#include <stdlib.h>  /* for  atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP     100  /* max size of operand or operator */
#define NUMBER    'n'  /* signal that a number was found */
#define VARIABLE  'v'  /* signal that a variable was found */
#define LAST      'l'  /* signal that a variable for last pop was found */

void push(double);
double pop(void);

#define MAXVAL  100  /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */
double vars[6] = {0,0,0,0,0,0}; /* variable store */
int vp; /* pointer to current variable */

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
  void evaluate(int type, char s[]);
  int parseop(char *op);

  ++argv;
  while (--argc > 0) {
    evaluate(parseop(*argv), *argv);
    ++argv;
  }

  return 0;
}

int parseop(char *arg)
{
  int i = 0;

  if (!isdigit(arg[i]) && arg[i] != '.' && arg[i] != '-' && arg[i] != '+') {
    if ('v' < arg[i] && arg[i] <= 'z')
      return VARIABLE;
    else if (arg[i] == 'l')
      return LAST;
    return arg[i];      /* not a number */
  }

  if (isdigit(arg[i]) || arg[i] == '-' || arg[i] == '+')
    while (isdigit(arg[++i]))
      ;
  if (arg[i] == '.')      /* collect fraction part */
    while (isdigit(arg[++i]))
      ;

  if (i > 0 && !isdigit(arg[i - 1]))
    return arg[i - 1];
  else if (arg[i] == '\0') // only return n if exhausted arg
    return NUMBER;
  else
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

void evaluate(int type, char s[])
{
  // printf("Evaluating: %s\n", s);
  double op1, op2;
  int swap;

  switch (type) {

  case NUMBER:
    push(atof(s));
    break;

  case VARIABLE:
    vp = s[0] - 'v';
    // printf("variable vp: %d\n", vp);
    push(vars[vp]);
    break;

  case LAST:
    push(vars[5]);
    break;

  case '=':
    pop(); // ignore variable value
    vars[vp] = pop();
    // push(vars[vp]); // don't evaluate var immediately
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

  case 'p':
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
