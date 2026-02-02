/*
Name: Yui Luong
UID: U09662268

Description:
This program calculates the rental cost of air conditioners based on
user selection and number of rental days. Charges are computed using
a flat fee for the first day, daily rates for additional days, and
a maximum weekly charge cap.
*/

#include <stdio.h>

// Calculates total rental charge based on AC type and rental duration
int charge(int ac_selection, int days) {
  int max_week_charge;
  int daily_charge;
  int flat_fee;
  switch (ac_selection) {
  case 1:
    max_week_charge = 160;
    daily_charge = 30;
    flat_fee = 50;
    break;
  case 2:
    max_week_charge = 200;
    daily_charge = 35;
    flat_fee = 60;
    break;
  case 3:
    max_week_charge = 280;
    daily_charge = 50;
    flat_fee = 80;
    break;
  case 4:
    max_week_charge = 550;
    daily_charge = 120;
    flat_fee = 200;
    break;
  default:
    return -1;
  }

  int remaining_day = days % 7;
  int weeks = days / 7;
  int total_charge = weeks * max_week_charge;
  if (remaining_day > 0) {
    int partial_charge;
    if (weeks == 0) {
      // Only apply flat fee when there is no full week
      partial_charge = flat_fee + (remaining_day - 1) * daily_charge;
    } else {
      partial_charge = remaining_day * daily_charge;
    }
    if (partial_charge > max_week_charge) {
      partial_charge = max_week_charge;
    }
    total_charge += partial_charge;
  }

  return total_charge;
}

// Handles user inputs, validate data and display messages.
void ACrental() {
  printf("Please select from four types of AC: 1, 2, 3, and 4\n");
  printf("Enter selection: ");

  int ac_selection;
  if (scanf("%d", &ac_selection) != 1 || ac_selection < 1 || ac_selection > 4) {
    printf("Invalid selection. Select from 1 to 4.");
    return;
  }

  printf("Enter days:");
  int days;

  if (scanf("%d", &days) != 1 || days < 0) {
    printf("Invalid days.");
    return;
  }

  int total_charge = charge(ac_selection, days);
  printf("Charge($): %d", total_charge);
}

int main() {
  ACrental();
  return 0;
}
