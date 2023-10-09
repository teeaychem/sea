#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* store last n lines in buffer of ALLOCSIZE
 as always remove nth line free space by shifting start of buffer forward
 and looping to the start at the end */

/* setting aside storage is fine.
  splitting pointers from main is difficult.
  there's no way to do variable storage outside a function call
  so either set aside space for up to n pointers or keep some func alive */

/* To help reutrn the results allocbuf has an extra space at the end which
   each line pointer starts at.
   this allows to test whether line has been set.
*/

#define ALLOCSIZE 1023
static char allocbuf[ALLOCSIZE + 1];

int main(int argc, char *argv[])
{
  void read_args(int argc, char *argv[], int *n);
  int allocbuf_space(char *line_a, char *line_b);
  char *next_allocbuf(char *current_allocbuf);

  int line_ptrs = 5; // default number of line pointers
  read_args(argc, argv, &line_ptrs); // read arguments

  char *line_ptr_buf[line_ptrs]; // buffer for line pointers
  int lp_i = -1; // first run immediately sets to +1

  for (int i = 0; i < line_ptrs; i++)
    line_ptr_buf[i] = &allocbuf[ALLOCSIZE + 1];

  /* main loop.
     while c (char) isn't EOF
     if c is newline, update buffer stuff.
     else, so long as space then add to buffer.
  */

  char c;
  int available_space = ALLOCSIZE;
  char *allocbuf_ptr = allocbuf; // points to next available space
  char new_str = 1; // boolean for whether to store a new string

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      *allocbuf_ptr = '\0'; // end the string
      new_str = 1; // set new string on next char
    }
    else {
      if (new_str) { // take care of new string if needed
	// move allocbuf_ptr and lp_i forward
	allocbuf_ptr = next_allocbuf(allocbuf_ptr);
	lp_i = (lp_i + 1) % line_ptrs;
	// update new line
	line_ptr_buf[lp_i] = allocbuf_ptr;
	// space is from deleting next pointer.
	available_space = allocbuf_space(line_ptr_buf[lp_i],
					 line_ptr_buf[(lp_i + 1) % line_ptrs]);
	new_str = 0;
      }
      if (available_space > 0) { // store the char, ptr forward, reduce space.
	*allocbuf_ptr = c;
	allocbuf_ptr = next_allocbuf(allocbuf_ptr);
	--available_space;
      }
    }
  }

  printf("\n");
  for (int j = 1; j <= line_ptrs; j++) {
    if (line_ptr_buf[(lp_i + j) % line_ptrs] != &allocbuf[ALLOCSIZE + 1])
      // printf("%d: %s\n", j, line_ptr_buf[(lp_i + j) % line_ptrs]);
      printf("%s\n", line_ptr_buf[(lp_i + j) % line_ptrs]);
  }

  return 0;
}

/* could do with mod… */
char *next_allocbuf(char *current_allocbuf)
{
  if ((current_allocbuf - allocbuf) == (ALLOCSIZE - 1)) {
    return &allocbuf[0];
  }
  else {
    return current_allocbuf + 1;
  }
}

/* get available space after 'deleting' line a
   i.e. space from start of a to start of b */
int allocbuf_space(char *line_a, char *line_b)
{
  if (*line_b > *line_a)
    return *line_b - *line_a;
  else
    return ALLOCSIZE - (*line_a - *line_b);
}

void read_args(int argc, char *argv[], int *n)
{
  /* figure out how many lines to store */
  int c;
  while (--argc > 0 && (*++argv)[0] == '-') {
    c = *++argv[0]; /* just check the first char after - */
    switch (c) {
    case 'n':
      *n = atoi(*++argv); /* next arg specifies number */
      if (n < 0) {
	printf("can't do negative… ignoring the sign\n");
	*n = -1 * *n;
      }
      --argc;
      break;
    default:
      printf("illegal option %c\n", c);
      break;
    }
  }
}
