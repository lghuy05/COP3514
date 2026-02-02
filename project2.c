/*
Name: Yui Luong
UID: U09662268

Description:
This program reads characters from standard input one at a time and analyzes
their ASCII values. For each valid character entered, the program displays
the character, its ASCII code, and its classification (uppercase letter,
lowercase letter, digit, printable symbol, or non-printable/extended ASCII).

Lowercase letters are converted to uppercase, and uppercase letters are
converted to lowercase. Digits and symbols are not converted.

The program processes input line by line. After the user presses ENTER, the
prompt is displayed again. The program terminates immediately when the user
enters the '#' character.
*/

#include <stdio.h>

void ascii_stream_analyzer(void) {
  int c;

  /* Outer loop: repeats for each input line */
  while (1) {
    // prompt
    printf("Enter 1 or more characters then ENTER:\n");
    printf("(NOTE: a character # will exit the program):\n");

    // these awkward only for passing the testcases
    /*
       first_block_in_line:
       - Used to control spacing after the prompt.
       printed_any_block:
       - Tracks whether at least one character block was printed
         on the current input line.
    */
    int first_block_in_line = 1;
    int printed_any_block = 0;

    /* Inner loop: read characters one at a time */
    while ((c = getchar()) != EOF) {
      /* Exit program immediately if '#' is entered */
      if (c == '#') {
        return;
      }

      if (c == '\n') {
        /* End of this input line */

        if (printed_any_block) {
          /* Print a blank line before the next prompt
           only if output was printed on this line */
          printf("\n");
        }
        break;
      }

      // NOTE: a block is a valid input (not #, enter or EOF)

      /* Handle spacing between output blocks */
      if (first_block_in_line) {
        /* Blank line after prompt before first output block */
        printf("\n");
        first_block_in_line = 0;
      } else {
        /* Blank line between character output blocks */
        printf("\n");
      }

      printed_any_block = 1;
      /* Display character and ASCII value */
      printf("You typed: '%c' (ASCII %d)\n", c, c);

      /* Character classification and conversion */
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
