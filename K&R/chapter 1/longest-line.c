#include <stdio.h>

#define MAXLINE 10

int getlinealt(char line[], int lim); /* getline is defined elsewhere */
void copy(char to[], char from[]);

/* print longest input line */
/* ^D in terminal to enter EOF. Useful: stty all  */

int main()
{

  int len;
  int max = 0;
  int lineCount = 0;
  char line[MAXLINE];
  char longest[MAXLINE];

  while ((len = getlinealt(line, MAXLINE)) > 0)
    {
      lineCount += 1;
      if (len > max) {
	max = len;
	copy(longest, line);
      }
    }

  lineCount += 1;

  if (max > 0) {
    printf("The longest of %d lines had %d characters.\n", lineCount, max);
    printf("The longest line (up to a limit of %d characters) was:\n", (MAXLINE - 1));
    printf("%s\n", longest);
  }

  return 0;
}

int getlinealt(char s[], int lim)
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

void copy(char to[], char from[])
{
  int i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}
