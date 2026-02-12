/*
Name: Yui Luong
UID: U09663368

Description:
This program finds the counselor that has not been assigned
to a summer camp program

Counselors are numbered from 1 to n
All counselors except one have already been assigned

The program uses a helper function "search" to determine
which counselor number is missing
*/

#include <stdio.h>

/*
Finds the missing counselor number
Logic:
    The total sum of numbers from 1 to n is:
        n(n + 1) / 2 (math formula of sum)

    If we subtract the sum of assigned counselors
    from the total expected sum,
    the difference is the missing counselor

Returns:
    The counselor number that has not been assigned
*/
int search(int counselors[], int n) {

  int expectedSum = n * (n + 1) / 2;
  int assignedSum = 0;

  // Add up all assigned counselor numbers
  for (int i = 0; i < n - 1; i++) {
    assignedSum += counselors[i];
  }

  // The difference gives the missing counselor
  return expectedSum - assignedSum;
}

int main() {

  int totalCounselors;

  printf("Enter number of counselors: ");
  scanf("%d", &totalCounselors);

  // There will be n-1 assigned counselors
  int assigned[totalCounselors - 1];

  printf("Enter counselors assigned: ");

  for (int i = 0; i < totalCounselors - 1; i++) {
    scanf("%d", &assigned[i]);
  }

  int missingCounselor = search(assigned, totalCounselors);

  printf("Counselor has not been assigned: %d\n", missingCounselor);

  return 0;
}
