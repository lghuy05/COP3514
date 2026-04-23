// UID: 09663368
// Name: Yui Luong
/*
    This program allows the user to select a sequence of string transformation
    functions from a predefined library and apply them to an input string.
    The user can choose from functions that reverse the string, convert it to
    uppercase, lowercase, toggle case, shuffle the characters, or keep it the
   same. The selected functions are stored in a dynamic storage structure, and
   then executed in sequence on the input string, with the results printed after
   each step.
*/

#include <stdio.h>
#include <stdlib.h>

#include "library.h"
#include "storage.h"

// Number of functions available to use from library.h
#define MAX_FUNCTIONS_IN_LIBRARY 6

// Maximum number of transformation steps that the user can apply to the input
// string
#define MAX_STEPS 10

int main(void) {

  /*
      Array containing all the functions of our library
      Needs to be modified by hand when adding or removing
      a function form the library.
  */
  // TODO declare an array named library_functions which elements
  //      are of type function_pointer_t and initialize it with the
  //      functions defined in library.h

  /*
      Array of names for each of the above functions.
      Also needs to be modified by hand if we add / remove a function
      to our library.
      Make sure that you keep the index of this array and the one above
      synchronized: i.e., index i in both array would correspond to
      the same function.
  */
  // TODO Declare an array of strings named library_function_names and
  // initialize it with the
  //      names of the functions in library_functions. The name of the function
  //      will be printed to the user when asking them to select a function for
  //      each step. To be compatible with the tests, the names of the functions
  //      should be exactly as follows but you can order them to match the order
  //      of the functions in the array library_functions: "Reverse String",
  //      "Uppercase String", "Lowercase String", "Toggle Case String", "Shuffle
  //      String", "Keep String the Same"
  function_pointer_t library_functions[MAX_FUNCTIONS_IN_LIBRARY] = {
      f_reverse, f_uppercase, f_lowercase, f_togglecase, f_shuffle, f_same};
  char *library_function_names[MAX_FUNCTIONS_IN_LIBRARY] = {
      "Reverse String",     "Uppercase String", "Lowercase String",
      "Toggle Case String", "Shuffle String",   "Keep String the Same"};
  /*
      Let's create the storage for the functions that we want to
      be able apply, one after the other, to an input string.
      Initally, the storage is empty, and we will fill it with the functions
      selected by the user in the next step.
  */
  Storage *storage = storage_create();
  if (!storage) {
    fprintf(stderr, "Failed to create storage.\n");
    return EXIT_FAILURE;
  }
  int nb_steps = 0;
  while (1) {
    printf("Number of string transformation steps that you want to apply: \n");
    if (scanf("%d", &nb_steps) != 1 || nb_steps < 1 || nb_steps > MAX_STEPS) {
      printf("Invalid input. Please enter a number between 1 and %d.\n",
             MAX_STEPS);
      while (getchar() != '\n')
        ; // Clear invalid input
    } else {
      break;
    }
  }

  /*  We prompt the user to choose functions to apply for the
      number of steps specified by nb_steps. For each step, we print the list of
     available functions and ask the user to select one by entering its number.
  */
  for (int index = 0; index < nb_steps; index++) {

    printf("Assigning function for step #%d out of %d: \n", index + 1,
           nb_steps);

    printf("Available functions:\n");
    for (int i = 0; i < MAX_FUNCTIONS_IN_LIBRARY; i++) {
      printf("%d. %s\n", i + 1, library_function_names[i]);
    }

    int value;
    while (1) {
      printf("Select function number (1-%d): ", MAX_FUNCTIONS_IN_LIBRARY);
      if (scanf("%d", &value) != 1 || value < 1 ||
          value > MAX_FUNCTIONS_IN_LIBRARY) {
        printf("Invalid input. Please enter a number between 1 and %d.\n",
               MAX_FUNCTIONS_IN_LIBRARY);
        while (getchar() != '\n')
          ; // Clear invalid input
      } else {
        break;
      }
    }

    printf("Function '%s' assigned to step #%d.\n",
           library_function_names[value - 1], index + 1);

    if (storage_add_function(storage, library_functions[value - 1]) != 0) {
      fprintf(stderr, "Failed to add function to storage.\n");
      storage_destroy(storage);
      return EXIT_FAILURE;
    }
  }

  /*
      Now we prompt the user for the string to which they want to apply
      the functions specified above
  */
  printf("Enter input string: ");
  char input_string[1024];
  scanf(" %[^\n]", input_string);

  /*
      Apply the selected functions, one after the other, to the input string
      and print the result after each step. The string resulting from step #n
      will be used as input for step #(n+1).
  */
  char **results = storage_execute_all(storage, input_string);
  if (!results) {
    fprintf(stderr, "Failed to execute functions.\n");
    storage_destroy(storage);
    return EXIT_FAILURE;
  }
  size_t size = storage_get_size(storage);
  for (size_t i = 0; i < size; i++) {
    if (results[i]) {
      printf("Result after step %zu: %s\n", i + 1, results[i]);
      free(results[i]);
    } else {
      // just in case, for whatever reason, we did not get a
      // string for this step
      printf("Result after step %zu: (null)\n", i + 1);
    }
  }
  free(results);
  storage_destroy(storage);

  return EXIT_SUCCESS;
}
