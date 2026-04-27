// Yui Luong
// UID: U09663368
// Description: Functions for adding, deleting, printing, and freeing the
// linked list of book requests.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "read_line.h"

/* Adds a book to the list in alphabetical order by author. */
book *add_to_ordered_list(book *head) {
  char title[TITLE_LEN], first[NAME_LEN], last[NAME_LEN];

  printf("Enter book title: ");
  read_line(title, TITLE_LEN);

  printf("Enter author's first name: ");
  read_line(first, NAME_LEN);

  printf("Enter author's last name: ");
  read_line(last, NAME_LEN);

  book *cur = head;
  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {
      printf("book already exists\n\n");
      return head;
    }
    cur = cur->next;
  }

  book *new_node = calloc(1, sizeof(book));
  if (!new_node)
    exit(1);

  strcpy(new_node->title, title);
  strcpy(new_node->first, first);
  strcpy(new_node->last, last);

  printf("Enter book's price: ");
  scanf("%lf", &new_node->price);

  printf("Enter the number of requests: ");
  scanf("%d", &new_node->requests);

  new_node->next = NULL;

  if (head == NULL) {
    printf("\n");
    return new_node;
  }

  book *prev = NULL;
  cur = head;

  while (cur != NULL) {
    int cmp = strcmp(new_node->last, cur->last);
    if (cmp < 0 || (cmp == 0 && strcmp(new_node->first, cur->first) < 0))
      break;
    prev = cur;
    cur = cur->next;
  }

  if (prev == NULL) {
    new_node->next = head;
    printf("\n");
    return new_node;
  }

  prev->next = new_node;
  new_node->next = cur;
  printf("\n");
  return head;
}

/* Deletes the matching book from the list, if it exists. */
book *delete_from_list(book *head) {
  char title[TITLE_LEN], first[NAME_LEN], last[NAME_LEN];

  printf("Enter title: ");
  read_line(title, TITLE_LEN);

  printf("Enter author first name: ");
  read_line(first, NAME_LEN);

  printf("Enter author last name: ");
  read_line(last, NAME_LEN);

  book *cur = head;
  book *prev = NULL;

  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {

      if (prev == NULL)
        head = cur->next;
      else
        prev->next = cur->next;

      free(cur);
      printf("book deleted\n\n");
      return head;
    }

    prev = cur;
    cur = cur->next;
  }

  printf("book does not exist\n\n");
  return head;
}

/* Prints the list in the same column format required by the project. */
void print_list(book *head) {
  printf("Title\t\t\t\t\tFirst Name\tLast Name\tRequests  Price\n");

  while (head != NULL) {
    printf("%-40s%-16s%-21s%d%10.2f\n", head->title, head->first, head->last,
           head->requests, head->price);
    head = head->next;
  }

  printf("\n");
}

/* Releases all dynamically allocated nodes in the list. */
void clear_list(book *head) {
  book *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}
