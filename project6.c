/*
Name: Yui Luong
UID: U09663368

Description:
This program reads an input text file and splits its contents into multiple
output files. The second command-line argument determines how many complete
lines should be written to each chunk file. Output files are named
1.chunk.txt, 2.chunk.txt, and so on. The program preserves full lines even
when a line is read in multiple fixed-size buffer reads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_FILENAME 64
#define READ_CHUNK_SIZE 30

int main(int argc, char *argv[]) {
  /*
  Function logic:
  1. Validate the command-line arguments and ensure the requested chunk size
     is a positive integer.
  2. Open the input file for reading.
  3. Read the file a small buffer at a time and write each buffer into the
     current output chunk file.
  4. Count completed lines by checking for newline characters, and once the
     requested number of full lines has been written, close the current chunk
     file and start the next one.
  5. Close any open files before exiting.
  */

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
    // Open a new chunk file before writing the first data for that chunk.
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

    // A line is only counted after its newline character has been read.
    if (strchr(buffer, '\n') != NULL) {
      line_count++;

      // Start a new output file only after the full line limit is reached.
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
