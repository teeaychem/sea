  #include <stdio.h>

int val;
char c;

int main() {
  val = ((c = getchar()) != EOF);
  printf("%d", val);
}
