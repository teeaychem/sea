#include <stdio.h>

/*
  make a Fahrenheit-Celcuis table using functions.
  toFahrenheit and toCelcius are simple.
  printTable may need some revision.
  On current understanding, pass functions by pointers to function.
  Explicitly passing address seems optional, same for notating converter as a pointer.
 */

# define CLOSING_MSG "Goodbye!\n"

float toFahrenheit(float celsius);
float toCelcius(float fahrenheit);
void printTable( float (*converter)(float), char[], char[], int, int, int);

int main() {
  /* int fahr, celsius; */
  printf("To begin, some fahrenheit\n");

  printTable(&toCelcius, "F", "C", 0, 212, 20);

  printf("And now, for some celcuis\n");

  printTable(&toFahrenheit, "C", "F", 0, 100, 10);

  printf(CLOSING_MSG);
}

float toFahrenheit(float celsius) { return ((celsius * 9) / 5.0) + 32; }

float toCelcius(float fahrenheit) { return (5 * (fahrenheit - 32)) / 9.0; }

void printTable(float (*converter)(float), char unitA[], char unitB[], int lower, int upper, int step) {

  for (int i = upper; i >= lower; i = i - step) {
    printf("%6.2f < %s ~ %s > %6.2f\n", (float) i, unitA, unitB, (*converter)(i));
  }
}
