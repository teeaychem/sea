#include <stdio.h>
#define MAXLINE 4

int getlinealt(char line[], int maxline); /* getline is defined elsewhere */
void copy(char to[], char from[]);

/* print longest input line */
/* ^D in terminal to enter EOF. Useful: stty all  */

int main() {

  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];

  max = 0;

  while ((len = getlinealt(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(longest, line);
    }
    if (max > 0) {
      printf("%s\n", longest);
    }

  return 0;
}

int getlinealt(char s[], int lim)
{
  int c, i;

  /* while inside the limit  put each character in the s array */
  for (i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n'; ++i)
    /* if lim then get last MAXLINE chars when exceed
       issue is the line array doesn't have the space
       the problem then is \0.
       this isn't added to the array and so copy doesn't have inf to stop */
    {
      s[i] = c;
    }
  /* no more chars to get, but if ended on a new line keep it */
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  /* set string termination */
  /* if set i < lim above and then s[lim - 1] for \0 things work as
   expected so long as line exceeds MAXLINE */
  s[i] = '\0';
  return i;
}

void copy(char to[], char from[])
/* following the above, could force insert \0 at some lim here
   but, we'll already have a mess */
{
  int i;

  i = 0;
  /* /this/ style of writing things… asign from[i] to to[i] and then check the
     value isn't \0 */
  while ((to[i] = from[i]) != '\0')
    i++;
}
