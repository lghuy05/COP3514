/*
Name: Yui Luong
UID: U09663368

Description:
This program calculates the rental cost of air conditioners based on
user selection and number of rental days. Charges are computed using
arrays for first day rate, daily rate after first day, and weekly cap.
*/

#include <stdio.h>

// Calculates total rental charge using rate arrays
int charge(int selection, int days, int first_day[], int daily_after[],
           int per_week[]) {

  int index = selection - 1; // convert 1-4 to 0-3 index

  int weeks = days / 7;
  int remaining_days = days % 7;

  int total = weeks * per_week[index];

  if (remaining_days > 0) {
    int partial;

    if (weeks == 0) {
      // first day rate applies only if no full week
      partial = first_day[index] + (remaining_days - 1) * daily_after[index];
    } else {
      partial = remaining_days * daily_after[index];
    }

    if (partial > per_week[index]) {
      partial = per_week[index];
    }

    total += partial;
  }

  return total;
}

void ACrental() {

  // Arrays required by project instructions
  int first_day[4] = {50, 60, 80, 200};
  int daily_after[4] = {30, 35, 50, 120};
  int per_week[4] = {160, 200, 280, 550};

  printf("Please select from four types of AC: 1, 2, 3, and 4\n");
  printf("Enter selection: ");

  int selection;
  if (scanf("%d", &selection) != 1 || selection < 1 || selection > 4) {
    printf("Invalid selection. Select from 1 to 4.");
    return;
  }

  printf("Enter days:");
  int days;

  if (scanf("%d", &days) != 1 || days < 0) {
    printf("Invalid days.");
    return;
  }

  int total = charge(selection, days, first_day, daily_after, per_week);

  printf("Charge($): %d", total);
}

int main() {
  ACrental();
  return 0;
}
