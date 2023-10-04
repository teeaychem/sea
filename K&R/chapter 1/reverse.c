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

/* P.S. The func given in the book in S3.6 tidies this up.
   It's in the comments below. Notes contrast. */
int reverse(char s[])
{
  int left = 0; // i
  int right = 0; // j
  char swap; // c

  for (right = 0; s[right] != '\0'; right++) {} // Simple way to get strlen

  --right; // Now right = strlen(s) - 1.

  while (right - left > 0) { //  left < right is more elegant
    swap = s[left]; // same switch procedure
    s[left] = s[right];
    s[right] = swap;
    ++left; // updates are placed in the for loop
    --right;
  }

  return 1;
}

/* reverse from S3.6
void reverse(char s[])
{
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
*/
