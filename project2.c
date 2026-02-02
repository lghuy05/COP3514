#include <stdio.h>

void ascii_stream_analyzer() {

  int c;
  printf("Enter 1 or more characters then ENTER:\n");
  printf("(NOTE: a character # will exit the program):\n");
  printf("\n");

  do {
    c = getchar();
    if (c == '\n') {
      continue;
    } else if (c == '#') {
      break;
    }
    printf("You typed: '%c' (ASCII %d)\n", c, c);
    if (c >= 97 && c <= 122) {
      printf("Class: Lowercase Letter\n");
      c -= 32;
      printf("Converted to: '%c'\n", c);
    } else if (c >= 65 && c <= 90) {
      printf("Class: Uppercase Letter\n");
      c += 32;
      printf("Converted to: '%c'\n", c);
    }
  } while (c != '#' && c != EOF);
}

int main(void) {
  ascii_stream_analyzer();
  return 0;
}
