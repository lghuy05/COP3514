// Yui Luong
// UID: U09663368
// Description: This program keeps a linked list of book requests. The user can
// add a book, delete a book, print the current list, or quit. Books are stored
// in order by the author's last name, then first name.
#include <stdio.h>

#include "book.h"

int main() {
  book *head = NULL;
  char op;
  int ch;

  printf("Operation Code: a for adding to the list, d for deleting a book, p "
         "for printing the list; q for quit.\n");

  while (1) {
    printf("Enter operation code: ");
    scanf(" %c", &op);
    while ((ch = getchar()) != '\n' && ch != EOF)
      ;

    if (op == 'a') {
      head = add_to_ordered_list(head);
    } else if (op == 'd') {
      head = delete_from_list(head);
    } else if (op == 'p') {
      printf("\n");
      print_list(head);
    } else if (op == 'q') {
      clear_list(head);
      break;
    } else {
      printf("Illegal code\n\n");
    }
  }

  return 0;
}
