#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getlinealt(char line[], int max);
int lstrindex(char source[], char searchfor[]);
int rstrindex(char source[], char searchfor[]);

char pattern[] = "ould";   /* pattern to search for */

/* find all lines matching pattern */
int main()
{
  char line[MAXLINE];
  int found = 0;
  while (getlinealt(line, MAXLINE) > 0)
    if (lstrindex(line, pattern) >= 0) {
      printf("%s\n", line);
      printf("Left index: %d\n", lstrindex(line, pattern));
      printf("Right index: %d\n", rstrindex(line, pattern));
      found++; }
  return found;
}

/* getlinealt:  get line into s, return length
   alt as defined in stdio*/
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

/* lstrindex:  return index of t in s, −1 if none */
int lstrindex(char s[], char t[])
{
  int i, j, k;
  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k]!='\0' &s[j]==t[k]; j++, k++)
      ;
    if (k > 0 &t[k] == '\0')
      return i;
  }
  return -1;
}

int rstrindex(char s[], char t[])
{
  int i, j, k;
  int lastIndex = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k]!='\0' &s[j]==t[k]; j++, k++)
      ;
    if (k > 0 &t[k] == '\0')
      lastIndex = i;
  }
  return lastIndex;
}

