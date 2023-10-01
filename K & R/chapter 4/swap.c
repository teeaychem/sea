#include <stdio.h>

#define swp(t,x,y) { t swap = x; x = y; y = swap; }

int main()
{
  int x = 1;
  int y = 0;
  printf("x: %d y: %d\n", x, y);
  swp(int, x, y);
  printf("x: %d y: %d\n", x, y);

  double a = 432;
  double b = 643543534543656547 * 5;
  printf("a: %g b: %g\n", a, b);
  swp(double, a, b);
  printf("a: %g b: %g\n", a, b);
}
