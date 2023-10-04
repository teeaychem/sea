#include <stdio.h>

void shellsort(int v[], int n);
void printIntArray(int ints[], int l);

int main()
{
  const int l = 10;
  int ints[l] = {9, 7, 5, 3, 1, 2, 4, 6, 8};
  shellsort(ints, l);

}



/* shellsort: sort v[〇]...v[n-1]into increasing order */

void shellsort(int v[], int n)
{
  for (int gap = n / 2; gap > 0; gap /= 2) {
    printf("New gap: %d\n", gap);
    for (int i = gap; i < n; i++)
      for (int j = (i - gap); j >= 0 && v[j] > v[j + gap]; j -= gap) {
	printIntArray(v, n);
	int temp = v[j];
	v[j] = v[j + gap];
	v[j + gap] = temp;
      }
  }
}

void printIntArray(int ints[], int l)
{
  for (int i = 0; i < l - 1; i++)
    printf("%d, ", ints[i]);
  printf("%d\n", ints[l - 1]);
}


/*
  New gap: 5
  9, 7, 5, 3, 1, 2, 4, 6, 8, 0 // 9 vs 2, flip
  2, 7, 5, 3, 1, 9, 4, 6, 8, 0 // 7 vs 4, flip
  2, 4, 5, 3, 1, 9, 7, 6, 8, 0 // 5 vs 6, no flip, eventually 1 vs 0 flip and then new gap
  New gap: 2
  2, 4, 5, 3, 0, 9, 7, 6, 8, 1 // did 2 vs 5, condition failed, now 4 vs 3, flip
  2, 3, 5, 4, 0, 9, 7, 6, 8, 1 // from here, comparing two apart, e.g. 5 vs 0.
  2, 3, 0, 4, 5, 9, 7, 6, 8, 1 // most are ok, so i increases
  0, 3, 2, 4, 5, 9, 7, 6, 8, 1 // 9 vs 1
  0, 3, 2, 4, 5, 6, 7, 9, 8, 1 // and this goes all the way back now, given the innermost loop
  0, 3, 2, 4, 5, 6, 7, 1, 8, 9
  0, 3, 2, 4, 5, 1, 7, 6, 8, 9
  0, 3, 2, 1, 5, 4, 7, 6, 8, 9
  New gap: 1
  0, 1, 2, 3, 5, 4, 7, 6, 8, 9 // 0 vs 3, no flip, 3 vs 2 flip, 3 vs 1 flip and push 1 down.
  0, 1, 2, 3, 4, 5, 7, 6, 8, 9
 */
