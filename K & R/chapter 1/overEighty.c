#include <stdio.h>

#define MAXLINE 101

int getlinealt(char line[], int lim); /* getline is defined elsewhere */
void copy(char to[], char from[]);

/* print input lines over 80 chars */
/* ^D in terminal to enter EOF. Useful: stty all  */

int main()
{

  int len;
  int min = 80;
  char line[MAXLINE];
  char longest[MAXLINE];

  while ((len = getlinealt(line, MAXLINE)) > 0)
    {
      if (len > min) {
	copy(longest, line);
	printf("The previous line was over %d characters.\n", min);
	printf("Here it is (up to the first %d characters) again:\n%s\n", (MAXLINE - 1), longest);
      }
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
