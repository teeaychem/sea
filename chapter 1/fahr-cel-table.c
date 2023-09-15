#include <stdio.h>

/*
  make a Fahrenheit-Celcuis table
 */

int main() {
  /* int fahr, celsius; */
  float celsius, fahr; /* no need to convert fahr to float if div by float
			  and saving result to float, but as converting both ways
			  want float for both */
  int lower, fUpper, cUpper, fStep, cStep; /* separate ints for f and c tasks */

  lower = 0;

  fUpper = 300;
  fStep = 20;

  cUpper = 100;
  cStep = 5;

  fahr = lower;
  while (fahr <= fUpper) {
    celsius = (5 * (fahr - 32)) / 9.0; /* integer division truncates */
    /* printf("%d\t%d\n", fahr, celsius); /\* \t for tab *\/ */
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
    fahr = fahr + fStep;
  }

  celsius = lower;
  while (celsius <= cUpper) {
    fahr = ((celsius * 9) / 5.0) + 32;
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
    celsius = celsius + cStep;
  }
}
