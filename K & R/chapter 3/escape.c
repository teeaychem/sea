#include <stdio.h>
#include <string.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
  char original[] = "Hello!\n\tThis is a test.";
  char copy[2 * strlen(original)]; // doulbe as may need to make every char explicit
  char backAgain[2 * strlen(original)]; // doulbe as may need to make every char explicit
  printf("%s\n", backAgain);

  escape(copy, original);
  unescape(backAgain, copy);

  printf("Original:\n\n");
  printf("%s\n\n", original);
  printf("Copy:\n\n");
  printf("%s\n\n", copy);
  printf("Back again:\n\n");
  printf("%s\n\n", backAgain);

  return 0;
}


void escape(char s[], char t[])
{
  int i = 0;
  int j = 0;

  while (t[i] != '\0') {

    switch (t[i]) {
    case '\t':
      s[j] = '\\';
      ++j;
      s[j] = 't';
      break;
    case '\n':
      s[j] = '\\';
      ++j;
      s[j] = 'n';
      break;
    default:
      s[j] = t[i];
    }
    ++j;
    ++i;
  }
  s[j] = '\0';
}

void unescape(char s[], char t[])
{
  int i = 0;
  int j = 0;

  while (t[i] != '\0') {
    if (t[i] == '\\') {
      switch (t[i + 1]) {
      case 't':
	s[j] = '\t';
	++i;
	break;
      case 'n':
	s[j] = '\n';
	++i;
	break;
      default:
	s[j] = t[j];
      }
      ++i;
      ++j;
    } else {
      s[j] = t[i];
      ++i;
      ++j;
    }
  }
  s[j] = '\0';
}
