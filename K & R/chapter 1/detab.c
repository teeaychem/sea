#include <stdio.h>

#define STOPDIST 3

int main()
{

  int afterTab = 0;
  char c;

  while ((c = getchar()) != EOF) {

    if (c == '\t') {
      for (int i = STOPDIST - afterTab; i > 0; i--) {
	putchar(' ');
      }
      afterTab = 0;
    }
    else {
      putchar(c);
      if (c == '\n') {
	afterTab = 0;
      } else {
	afterTab = ((afterTab + 1) % STOPDIST);
      }
    }
  }

  return 0;
}
