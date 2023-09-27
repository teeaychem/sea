#include <stdio.h>
#include <string.h>

/* convert a string of hexadecimal digits to integer value */

double htoi(char s[]);
double power(double n, double m);

int main()
{
  char hexString[] = "854765aa";
  htoi(hexString);

  printf("%f\n", htoi("854765aa"));
  printf("%f\n", htoi("0x854765aa"));
  printf("%f\n", htoi("0X854765aa"));
  return 0;
}

double htoi(char s[])
{
  double hexInt = 0;

  unsigned long hexLength = strlen(s);
  unsigned long i = 0;

  double hexExp = hexLength - 1;

  // adjust start and initial exponent if optional 0x/0X
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    i = 2;
    hexExp -= 2;
  }

  // covert char to int and then raise to relevant exponent
  for ( ; i < hexLength; i++) {
    char c = s[i];
    int j = 0;
    if (c >= '0' && c <= '9') {
      j = c - '0';
    }
    else if (c >='a' && c <= 'f') {
      j = c - 'a' + 10;
    }
    else if (c >='A' && c <= 'F') {
      j = c - 'A' + 10;
    }
    else {
      printf("error, not a valid hex number");
    }
    hexInt += power(16, hexExp) * j;
    --hexExp;
  }
  return hexInt;
}

/* basic power func */
double power(double n, double m)
{
  if (m == 0) {
    return 1;
  }
  else {
    double base = n;
    for (int i = 1; i < m; i++) {
      base *= n;
    }
    return base;
  }
}
