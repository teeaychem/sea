#include <stdio.h>

int main(void)
{
  void test_strcat_ptr(void);
  void test_strcat_book(void);
  void test_strend(void);

  test_strcat_ptr();

  test_strcat_book();

  test_strend();

  return 0;
}

void test_strcat_ptr(void)
{
  printf("\nTesting: strcat_ptr\n");
  void strcat_ptr(char *s, char *t);
  char s[15] = "Hello, "; // ensure s is big enough
  char t[5] = "world";

  printf("\tBefore strcat_ptr:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);

  strcat_ptr(s, t);

  printf("\tAfter strcat_ptr:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);
}

/* strcat_ptr: concatenate t to end of s using pointers; s must be big enough */
void strcat_ptr(char *s, char *t)
{
  while (*s != '\0') /* find the end of s */
    s++;

  while ((*s++ = *t++) != '\0') /* copy t */
    ;
}

void test_strcat_book(void)
{
  void strcat_book(char s[], char t[]);

  printf("\nTesting: strcat_book\n");

  char s[15] = "Hello, ";
  char t[5] = "world";

  printf("\tBefore strcat_book:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);

  strcat_book(s, t);

  printf("\tAfter strcat_book:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);
}


/* strcat: concatenate t to end of s; s must be big enough */
void strcat_book(char s[], char t[])
{
  int i, j;
  i = j = 0;
  while (s[i] != '\0') /* find end of s */
    i++;
  while ((s[i++] = t[j++]) != '\0') /* copy t */
    ;
}

void test_strend(void)
{
  printf("\nTesting: strend\n");
  void strcat_ptr(char *s, char *t);
  int strend(char *s, char *t);
  char s[15] = "Hello, "; // ensure s is big enough
  char t[5] = "world";

  strcat_ptr(s, t);

  printf("\tStrings:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);

  printf("\tIs t is at the end of s? %d\n", strend(s, t));
  printf("\tIs s is at the end of t? %d\n", strend(t, s));
}

/* strend: return 1 if t is at the end of s, 0 otherwise */
int strend(char *s, char *t)
{
  int slen = 0;
  int tlen = 0;

  while (*s != '\0') { /* find the end of s */
    s++;
    slen++;
  }

  while (*t != '\0') { /* find the end of s */
    t++;
    tlen++;
  }

  /* work backwards checking char equality */
  while (*s == *t && tlen >= 0 && slen >= 0) {
    s--;
    t--;
    slen--;
    tlen--;
  }

  /* return 1 only if walked back all of t */
  if (tlen == -1) {
    return 1;
  } else {
    return 0;
  }
}
