// project3_counselors.c

#include <stdio.h>

int search(int counselors[], int n) {
  int total_sum = n * (n + 1) / 2;
  int assigned_sum = 0;

  for (int i = 0; i < n - 1; i++) {
    assigned_sum += counselors[i];
  }

  return total_sum - assigned_sum;
}

int main() {
  int n;

  printf("Enter number of counselors: ");
  scanf("%d", &n);

  int counselors[n - 1];

  printf("Enter counselors assigned: ");
  for (int i = 0; i < n - 1; i++) {
    scanf("%d", &counselors[i]);
  }

  int missing = search(counselors, n);

  printf("Counselor has not been assigned: %d\n", missing);

  return 0;
}
