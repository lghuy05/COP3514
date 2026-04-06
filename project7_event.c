// UID: U09663368
// Program description:
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

struct customer {
  char email[101];
  int purchases;
  char name[101];
};

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

  int n = 0;

  // Read file
  while (fscanf(infile, "%[^,],%d,%[^\n]\n", list[n].email, &list[n].purchases,
                list[n].name) == 3) {
    n++;
  }

  int num;
  printf("Enter number of purchases: ");
  scanf("%d", &num);

  int found = search(list, n, num, result);

  // Write to output file
  for (int i = 0; i < found; i++) {
    fprintf(outfile, "%s, %d, %s\n", result[i].email, result[i].purchases,
            result[i].name);
  }

  fclose(infile);
  fclose(outfile);

  printf("Output file name: result.csv\n");

  return 0;
}
