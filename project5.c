// Name: Yui Luong
// UID: U09663368

// Program: Command Line Word Replacement
//
// Description:
// This program replaces every occurrence of a given word in a sentence
// with another word of the same length. The program can run in two modes:
//
// 1. Command-line mode:
//    ./a.out "sentence here" word replacement
//
// 2. Interactive mode:
//    If no command line arguments are provided, the user will be prompted
//    to enter the sentence, the word to replace, and the replacement word.
//
// The program uses pointer-based string manipulation to:
// - measure string length
// - copy strings
// - detect whether a word occurs at a given position
// - overwrite words in place
//
// Standard string library functions (like those in <string.h>) are not used.
// Instead, all string operations are implemented manually using pointers.
//
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 50

// Copies the string from 'source' to 'destination' using pointer iteration.
// The destination buffer is assumed to have enough allocated space.
// If either pointer is NULL, the function returns without doing anything.
// The function also checks that the string length does not exceed
// MAX_STRING_LEN to prevent scanning infinitely if '\0' is missing.
void my_strcpy(char *destination, char *source) {
  if (destination == NULL || source == NULL)
    return;

  char *src = source;
  char *dest = destination;
  int count = 0;
  while (*src != '\0') {
    *dest = *src;
    src++;
    dest++;
    count++;

    if (count > MAX_STRING_LEN) {
      printf("Unable to find end of string or string too long\n");
      exit(EXIT_FAILURE);
    }
  }
  *dest = '\0';
}

// my_strlen
// Calculates the length of a string using pointer traversal.
// The length returned does not include the null terminator '\0'.
// If the pointer is NULL, the function returns 0.
// If more than MAX_STRING_LEN characters are scanned without
// encountering '\0', the program prints an error and exits.
size_t my_strlen(const char *s) {
  if (s == NULL)
    return 0;

  const char *start = s;
  const char *ptr = s;
  int count = 0;
  while (*ptr != '\0') {
    ptr++;
    count++;
    if (count > MAX_STRING_LEN) {
      printf("Unable to find end of string or string too long\n");
    }
  }
  return ptr - start;
}

// Determines whether the string 'sentence' begins with the string 'word'
// starting at the given memory location.
// The comparison is done character by character using pointers.
// Returns true if the characters match for the entire length of 'word',
// otherwise returns false.
bool starts_with_word(char *sentence, char *word) {
  if (sentence == NULL || word == NULL)
    return false;
  size_t len_sentence = my_strlen(sentence);
  size_t len_word = my_strlen(word);
  if (len_sentence < len_word)
    return false;

  char *s = sentence;
  char *w = word;

  while (*w != '\0') {
    if (*s != *w)
      return false;
    w++;
    s++;
  }
  return true;
}

// Replaces characters starting at the address 'start' with the characters
// from the string 'replacement'. The function only performs the overwrite
// if the remaining portion of 'start' is long enough to contain the
// replacement word. Returns true if the overwrite occurs, otherwise false.
bool overwrite_with_word(char *start, char *replacement) {
  if (start == NULL || replacement == NULL)
    return false;
  size_t len_start = my_strlen(start);
  size_t len_replacement = my_strlen(replacement);

  if (len_start < len_replacement)
    return false;

  char *s = start;
  char *r = replacement;

  while (*r != '\0') {
    *s = *r;
    s++;
    r++;
  }
  return true;
}

// Scans the sentence and replaces every occurrence of 'word' with
// 'replacement'. A valid word occurrence must be surrounded by spaces
// or string boundaries so that partial matches inside other words
// are not replaced. The function uses the helper functions
// starts_with_word() and overwrite_with_word() to perform the replacement.
void overwrite_all_words(char *sentence, char *word, char *replacement) {
  if (sentence == NULL || word == NULL || replacement == NULL) {
    printf("Unable to find end of string or string too long\n");
    exit(EXIT_FAILURE);
  }

  size_t len_sentence = my_strlen(sentence);
  size_t len_word = my_strlen(word);
  size_t len_replacement = my_strlen(replacement);

  if (len_word != len_replacement)
    return;

  if (len_word > len_replacement)
    return;

  char *ptr = sentence;

  while (*ptr != '\0') {
    if (starts_with_word(ptr, word)) {
      bool left_ok = (ptr == sentence || *(ptr - 1) == ' ');
      bool right_ok = (*(ptr + len_word) == ' ' || *(ptr + len_word) == '\0');

      if (left_ok && right_ok) {
        overwrite_with_word(ptr, replacement);
        ptr += len_word;
        continue;
      }
    }
    ptr++;
  }
}

/* This function iterates over a string until it reaches the end
    or finds a newline character. If it finds a newline, it replaces
    it with a null terminator and return immediately.
*/
void remove_end_newline(char *s) {
  char *p = s;
  while (*p != '\0') {
    if (*p == '\n') {
      *p = '\0';
      break;
    }
    ++p;
  }
}

/*  This main function provides 2 modes of operation: interactive and
   command-line. In interactive mode, the user is prompted to enter a sentence,
   a word to replace, and a replacement word. In command-line mode, the user
   provides these three pieces of information as command-line arguments when
   running the program. That's the mode required by the instuctions, but the
   interactive mode is provided for your convenience while testing. The program
   then validates the input according to the specifications and performs the
   word replacement in the sentence, finally printing the modified sentence to
    standard output.
*/
int main(int argc, char **argv) {

  char sentence[MAX_STRING_LEN * 2 + 1];    // the sentence to be worked on
  char word[MAX_STRING_LEN * 2 + 1];        // the word to be replaced
  char replacement[MAX_STRING_LEN * 2 + 1]; // the replacement word

  bool interactive =
      false; // whether to run in interactive mode or command-line mode

  if (argc == 1) {
    // if we have no command-line arguments, run in interactive mode
    interactive = true;
  } else if (argc != 4) {
    // if we don't have exactly 3 command-line arguments, print usage
    // message and exit with failure
    fputs("Usage: ./a.out \"<sentence>\" \"<word>\" \"<replacement>\"\n",
          stdout);
    fputs("   or: ./a.out\n", stdout);
    exit(EXIT_FAILURE);
  }

  if (interactive) {
    printf("Original sentence (max length %d): ", MAX_STRING_LEN);

    // The fgets function is another way to read an entire line
    fgets(sentence, (int)sizeof(sentence), stdin);
    // fgets reads everything on the line, including the newline
    // character at the end. We don't want that, so we call this
    // helper function to remove it.
    remove_end_newline(sentence);

    fputs("\nWord to replace: ", stdout);
    fgets(word, (int)sizeof(word), stdin);
    remove_end_newline(word);

    fputs("\nReplacement: ", stdout);
    fgets(replacement, (int)sizeof(replacement), stdin);
    remove_end_newline(replacement);
  } else {
    // In non-interactive mode, we use the command line arguments
    my_strcpy(sentence, argv[1]);
    my_strcpy(word, argv[2]);
    my_strcpy(replacement, argv[3]);
  }

  /* Validate according to spec */
  size_t len_sentence = my_strlen(sentence);
  size_t len_word = my_strlen(word);
  size_t len_replacement = my_strlen(replacement);

  if (len_sentence == 0 || len_word == 0 || len_replacement == 0) {
    fputs("Unable to process your input\n", stdout);
    exit(EXIT_FAILURE);
  }

  if (len_word != len_replacement) {
    fputs("Unable to process your input\n", stdout);
    exit(EXIT_FAILURE);
  }

  if (len_sentence < len_word || len_sentence < len_replacement) {
    fputs("Unable to process your input\n", stdout);
    exit(EXIT_FAILURE);
  }

  // we call our primary function:
  overwrite_all_words(sentence, word, replacement);

  // Display a message before the resulting string (only in interactive mode):
  if (interactive)
    fputs("\nModified string: ", stdout);

  // Displays the modified sentence:
  fputs(sentence, stdout);
  fputc('\n', stdout);

  return EXIT_SUCCESS;
}
