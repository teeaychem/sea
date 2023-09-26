#include <stdio.h>

#define MAXLINE 4

int cleanLine(int lim); /* getline is defined elsewhere */

/* print longest input line */
/* ^D in terminal to enter EOF. Useful: stty all  */

int main()
{
  cleanLine(MAXLINE);

  return 0;
}

int cleanLine(int lim)
{

  int blankTab[lim];
  for (int i = 0; i < lim; i++) {
    blankTab[i] = 0;
  }

  int c;
  int bti = 0; // position for blank (even) /tab (odd)

  while ((c = getchar()) != EOF) {

    if (c == '\n') {
      // remove blanks
      for (int i = 0; i < lim; i++) {
	blankTab[i] = 0;
      }
      putchar('\n');
      bti = 0;
    }
    else if (c == ' ' && bti < lim) {
      // blank so check index is even
      if (bti % 2 == 1) {
	++bti;
      }
      blankTab[bti] += 1;
    }
    else if (c == '\t' && bti < lim) {
      // tab so
      if (bti % 2 == 0) {
	++bti;
      }
      blankTab[bti] += 1;
    }
    // character case
    else {
      for (int j = 0; j < (bti + 1); j++) {
	if (j % 2 == 0) {
	  for (int k = 0; k < blankTab[j]; k++) {
	    putchar(' ');
	  }
	}
	else if (j % 2 == 1) {
	  for (int k = 0; k < blankTab[j]; k++) {
	    putchar('\t');
	  }
	}
	blankTab[j] = 0;
      }
      putchar(c);
      bti = 0;
    }
  }
  return 1;
}
