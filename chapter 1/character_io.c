#include <stdio.h>

int main() {

  long charCount;
  int lineCount, tabCount, blankCount;
  char c;

  charCount = 0;
  lineCount = 0;
  tabCount = 0;
  blankCount = 0;

  while ((c = getchar()) != EOF) {

    if (c == '\n') {
      ++lineCount;
    }
    else if (c == ' ') {
      ++blankCount;
    }
    else if (c == '\t') {
      ++tabCount;
    }
    else {
      ++charCount;
    }
  }

  printf("The text contained:\n");
  printf("%d lines\n", lineCount);
  printf("%d tabs\n", tabCount);
  printf("%d blank characters\n", blankCount);
  printf("%ld (non-blank) characters\n", charCount);
  printf("Goodbye!\n");
}
