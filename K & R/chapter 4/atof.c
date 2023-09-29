#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
double pw(double n, double m);

int main(void)
{
  char ns[]= "321.32";
  printf("String:\t%s\n"
	 "Float:\t%f\n", ns, atof(ns));

  char sns[]= "1.8e-01";
  printf("String:\t%s\n"
	 "Float:\t%g\n", sns, atof(sns));

  char sns2[]= "1.8e10";
  printf("String:\t%s\n"
	 "Float:\t%g\n", sns2, atof(sns2));

  char sns3[]= "1.8e+10";
  printf("String:\t%s\n"
	 "Float:\t%g\n", sns3, atof(sns3));

}

/* atof:  convert string s to double */
double atof(char s[])
{
  double val, power;
  int i, sign;
  int pluse;
  double e;

  for (i = 0; isspace(s[i]); i++)  /* skip white space */
    ;

  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
           i++;

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  if (s[i] == 'e' || s[i] == 'E') {
    ++i;
    pluse = (s[i] == '-') ? 0 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (e = 0; isdigit(s[i]); i++)
      e = 10 * e + (s[i] - '0');
    e = pw(10, e);
    if (pluse) {
      val *= e;
    } else {
      power *= e;
    }
  }

  return sign * val / power;
}

/* basic power func */
double pw(double n, double m)
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
