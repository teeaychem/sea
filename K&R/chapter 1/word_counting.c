#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_WL 5

  int main() {

    int i, j, c, wc, state, top_wf, top_wl;

    wc = top_wf = top_wl = 0;
    int wl[MAX_WL];
    state = OUT;

    for (i = 0; i < MAX_WL; ++i) {
      wl[i] = 0;
    }

    while ((c = getchar()) != EOF) {
      if (c == ' ' || c == '\t' || c == '\n') {
	if (state == IN) {
	  state = OUT;
	  if (wc <= MAX_WL) {
	    ++wl[wc - 1]; /* no need to count 0 */
	  }
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
    for (i = 0; i < MAX_WL; ++i) {
      if (wl[i] != 0) {
	top_wl = i + 1;
	if (wl[i] > top_wf) {
	  top_wf = wl[i];
	}
      }
    }

    /* make histogram.
       go from the max length down and print
       a bar if count exceeds current
    */
    for (i = top_wf; i >= 0; --i) {
      for (j = 0; j < top_wl; ++j) {
	if (wl[j] > i) {
	  printf("  |");
	} else {
	  printf("   ");
	}
      }
      printf("\n");
    }
    /* finish off with integer */
    for (j = 0; j < top_wl; ++j) {
      printf("%3d", j + 1);
    }
    printf("\n");
  }
