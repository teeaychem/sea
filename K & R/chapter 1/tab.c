#include <stdio.h>

#define STOPDIST 4

void detab(void);
void entab(void);

int main()
{

  // detab();
  entab();

  return 0;
}

void detab(void)
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
}

void entab(void)
{

  int spacesSeen = 0;
  int afterTab = 0;
  char c;

  while ((c = getchar()) != EOF) {

    if (c == ' ') {
      ++spacesSeen;
      if ((afterTab + spacesSeen) == STOPDIST) {
	putchar('\t');
	afterTab = 0;
	spacesSeen = 0;
      }
    }
    else {
      while (spacesSeen > 0) {
	putchar(' ');
	--spacesSeen;
	++afterTab;
      }
      putchar(c);
      ++afterTab;

      afterTab = afterTab % STOPDIST;
    }
  }
}
