#include <stdio.h>

int main() {

  long charCount;
  int lineCount, tabCount, blankCount, previousBlank, blanksLost, replacement;
  char c;

  charCount = 0;
  lineCount = 0;
  tabCount = 0;
  blankCount = 0;
  previousBlank = 0;
  blanksLost = 0;
  replacement = 0;

  while ((c = getchar()) != EOF) {

    replacement = 0;

    if (c == ' ') {
      ++blankCount;
      ++previousBlank;
    }
    else {
      if (c == '\n') {
	c = 'n';
	++lineCount;
	replacement = 2; /* special case to flag newline still needed */
      }
      if (c == '\t') {
	c = 't';
	++tabCount;
	replacement = 1;
      }
      if (c == '\\') {
	replacement = 1;
      }

      if (replacement > 0) {
	putchar('\\');
      }
      else {
	++charCount;
      }
      if (previousBlank > 1) {
	blanksLost = blanksLost + (previousBlank - 1);
      }
      previousBlank = 0;
    }

    if (previousBlank < 2) {
      putchar(c);
      if (replacement == 2) {
	putchar('\n');
      }
    }
  }

  printf("The text contained:\n");
  printf("%d lines\n", lineCount);
  printf("%d tabs\n", tabCount);
  printf("%d blank characters (%d were lost)\n", blankCount, blanksLost);
  printf("%ld (non-blank) characters\n", charCount);
  printf("Goodbye!\n");
}
