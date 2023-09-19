  #include <stdio.h>

  int main() {

    int i, j, c, max_wl;

    max_wl = 0;

    int wl[26];

    for (i = 0; i < 26; ++i) {
      wl[i] = 0;
    }

    while ((c = getchar()) != EOF) {
      if (c >= 'a' && c <= 'z') {
	++wl[c - 'a'];
      }
    }

    for (i = 0; i < 26; ++i) {
      if (wl[i] > max_wl) {
	max_wl = wl[i];
      }
    }

    printf("\n");
    for (i = max_wl - 1; i >= 0; --i) {
      printf(" %3d ", i);
      for (j = 0; j < 26; ++j) {
	if (wl[j] > i) {
	  printf(" | ");
	} else {
	  printf("   ");
	}
      }
      printf("\n");
    }
    printf("     ");
    for (j = 0; j < 26; ++j) {
      printf(" %c ", j + 'a');
    }
    printf("\n");
    }
