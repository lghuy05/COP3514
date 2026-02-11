/*
Name: Yui Luong
UID: U09663368

Description:
This program calculates the rental charge for an AC unit based on:
1) Selected AC type
2) Number of rental days

Rates are stored in three arrays:
- First day rate
- Daily rate after first day
- Weekly maximum rate

The program validates user input and applies weekly caps correctly.
*/

#include <stdio.h>

/*
Purpose:
    Computes the rental cost using:
    - Weekly maximum pricing
    - First-day special rate
    - Daily rate after first day
Return:
    Total rental charge
*/
int charge(int selection, int days, int firstDay[], int dailyRate[],
           int weeklyMax[]) {

  int index = selection - 1; // Convert 1–4 selection into 0–3 index
  int fullWeeks = days / 7;  // Number of complete weeks
  int extraDays = days % 7;  // Remaining days after full weeks

  int totalCost = fullWeeks * weeklyMax[index];

  // Handle remaining days (if any)
  if (extraDays > 0) {

    int partialCost;

    // If no full week was rented, apply first-day rate
    if (fullWeeks == 0) {
      partialCost = firstDay[index] + (extraDays - 1) * dailyRate[index];
    } else {
      // If already charged weekly rate,
      // remaining days use daily rate only
      partialCost = extraDays * dailyRate[index];
    }

    // Weekly maximum still applies to partial week
    if (partialCost > weeklyMax[index]) {
      partialCost = weeklyMax[index];
    }

    totalCost += partialCost;
  }

  return totalCost;
}

void ACrental() {

  // Rate tables
  int firstDay[4] = {50, 60, 80, 200};
  int dailyRate[4] = {30, 35, 50, 120};
  int weeklyMax[4] = {160, 200, 280, 550};

  int selection;
  int days;

  printf("Please select from four types of AC: 1, 2, 3, and 4\n");
  printf("Enter selection: ");

  if (scanf("%d", &selection) != 1 || selection < 1 || selection > 4) {
    printf("Invalid selection. Select from 1 to 4.\n");
    return;
  }

  printf("Enter days:");

  if (scanf("%d", &days) != 1 || days < 0) {
    printf("Invalid days.\n");
    return;
  }

  int total = charge(selection, days, firstDay, dailyRate, weeklyMax);

  printf("Charge($): %d\n", total);
}

int main() {
  ACrental();
  return 0;
}
