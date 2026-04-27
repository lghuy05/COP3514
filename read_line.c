// Yui Luong
// UID: U09663368
// Description: Reads one line of input into a character array.
#include <stdio.h>

#include "read_line.h"

/* Reads characters until a newline and stores a null-terminated string. */
void read_line(char str[], int n) {
  int ch, i = 0;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (i < n - 1)
      str[i++] = ch;
  }
  str[i] = '\0';
}
