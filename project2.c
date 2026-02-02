#include <stdio.h>

void ascii_stream_analyzer(void) {
  int c;

  while (1) {
    /* Print prompt (NO extra blank line here) */
    printf("Enter 1 or more characters then ENTER:\n");
    printf("(NOTE: a character # will exit the program):\n");

    int first_block_in_line = 1; // controls blank line after prompt
    int printed_any_block = 0;   // did we print at least one block this line?

    while ((c = getchar()) != EOF) {

      if (c == '#') {
        return; // exit immediately (no extra blank line for CASE #1)
      }

      if (c == '\n') {
        /* End of this input line */
        if (printed_any_block) {
          printf("\n"); // blank line BEFORE next prompt (needed for CASE #10)
        }
        break; // go re-prompt
      }

      /* We are going to print a block now */
      if (first_block_in_line) {
        printf("\n"); // blank line AFTER prompt, but only if we print a block
        first_block_in_line = 0;
      } else {
        printf("\n"); // blank line BETWEEN character blocks
      }

      printed_any_block = 1;

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
