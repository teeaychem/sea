#include <stdio.h>

#define IN 1
#define OUT 0

int main() {

  int i, j, c, wc, state, old_wl, new_wl, max_wl;

  wc = max_wl = old_wl = 0;
  new_wl = 2;
  int wl[new_wl];
  state = OUT;

  for (i = old_wl; i < new_wl; ++i) {
    wl[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      if (state == IN) {
	state = OUT;

	if (wc >= new_wl) { /* extend the array if needed */
	  old_wl = new_wl;
	  new_wl = wc;
	  for (i = old_wl; i < new_wl; ++i) {
	    wl[i] = 0;
	  }
	}

	++wl[wc - 1];
	wc = 0;
      }
    } else {
      state = IN;
      ++wc;
    }
  }

  /* figure out max word length could
     be done while building but assume
     fewer lengths than words
  */
  for (i = 0; i < new_wl; ++i) {
    if (wl[i] > max_wl) {
      max_wl = wl[i];
    }
  }

  /* make histogram.
     go from the max length down and print
     a bar if count exceeds current
  */
  for (i = max_wl; i >= 0; --i) {
    for (j = 0; j < new_wl; ++j) {
      if (wl[j] > i) {
	printf(" | ");
      } else {
	printf("   ");
      }
    }
    printf("\n");
  }
  /* finish off with integer */
  for (j = 1; j <= new_wl; ++j) {
    printf(" %d ", j);
  }
  printf("\n");
}
