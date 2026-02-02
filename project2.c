#include <stdio.h>

void ascii_stream_analyzer(void) {
  int c;

  while (1) {
    /* Prompt */
    printf("Enter 1 or more characters then ENTER:\n");
    printf("(NOTE: a character # will exit the program):\n\n");

    int first = 1; // controls blank lines between character blocks

    while ((c = getchar()) != EOF) {

      if (c == '\n') {
        break; // new line → re-prompt
      }

      if (c == '#') {
        return; // exit program immediately
      }

      if (!first) {
        printf("\n"); // blank line BETWEEN blocks only
      }
      first = 0;

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
    }
  }
}

int main(void) {
  ascii_stream_analyzer();
  return 0;
}
