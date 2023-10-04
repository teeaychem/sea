#include <stdio.h>

/*
  make a Fahrenheit-Celcuis table
 */

# define LOWER 0
# define FUPPER 212
# define FSTEP 20
# define CUPPER 100
# define CSTEP 7.532
/* No typing with symbolic constants… */

# define CLOSING_MSG "Goodbye!\n"
/*
  What's stored is determined.
  But, what about interpreting the bits?
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
  for (fahr = FUPPER; celsius >= LOWER; fahr = fahr - FSTEP) {

    celsius = (5 * (fahr - 32)) / 9.0;
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
  }

  printf("And now, for some celcuis\n");

  for (celsius = CUPPER; celsius >= LOWER; celsius = celsius - CSTEP) {
    fahr = ((celsius * 9) / 5.0) + 32;
    printf("%6.2f < c ~ f > %6.2f\n", celsius, fahr);
  }

  printf(CLOSING_MSG);
}
