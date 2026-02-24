#include <stdio.h>

int find_elements(int *a, int n1, int *b, int n2, int *c) {
  int count = 0;

  int *pa = a;
  int *pc = c;

  while (pa < a + n1) {
    *pc = *pa;
    pc++;
    pa++;
    count++;
  }

  int *pb = b;
  while (pb < b + n2) {
    int exists = 0;
    int *check = c;

    while (check < c + count) {
      if (*check == *pb) {
        exists = 1;
        break;
      }
      check++;
    }
    if (!exists) {
      *pc = *pb;
      pc++;
      count++;
    }
    pb++;
  }
  return count;
}

int main() {
  int n1, n2;

  printf("Enter the length of the first array: ");
  scanf("%d", &n1);

  int a[n1];
  printf("Enter elements in the first array: ");
  for (int i = 0; i < n1; i++)
    scanf("%d", &a[i]);

  printf("Enter the length of the second array: ");
  scanf("%d", &n2);
  int b[n2];
  printf("Enter elements in the second array: ");
  for (int i = 0; i < n2; i++)
    scanf("%d", &b[i]);

  int c[n1 + n2];

  int size = find_elements(a, n1, b, n2, c);

  printf("Output: ");
  for (int i = 0; i < size; i++)
    printf("%d ", c[i]);

  printf("\n");

  return 0;
}
