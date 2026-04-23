// UID: 09663368
// Name: Yui Luong
#include "storage.h"
#include <stdlib.h>
#include <string.h>

Storage *storage_create(void) {
  Storage *s = (Storage *)malloc(sizeof(Storage));
  if (!s)
    return NULL;

  s->functions_array = NULL;
  s->functions_array_size = 0;
  return s;
}

void storage_destroy(Storage *storage) {
  if (!storage)
    return;

  free(storage->functions_array);
  free(storage);
}

size_t storage_get_size(Storage *storage) {
  if (!storage)
    return 0;
  return storage->functions_array_size;
}

int storage_add_function(Storage *storage, function_pointer_t function) {
  if (!storage || !function)
    return -1;

  function_pointer_t *new_array;

  if (storage->functions_array == NULL) {
    new_array = (function_pointer_t *)malloc(sizeof(function_pointer_t));
  } else {
    new_array = (function_pointer_t *)realloc(
        storage->functions_array,
        (storage->functions_array_size + 1) * sizeof(function_pointer_t));
  }

  if (!new_array)
    return -1;

  storage->functions_array = new_array;
  storage->functions_array[storage->functions_array_size] = function;
  storage->functions_array_size++;

  return 0;
}

char **storage_execute_all(Storage *storage, const char *input) {
  if (!storage || !input)
    return NULL;

  size_t n = storage->functions_array_size;

  char **results = (char **)malloc(n * sizeof(char *));
  if (!results)
    return NULL;

  const char *current_input = input;

  for (size_t i = 0; i < n; i++) {
    function_pointer_t func = storage->functions_array[i];

    char *output = func(current_input);
    if (!output) {
      // free previous results
      for (size_t j = 0; j < i; j++) {
        free(results[j]);
      }
      free(results);
      return NULL;
    }

    results[i] = output;
    current_input = output; // chain
  }

  return results;
}
