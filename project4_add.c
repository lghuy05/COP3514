#include <stdio.h>

void compute(int *a1, int n1, int *a2, int n2) {

  int left = 0;
  int right = n1 - 1;
  while (left < right) {
    *a2 = *(a1 + left++) + *(a1 + right--);
    a2++;
  }

  if (n1 % 2 != 0)
    *a2 = *(a1 + left);
}

// TODO: read the length of input array and array elements
// TODO: calculate length of output array based on the length of input array

int main() {
  int n1;
  printf("Enter the length of the array: ");
  scanf("%d", &n1);

  int a1[n1];
  printf("Enter the elements of the array: ");
  for (int i = 0; i < n1; i++)
    scanf("%d", &a1[i]);

  int n2;
  if (n1 % 2 == 0) {
    n2 = n1 / 2;
  } else {
    n2 = n1 / 2 + 1;
  }
  int a2[n2];
  compute(a1, n1, a2, n2);
  printf("Output: ");
  for (int i = 0; i < n2; i++)
    printf("%d ", a2[i]);
  return 0;
}
