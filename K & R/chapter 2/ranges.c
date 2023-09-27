#include <stdio.h>
#include <limits.h>
#include <float.h>

#define DISPLAY_LIMITS 1

int main() {

  double dbl = 1;
  float max = 1;

  while ((dbl + 1) == (float) (max + 1)) {

    double j = 1;

    while (((dbl + (j * 2)) == (float) (max + (j * 2))) ) { j = j * 2; }

    dbl = dbl + j;
    max = max + j;
  }

  dbl = 1;
  float min = 1;

  while ((dbl - 1) == (float) (min - 1)) {

    double j = 1;

    while ((dbl - (j * 2)) == (float) (min - (j * 2))) { j = j * 2; }

    dbl = dbl - j;
    min = min - j;
  }

  printf("%f\n", max);
  printf("%f\n", max + 1);
  printf("\nFinal results:\n \tMax: %f\n \tMin: %f\n", max, min);

  if (DISPLAY_LIMITS) {
    printf("Char:\n");
    printf("\tMax: %d\n", CHAR_MAX);
    printf("\tMin: %d\n", CHAR_MIN);

    printf("Int:\n");
    printf("\tMax: %d\n", INT_MAX);
    printf("\tMin: %d\n", INT_MIN);

    printf("Short:\n");
    printf("\tMax: %d\n", SHRT_MAX);
    printf("\tMin: %d\n", SHRT_MIN);

    printf("Long:\n");
    printf("\tMax: %ld\n", LONG_MAX);
    printf("\tMin: %ld\n", LONG_MIN);

    printf("Float:\n");
    printf("\tMax: %f\n", FLT_MAX);
    printf("\tMin: %f\n", FLT_MIN);

    printf("Double:\n");
    printf("\tMax: %g\n", DBL_MAX);
    printf("\tMin: %g\n", DBL_MIN);
  }
}
