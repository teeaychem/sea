#include <stdio.h>
#include <string.h>
#include "./alloc.c"
#include "./qsort.c"

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 10000 /* size of available space */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines_main(char *lineptr[], int maxlines, char buf[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() {

  int nlines; /* number of input lines read */
  char buf[ALLOCSIZE];

  if ((nlines = readlines_main(lineptr, MAXLINES, buf)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }

}

#define MAXLEN 1000 /* max length of any input line */


int readlines_main(char *lineptr[], int maxlines, char buf[])
{
  int getlinealt(char *, int);

  char *bufp = buf; /* buf only updated within readlines */
  int len;
  char line[MAXLEN];
  int nlines = 0;

 while ((len = getlinealt(line, MAXLEN)) > 0)
   /* replicate free mem test inline */
   if (nlines >= maxlines || (buf + ALLOCSIZE - bufp < len))
     return -1;
   else {
     line[len - 1] = '\0'; /* delete newline */
     lineptr[nlines++] = bufp; /* store ptr to line */
     strcpy(bufp, line);
     bufp += len; /* update bufp past stored line */
   }
 return nlines;
}

/* readlines: read input lines */
int readlines_alloc(char *lineptr[], int maxlines)
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
