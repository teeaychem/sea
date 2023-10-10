#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./alloc.c"

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void writelines_reverse(char *lineptr[], int nlines);

void qsort_bk(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp_bk(char *s1, char *s2);
int strcmp_fold(char *s, char *t);


int numeric = 0; /* 1 if numeric sort */
int reverse = 0; /* 1 if reverse sort */
int fold = 0;    /* 1 if fold sort */
int directory = 0; /* 1 if directory sort */

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines; /* number of input lines read */
  int c;

  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0])) {
      switch (c) {
      case 'n':
	numeric = 1;
	break;
      case 'r':
	reverse = 1;
	break;
      case 'f':
	fold = 1;
	break;
      case 'd':
	directory = 1;
	break;
      default:
	printf("quicksort: illegal operation \'%c\'\n", c);
	break;
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort_bk((void**) lineptr,
	     0,
	     nlines - 1,
	     (int (*)(void*,void*)) (numeric ? numcmp_bk : strcmp_fold));
    (reverse ? writelines_reverse(lineptr, nlines) : writelines(lineptr, nlines));
    return 0;
  }
  else {
    printf("input too big to sort\n");
    return 1;
  }
}


/* qsort_bk: sort v[left]...v[right] into increasing order */
void qsort_bk(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;

  void swap(void *v[], int, int);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */

  swap(v, left, (left + right)/2); last = left;

  for (i = left+1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0) swap(v, ++last, i);
  swap(v, left, last);
  qsort_bk(v, left, last - 1, comp);
  qsort_bk(v, last+1, right, comp);
}

/* alpha to lowercase */
char lower(char c)
{
  if ('A' <= c && c <= 'Z')
    return c - 'A' + 'a';
  else
    return c;
}

/* test whether c is a letter number or blank */
char isLNB(char *c)
{
  return (('A' <= *c && *c <= 'Z') ||
	  ('a' <= *c && *c <= 'z') ||
	  ('0' <= *c && *c <= '9') ||
	  *c == ' ');
}


/* strcmp_bk_fold: return <0 if s<t, 0 if s==t, >0 if s>t
   where s,t are lowercased if fold is set */
int strcmp_fold(char *s, char *t)
{
  char isLNB(char *c);
  char lower(char c);
  char a, b;

  do {

    if (directory) {
      while (!isLNB(s) && *s != '\0')
	{ ++s; }
      while (!isLNB(t) && *t != '\0')
	{ ++t; }
    }

    a = fold ? lower(*s) : *s;
    b = fold ? lower(*t) : *t;

    if (a == b && a == '\0')
      { return 0; }

    ++s;
    ++t;
  }
  while (a == b);
  return a - b;
}


/* numcmp_bk: compare s1 and s2 numerically */
int numcmp_bk(char *s1, char *s2)
{
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int getlinealt(char *, int);
  char *alloc(int);

  int len;
  char *p, line[MAXLEN];
  int nlines = 0;

 while ((len = getlinealt(line, MAXLEN)) > 0)

   if (nlines >= maxlines || (p = alloc(len)) == NULL)
     return -1;
   else {
     line[len - 1] = '\0'; /* delete newline */
     strcpy(p, line);
     lineptr[nlines++] = p;
   }
 return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* writelines_reverse: write output lines in reverse */
void writelines_reverse(char *lineptr[], int nlines)
{
  lineptr = lineptr + (nlines - 1); // jump to end
  while (nlines-- > 0) // print going backwards
    printf("%s\n", *lineptr--);
}

int getlinealt(char *s, int lim)
{
  int c;
  int i = 0;

  while ((c = getchar()) != EOF && c != '\n') {

    if (i < (lim - 1)) {
      s[i] = c;
    }
    ++i;
  }

  if (i < (lim - 1)) { // count \n char.
    if (c == '\n') {
      s[i] = c;
      ++i;
    }
    s[i] = '\0';
  }
  else {
    s[lim - 1] = '\0';
  }

  return i;
}
