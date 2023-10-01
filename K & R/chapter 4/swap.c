#include <stdio.h>

#define swp(t,x,y) { t swap = x; x = y; y = swap; }

#define swap(t,x,y) { t c = x; t d = y; t swap = c; c = d; d = swap; x = c; y = d; }

int main()
{
  int x = 1;
  int y = 0;
  printf("x: %d y: %d\n", x, y);
  swap(int, x, y);
  printf("x: %d y: %d\n", x, y);

  int c = 1;
  int d = 0;
  printf("c: %d d: %d\n", c, d);
  swap(int, c, d);
  printf("c: %d d: %d\n", c, d);
  swp(int, c, d);
  printf("c: %d d: %d\n", c, d);

  int a = 432;
  int swap = 234;
  printf("a: %d b: %d\n", a, swap);
  swap(int, a, swap);
  printf("a: %d b: %d\n", a, swap);
}
