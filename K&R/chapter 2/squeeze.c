#include <stdio.h>

void squeezeChar(char s[], int c);
void squeezeString(char s[], char t[]);
int containsStringChar(char s[], char c);

int main()
{
  char str1[] = "programming";
  char str2[] = "programming";

  squeezeChar(str1, 'r');
  squeezeString(str2, "rp");

  printf("%s\n", str1);
  printf("%s\n", str2);

  squeezeString(str2, str2);

  printf("%s\n", str2);

  return 0;
}


/* squeezeChar: delete all c from s */
void squeezeChar(char s[], int c)
{
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}


void squeezeString(char s[], char t[])
{
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
    if (!containsStringChar(t, s[i]))
      s[j++] = s[i];
  s[j] = '\0';
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
