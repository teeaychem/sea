#include <stdio.h>

int val;
char c;

int main() {
  val = ((c = getchar()) != EOF);
  printf("You entered %c\n" , c);
  printf("Testing whether %c is not equal to EOF returns %d\n", c, val);

  printf("Also, if we try to print EOF the result is:\n");
  printf("%c - with c\n", EOF);
  printf("%d - with d\n", EOF);
  printf("Goodbye!\n", EOF);
}
