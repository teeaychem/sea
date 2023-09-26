#include <stdio.h>

#define MAXLINE 30

int reverse(char s[]);

int main()
{

  char c;
  char stringStore[MAXLINE];
  for (int i = 0; i < MAXLINE; i++) { stringStore[i] = '\0'; }
  int pos = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      reverse(stringStore);
      printf("%s\n", stringStore);
      for (int i = 0; i < MAXLINE; i++) {
	stringStore[i] = '\0';
      }
      pos = 0;
    }
    else {
      stringStore[pos] = c;
      ++pos;
    }
  }

  return 0;
}

int reverse(char s[])
{
  int left = 0;
  int right = 0;
  char swap;

  for (right = 0; s[right] != '\0'; right++) {}

  --right;

  while (right - left > 0) {
    swap = s[left];
    s[left] = s[right];
    s[right] = swap;
    ++left;
    --right;
  }

  return 1;
}

