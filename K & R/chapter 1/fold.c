  #include <stdio.h>

  #define CWIDTH 5

  int countText(char text[]);
  void fold(char input[]);
  void shiftCharsLeft(char s[], int sLength, int from, int spaces);

  int main()
  {
    char t[] = "This is a piece of text with some extrodinarily long words";
    printf("%s\n", t);
    printf("Folded to width %d:\n", CWIDTH);
    fold(t);

    return 0;
  }

  void fold(char input[])
  {

    char lineBuffer[CWIDTH];
    int bufferIndex = 0;
    int lastSpace = -1;

    int inputLength =  countText(input);

    for (int i = 0; input[i] != '\0'; i++) {

      // skip any initial spaces
      if (bufferIndex == 0 && input[i] == ' ') { ++i; }

      // copy current char and make not if empty
      if (input[i] == '\t') {
	lineBuffer[bufferIndex] = ' ';
      } else {
      lineBuffer[bufferIndex] = input[i];
      }
      if (input[i] == ' ') {
	lastSpace = bufferIndex;
      }
      ++bufferIndex;

      // when buffer is full
      if (bufferIndex == CWIDTH) {

	// if space was found
	if (lastSpace > 0) {
	  // display until spacea
	  for (int j = 0; j < lastSpace; j++) {
	    putchar(lineBuffer[j]);
	  }
	  putchar('\n');
	  // move everything after to front of buffer
	  shiftCharsLeft(lineBuffer, CWIDTH, lastSpace + 1, lastSpace + 1);
	  // point to after everything just moved for next char
	  bufferIndex = CWIDTH - (lastSpace + 1);
	  lastSpace = -1;
	}
	// if full and space or newline next ignore these.
	else if ((i + 1) < inputLength && ((input[i + 1] == ' ') || (input[i + 1] == '\n'))) {
	  for (int j = 0; j < CWIDTH; j++) {
	    putchar(lineBuffer[j]);
	  }
	  putchar('\n');
	  lastSpace = -1;
	  bufferIndex = 0;
	}
	else if ((i + 1) == inputLength) {
	  // skip as empty buffer at end
	}
	// need to break the word.
	else {
	  // print as much as possible leaving room...
	  for (int j = 0; j < (CWIDTH - 1); j++) {
	    putchar(lineBuffer[j]);
	  }
	  // for a hyphen.
	  putchar('-');
	  putchar('\n');
	  // keep leftover char
	  shiftCharsLeft(lineBuffer, CWIDTH, (CWIDTH - 1), (CWIDTH - 1));
	  bufferIndex = 1;
	  lastSpace = -1;
	}
      }
    }
    // display anything remaining in buffer
    for (int j = 0; j < CWIDTH; j++) {
      putchar(lineBuffer[j]);
    }
    putchar('\n');
  }

  int countText(char text[]) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {}
    return i;
  }

  void shiftCharsLeft(char s[], int sLength, int from, int spaces)
  {
    for (int i = from; i < sLength; i++) {
      s[i - spaces] = s[i];
    }
    // cleanup
    for (int i = sLength - from; i < sLength; i++) {
      s[i] = '\0';
    }
  }
