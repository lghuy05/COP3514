#include <stdio.h>

#include "read_line.h"

/* Reads a line of input and leaves room for the null character. */
void read_line(char str[], int n) {
  int ch, i = 0;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (i < n - 1)
      str[i++] = ch;
  }
  str[i] = '\0';
}
