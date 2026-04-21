// Yui Luong
// UID: U09663368
// Description: This program keeps a linked list of book requests. The user can
// add a book, delete a book, print the current list, or quit. Books are stored
// in order by the author's last name, then first name.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LEN 100
#define NAME_LEN 50

typedef struct book {
  char title[TITLE_LEN];
  char first[NAME_LEN];
  char last[NAME_LEN];
  double price;
  int requests;
  struct book *next;
} book;

// PROTOTYPES
book *add_to_ordered_list(book *head);
book *delete_from_list(book *head);
void print_list(book *head);
void clear_list(book *head);
void read_line(char str[], int n);

int main() {
  book *head = NULL;
  char op;

  printf("Operation Code: a for adding to the list, d for deleting a book, p "
         "for printing the list; q for quit.\n");

  while (1) {
    printf("Enter operation code: ");
    scanf(" %c", &op);
    getchar();

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
    }
  }

  return 0;
}

/*
 * Adds a new book to the list in author name order.
 * If the same title and author are already in the list, the list is unchanged.
 */
book *add_to_ordered_list(book *head) {
  char title[TITLE_LEN], first[NAME_LEN], last[NAME_LEN];

  printf("Enter book title: ");
  read_line(title, TITLE_LEN);

  printf("Enter author's first name: ");
  read_line(first, NAME_LEN);

  printf("Enter author's last name: ");
  read_line(last, NAME_LEN);

  /* Check for a duplicate before asking for the rest of the book data. */
  book *cur = head;
  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {
      printf("book already exists\n\n");
      return head;
    }
    cur = cur->next;
  }

  book *new_node = malloc(sizeof(book));
  if (!new_node)
    exit(1);

  strcpy(new_node->title, title);
  strcpy(new_node->first, first);
  strcpy(new_node->last, last);

  printf("Enter book's price: ");
  scanf("%lf", &new_node->price);

  printf("Enter the number of requests: ");
  scanf("%d", &new_node->requests);
  getchar();

  new_node->next = NULL;

  if (head == NULL) {
    printf("\n");
    return new_node;
  }

  book *prev = NULL;
  cur = head;

  /* Stop when the new book belongs before the current book. */
  while (cur != NULL) {
    int cmp = strcmp(new_node->last, cur->last);
    if (cmp < 0 || (cmp == 0 && strcmp(new_node->first, cur->first) < 0))
      break;
    prev = cur;
    cur = cur->next;
  }

  /* Insert at the front when the new book comes before the old head. */
  if (prev == NULL) {
    new_node->next = head;
    printf("\n");
    return new_node;
  } else {
    prev->next = new_node;
    new_node->next = cur;
    printf("\n");
    return head;
  }
}

/*
 * Deletes the book that matches the entered title and author.
 * Returns the possibly changed head pointer.
 */
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

  /* Keep prev one node behind cur so the matching node can be unlinked. */
  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {

      /* Deleting the first node changes the head pointer. */
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

  printf("book does not exit\n\n");
  return head;
}

/* Prints all books in the list using columns for easier reading. */
void print_list(book *head) {
  printf("Title\t\t\t\t\tFirst Name\tLast Name\tRequests  Price\n");

  while (head != NULL) {
    printf("%-40s %-15s %-15s %5d %8.2f\n", head->title, head->first,
           head->last, head->requests, head->price);
    head = head->next;
  }

  printf("\n");
}

/* Frees every node before the program exits. */
void clear_list(book *head) {
  book *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

/* Reads a line of input and leaves room for the null character. */
void read_line(char str[], int n) {
  int ch, i = 0;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (i < n - 1)
      str[i++] = ch;
  }
  str[i] = '\0';
}
