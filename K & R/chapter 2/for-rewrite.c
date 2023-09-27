#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int getlinealt(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
  int len; /* current line length */
  int max; /* maximum length seen so far */
  char line[MAXLINE]; /* current input line */
  char longest[MAXLINE]; /* longest line saved here */

  max = 0;
  while ((len = getlinealt(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  if (max > 0) /* there was a line */
    printf("%s", longest);
  return 0;
}

/* getline: read a line into s, return length */

int getlinealt(char s[], int lim)
{
  char c;
  int i = 0;
  int ok = 1;

  while (ok) {
    if (i < lim-1) {
      c = getchar();
      if (c != EOF) {
	if (c != '\n') {
	  s[i] = c;
	  ++i;
	} else {
	  ok = 0;
	}
      } else {
	ok = 0;
      }
    } else {
      ok = 0;
    }
  }

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */

void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
