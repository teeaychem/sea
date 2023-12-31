#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  void test_strcat_ptr(void);
  void test_strcat_book(void);
  void test_strend(void);
  void test_whu(char *s, int n);
  void test_strncpy_ptr();
  void test_strncmp_ptr();
  void test_reverse_ptr();
  int char_tail(int argc, char *argv[]);

  /* test_strcat_ptr(); */

  /* test_strcat_book(); */

  /* test_strend(); */

  /* test_whu("this is a very long string", 5); */
  /* test_whu("short", 10); */
  /* test_whu("bepop bepop bepop", 4); */

  /* test_strncpy_ptr(); */

  /* test_strncmp_ptr(); */

  /* test_reverse_ptr(); */

  char_tail(argc, argv);

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

void test_whu(char *s, int n)
{
  int whu(char *from, char *to, int n);

  char to[n];

  printf("Testing: whu\n");

  printf("Initial string: %s\n", s);
  printf("Size of to: %d\n", n);

  int i = whu(s, to, (n - 1));

  printf("Result of whu:\n\tto:\t%s\n\ti:\t%d\n", to, i);

  printf("Reconstructed:\n\t\t");
  for (int j = i; j < (i + n - 1) && to[j % (n - 1)] != '\0'; j++) {
    printf("%c", to[j % (n - 1)]);
  }
  printf("\n");
}

int char_tail(int argc, char *argv[])
{
  int c;
  int n = 10;

  while (--argc > 0 && (*++argv)[0] == '-') {
    c = *++argv[0]; /* just check the first char after - */
    switch (c) {
    case 'n':
      n = atoi(*++argv) + 1; /* next arg specifies number */
      --argc;
      break;
    default:
      printf("illegal option %c\n", c);
      break;
    }
  }

  char to[n];
  int whu(char *from, char *to, int n);

  int i = whu(argv[0], to, n);

  for (int j = i; j < (i + n - 1) && to[j % n] != '\0'; j++) {
    printf("%c", to[j % n]);
  }
  printf("\n");

  return 0;
}

/* func to test a pointer arithmetic idea
 basically, this stores the last n chars of from in to
 and returns the index of where to start reading to from
 in order to reconstruct */
int whu(char *from, char *to, int n)
{
  int i = 0;
  while (*from != '\0') {
    (*(to + (i++ % n)) = *from);
    from++;
    /* for (int i = 0; i < n; i++)
       printf("%c", to[i]);
       printf("\n"); */
  }
  *(to + i++) = '\0';
  if (i > n)
    return i % n;
  else
    return 0;
}

void test_strncpy_ptr()
{
  printf("\nTesting: strncpy\n");
  void strncpy_ptr(char *s, char *t, int n);

  int n = 5;
  // int n = 20;
  char s[n]; // ensure s is big enough
  char t[] = "Hello, world";
  //char t[] = "Hi!";

  strncpy_ptr(s, t, n);

  printf("\tStrings:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);
}

/* copy at most n chars of t to s */
void strncpy_ptr(char *s, char *t, int n)
{
  while ((*s++ = *t++) != '\0' && --n > 0)
    ;
}

/* concatenate n chars of t to end of s  */
void strncat_ptr(char *s, char *t, int n)
{
  while (*s != '\0') /* find the end of s */
    s++;

  while ((*s++ = *t++) != '\0' && --n > 0) /* copy n of t */
    ;
}

void test_strncmp_ptr()
{
  int strncmp_ptr(char *s, char *t, int n);
  int n;
  char s[] = "abcde";
  char t[] = "abcdf";

  printf("\tStrings:\n"
	 "\ts:\t%s\n"
	 "\tt:\t%s\n", s, t);

  n = 4;
  printf("What's the lexicographic order between s and t given %d chars? %d\n",
	 n, strncmp_ptr(s, t, n));
  n = 5;
  printf("What's the lexicographic order between s and t given %d chars? %d\n",
	 n, strncmp_ptr(s, t, n));
}

/* negative, zero, or positive for s < t, s == t, s > t */
int strncmp_ptr(char *s, char *t, int n)
{
  for ( ; *s == *t && --n > 0; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

/* reverse: reverse string s in place */
void reverse_arr(char s[])
{
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}


void test_reverse_ptr()
{
  void reverse_ptr(char *s);

  char s[] = "Hello";

  printf("\tString:\n"
	 "\ts:\t%s\n", s);

  reverse_ptr(s);

  printf("Reversed:\n"
	 "\tt:\t%s\n", s);
}


/* reverse: reverse string s in place */
void reverse_ptr(char *s)
{
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = c;
  }
}


