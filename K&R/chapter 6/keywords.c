#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
  char *word;
  int count;
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

struct key keytab[] = {
  "#define", 0,
  "_a", 0,
  "a", 0,
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  /* ... too many to add */
  "test", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0,
};


/* if escape string is found write down closing string
   note, strcmp returns 0 when strings are equal. */
char esc_str[3];

int checkleftescape(char *word)
{
  if (!strcmp(word, "/*"))
    { strcpy(esc_str, "*/");
      return 1; }
  else if (!strcmp(word, "\""))
    { strcpy(esc_str, word);
      return 1; }
  else if (!strcmp(word, "//"))
    { strcpy(esc_str, "\n");
    return 1; }
  else
    { return 0; }
}

int checkrightescape(char *word)
{
  return !strcmp(word, esc_str);
}

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main()
{
  int n;
  int gw;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    // skip anything between comments
    if (checkleftescape(word))
      { while ((gw = getword(word, MAXWORD)) != EOF && !checkrightescape(word)) { }; }
    // note additional EOF check
    if (gw != EOF && (n = binsearch(word, keytab, NKEYS)) >= 0)
      { keytab[n].count++; }
  }

  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0) printf("%4d %s\n", keytab[n].count, keytab[n].word);
  return 0;
}

/* binsearch: find word in tab[0]...tab[n−1] */
int binsearch(char *word, struct key tab[], int n)
{
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low+high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int iswordpart(int c, int initialchar)
{
  return ((initialchar ? isalpha(c) : isalnum(c)) ||
	  c == '_' ||
	  c == '/' ||
	  c == '*' ||
	  c == '\\' ||
	  c == '#');
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c, getch(void);
  void ungetch(int);
  int iswordpart(int c, int initialchar);
  char *w = word;

  while (isspace(c = getch()))
    { };
  if (c != EOF)
    { *w++ = c; }

  if (!iswordpart(c, 1))
    { *w = '\0';
      return c; }
  for ( ; --lim > 0; w++)
    { if (!iswordpart(*w = getch(), 0))
	{ ungetch(*w);
	  break; }
    }
  *w = '\0';

  return word[0];
}





#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed−back) character */
    { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

