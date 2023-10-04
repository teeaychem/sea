#include <stdio.h>


int lower(int c);
int altLower(int c);
void putStringLower(char s[]);

int main()
{
  putStringLower("HELLO!\n"
		 "This is a quiet place, there is no SHOUTING here.\n");

  return 0;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

int altLower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}


void putStringLower(char s[])
{
  for (int i = 0; s[i] != '\0'; i++) {
    // putchar(lower(s[i]));
    putchar(altLower(s[i]));
  }
}
