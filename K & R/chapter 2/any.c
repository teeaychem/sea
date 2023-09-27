#include <stdio.h>

int any(char s[], char t[]);
int containsStringChar(char s[], char c);

int main()
{
  char str1[] = "programming";
  char str2[] = "programming";

  any(str2, "rp");

  printf("%d\n", any(str2, str2));
  printf("%d\n", any(str2, "r"));
  printf("%d\n", any(str2, "i"));
  printf("%d\n", any(str2, "ue"));


  return 0;
}

int any(char s[], char t[])
{
  int j = -1;

  for (int i = 0; s[i] != '\0' && j == -1; i++)
    if (containsStringChar(t, s[i]))
      j = i;
  return j;
}

int containsStringChar(char s[], char c)
{
  int i = 0;
  char d;
  int found = 0;
  while ((d = s[i]) != '\0' && found != 1) {
    if (d == c)
      found = 1;
    ++i;
  }
  return found;
}
