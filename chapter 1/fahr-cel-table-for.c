#include <stdio.h>

/*
  make a Fahrenheit-Celcuis table
 */

int main() {
  /* int fahr, celsius; */
  float celsius, fahr;

  printf("To begin, some fahrenheit\n");
  celsius = 0;

  /*
    No restriction on test condition. But need everything initialised.
    So, test before first instance, allowing to skip entirely.
  */
  for (fahr = 212; celsius >= 0; fahr = fahr - 20) {

    celsius = (5 * (fahr - 32)) / 9.0;
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
  }

  printf("And now, for some celcuis\n");

  for (celsius = 100; celsius >= 0; celsius = celsius - 5) {
    fahr = ((celsius * 9) / 5.0) + 32;
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
  }
}
