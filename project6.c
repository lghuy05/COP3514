/*
Name: Yui Luong
UID: U09663368
Description:
Given an input array, create an output array by summing the first and last
elements, the second and second-to-last elements, and so on. If the input
array has an odd length, copy the middle element as the last output value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 64
#define READ_CHUNK_SIZE 30

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Usage: ./a.out <input filename> <output file size>\n");
    return 1;
  }

  int chunk_size = atoi(argv[2]);
  if (chunk_size <= 0) {
    printf("Error: 2nd argument must be a positive integer.\n");
    return 2;
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Error opening input file '%s'\n", argv[1]);
    return 3;
  }

  char buffer[READ_CHUNK_SIZE];
  char filename[MAX_SIZE_FILENAME];

  FILE *output = NULL;

  int line_count = 0;
  int file_index = 1;

  while (fgets(buffer, READ_CHUNK_SIZE, input) != NULL) {

    // Create new file if needed
    if (line_count == 0 && output == NULL) {
      snprintf(filename, MAX_SIZE_FILENAME, "%d.chunk.txt", file_index);

      output = fopen(filename, "w");
      if (output == NULL) {
        printf("Error creating output file: %s\n", filename);
        fclose(input);
        return 4;
      }
    }

    fputs(buffer, output);

    // Check if FULL line finished
    if (strchr(buffer, '\n') != NULL) {
      line_count++;

      // Only switch AFTER finishing line
      if (line_count == chunk_size) {
        fclose(output);
        output = NULL;
        file_index++;
        line_count = 0;
      }
    }
  }

  if (output != NULL) {
    fclose(output);
  }

  fclose(input);
  return 0;
}
