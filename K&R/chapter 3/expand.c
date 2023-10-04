#include <stdio.h>
#include <string.h>

void expand(char s1[], char s2[]);
int twoAlphOrNum(char a, char b);

int main()
{
  char s1[] = "testing a-c0-3 and then a-f perhaps A-Y but not- nor -eh nor a-3 careful with a-a and then carry on";
  char s2[150];

  expand(s1, s2);

  printf("Results:\n");
  printf("\t%s\n", s1);
  printf("\t%s\n", s2);
  return 0;
}

void expand(char s1[], char s2[])
{
  int s1i = 0;
  int s2i = 0;

  // copy first and last outside of loop
  // length doesn't matter, as at worst this is \0.
  s2[s2i] = s1[s1i];
  ++s1i;
  ++s2i;

  for (int j = strlen(s1) - 1; s1i < j; s1i++) {
    printf("s1i: %d, char: %c\n", s1i, s1[s1i]);
    // know before and after are safe to check
    if (s1[s1i] == '-' && twoAlphOrNum(s1[s1i - 1], s1[s1i + 1])) {
      if (s1[s1i - 1] == s1[s1i + 1]) {
	++s1i;
      } else {
	for (int k = s1[s1i - 1] + 1; k < s1[s1i + 1]; k++, s2i++) {
	  s2[s2i] = k;
	}
      }
    }
    else {
      s2[s2i] = s1[s1i];
      ++s2i;
    }
  }

  s2[s2i] = s1[s1i];
  ++s1i;
  ++s2i;
  s2[s2i] = '\0';
}

int twoAlphOrNum(char a, char b)
{
  printf("Comparing %c and %c\n", a, b);
  if (('a' <= a && a <= 'z') && ('a' <= b && b <= 'z'))
    return 1;
  else if (('A' <= a && a <= 'Z') && ('A' <= b && b <= 'Z'))
    return 1;
  else if (('0' <= a && a <= '9') && ('0' <= b && a <= '9'))
    return 1;
  return 0;
}
