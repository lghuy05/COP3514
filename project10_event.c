/*
 * project10_event.c
 *
 * This program reads customer data from a CSV file,
 * sorts customers by number of purchases (ascending)
 * using qsort, and writes the result to result.csv.
 *
 * Name: Your Name
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 1000
#define MAX_LINE 256

// Customer structure
typedef struct {
  char email[100];
  int purchases;
  char name[100];
} Customer;

/*
 * compare_customers
 * -----------------
 * Comparison function for qsort (ascending by purchases)
 */
int compare_customers(const void *a, const void *b) {
  Customer *c1 = (Customer *)a;
  Customer *c2 = (Customer *)b;

  return c1->purchases - c2->purchases;
}

int main() {
  char filename[100];
  FILE *input_file, *output_file;

  Customer customers[MAX_CUSTOMERS];
  int count = 0;

  char line[MAX_LINE];

  // Prompt
  printf("Enter the file name: ");
  scanf("%s", filename);

  // Open input file
  input_file = fopen(filename, "r");
  if (input_file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  // Read file line by line
  while (fgets(line, sizeof(line), input_file)) {

    // Remove newline
    line[strcspn(line, "\n")] = '\0';

    // Skip empty lines
    if (strlen(line) == 0)
      continue;

    char *token;

    // 1. Email
    token = strtok(line, ",");
    if (token == NULL)
      continue;
    strcpy(customers[count].email, token);

    // 2. Purchases
    token = strtok(NULL, ",");
    if (token == NULL)
      continue;
    customers[count].purchases = atoi(token);

    // 3. Name
    token = strtok(NULL, "\n");
    if (token == NULL)
      continue;

    // Remove leading spaces
    while (*token == ' ')
      token++;

    strcpy(customers[count].name, token);

    count++;
  }

  fclose(input_file);

  // Sort using qsort
  qsort(customers, count, sizeof(Customer), compare_customers);

  // Open output file
  output_file = fopen("result.csv", "w");
  if (output_file == NULL) {
    printf("Error creating output file.\n");
    return 1;
  }

  // Write output (STRICT FORMAT)
  for (int i = 0; i < count; i++) {
    fprintf(output_file, "%s, %d,   %s\n", customers[i].email,
            customers[i].purchases, customers[i].name);
  }

  fclose(output_file);

  return 0;
}
