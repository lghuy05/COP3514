#include <stdio.h>

void ascii_stream_analyzer() {

  int c;
  printf("Enter 1 or more characters then ENTER:\n");
  printf("(NOTE: a character # will exit the program):\n");

  do {
    c = getchar();
    if (c == '\n') {
      continue;
    } else if (c == '#') {
      break;
    }
    printf("You typed: '%c' (ASCII %d)\n", c, c);

    if (c >= 'a' && c <= 'z') {
      printf("Class: Lowercase Letter\n");
      printf("Converted to: '%c'\n", c - 32);

    } else if (c >= 'A' && c <= 'Z') {
      printf("Class: Uppercase Letter\n");
      printf("Converted to: '%c'\n", c + 32);

    } else if (c >= '0' && c <= '9') {
      printf("Class: Digit\n");
      printf("No conversion done\n");

    } else if (c >= 32 && c <= 126) {
      printf("Class: Printable Symbol\n");
      printf("No conversion done\n");

    } else {
      printf("Class: Non-printable or extended ASCII\n");
      printf("No conversion done\n");
    }

  } while (c != '#' && c != EOF);
}

int main(void) {
  ascii_stream_analyzer();
  return 0;
}
