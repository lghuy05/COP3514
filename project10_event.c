/*
 * project10_event.c
 *
 * This program reads customer data from a CSV file, sorts the customers
 * by the number of purchases in the last three years in ascending order
 * using qsort, and writes the sorted data to result.csv.
 *
 * Name: Your Name
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 1000
#define MAX_LINE 256

// Structure to store customer data
typedef struct {
  int id;
  char name[50];
  int purchases;
} Customer;

/*
 * compare_customers
 * -----------------
 * Comparison function for qsort.
 * Sorts customers in ascending order of purchases.
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

  // Prompt user
  printf("Enter the file name: ");
  scanf("%s", filename);

  // Open input file
  input_file = fopen(filename, "r");
  if (input_file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  char line[MAX_LINE];

  // Read file line by line
  while (fgets(line, sizeof(line), input_file)) {
    // Remove newline
    line[strcspn(line, "\n")] = 0;

    // Parse CSV (assumes format: id,name,purchases)
    char *token = strtok(line, ",");
    if (token == NULL)
      continue;
    customers[count].id = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL)
      continue;
    strcpy(customers[count].name, token);

    token = strtok(NULL, ",");
    if (token == NULL)
      continue;
    customers[count].purchases = atoi(token);

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

  // Write sorted data
  for (int i = 0; i < count; i++) {
    fprintf(output_file, "%d,%s,%d\n", customers[i].id, customers[i].name,
            customers[i].purchases);
  }

  fclose(output_file);

  printf("Data sorted and written to result.csv\n");

  return 0;
}
