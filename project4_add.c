/*
Name: Yui Luong
UID: U09663368
Description:
Given an input array, create an output array by summing the first and last
elements, the second and second-to-last elements, and so on. If the input
array has an odd length, copy the middle element as the last output value.
*/

#include <stdio.h>

// Build the output array by pairing values from the ends toward the center.
void compute(int *a1, int n1, int *a2, int n2) {
  int left = 0;
  int right = n1 - 1;
  while (left < right) {
    // Sum current left and right elements into the next output slot.
    *a2 = *(a1 + left++) + *(a1 + right--);
    a2++; // advance output pointer
  }

  if (n1 % 2 != 0)
    *a2 = *(a1 + left); // copy middle element when input length is odd
}

int main() {
  int n1;
  printf("Enter the length of the array: ");
  scanf("%d", &n1);

  int a1[n1];
  printf("Enter the elements of the array: ");
  for (int i = 0; i < n1; i++)
    scanf("%d", &a1[i]);

  int n2;
  // Output length is half the input length, rounded up.
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
