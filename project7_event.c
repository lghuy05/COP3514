// UID: U09663368
// Program description:
// This program reads customer records from customers.csv, where each record
// contains an email address, a purchase count, and a customer name. The user
// enters a minimum purchase threshold, and the program copies every customer
// whose purchase count is greater than that value into result.csv.
#include <stdio.h>

#define MAX 1000

struct customer {
  char email[101];
  int purchases;
  char name[101];
};

// Copies customers with purchases greater than num into result and returns
// how many matching customers were found.
int search(struct customer list[], int n, int num, struct customer result[]) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (list[i].purchases > num) {
      result[count] = list[i];
      count++;
    }
  }
  return count;
}

int main() {
  FILE *infile = fopen("customers.csv", "r");
  FILE *outfile = fopen("result.csv", "w");

  if (infile == NULL || outfile == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  struct customer list[MAX];
  struct customer result[MAX];

  // n stores the number of customer records successfully read from the file.
  int n = 0;

  // Read each CSV row into the customer list until there is no complete record.
  while (fscanf(infile, "%[^,],%d,%[^\n]\n", list[n].email, &list[n].purchases,
                list[n].name) == 3) {
    n++;
  }

  // num is the user-provided purchase threshold.
  int num;
  printf("Enter number of purchases: ");
  scanf("%d", &num);

  int found = search(list, n, num, result);

  // Write only the matching customers to the output file.
  for (int i = 0; i < found; i++) {
    fprintf(outfile, "%s, %d, %s\n", result[i].email, result[i].purchases,
            result[i].name);
  }

  fclose(infile);
  fclose(outfile);

  printf("Output file name: result.csv\n");

  return 0;
}
