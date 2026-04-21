// Yui Luong
// UID: U09663368
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

/* ---------- PROTOTYPES ---------- */
book *add_to_ordered_list(book *head);
book *delete_from_list(book *head);
void print_list(book *head);
void clear_list(book *head);
void read_line(char str[], int n);

/* ---------- MAIN ---------- */
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

    /* 🔥 CRITICAL FIX: newline after each operation */
    printf("\n");
  }

  return 0;
}

/* ---------- ADD ---------- */
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
      printf("book already exists\n");
      return head;
    }
    cur = cur->next;
  }

  book *newNode = malloc(sizeof(book));
  if (!newNode)
    exit(1);

  strcpy(newNode->title, title);
  strcpy(newNode->first, first);
  strcpy(newNode->last, last);

  printf("Enter book's price: ");
  scanf("%lf", &newNode->price);

  printf("Enter the number of requests: ");
  scanf("%d", &newNode->requests);
  getchar();

  newNode->next = NULL;

  if (head == NULL)
    return newNode;

  book *prev = NULL;
  cur = head;

  while (cur != NULL) {
    int cmp = strcmp(newNode->last, cur->last);

    if (cmp < 0 || (cmp == 0 && strcmp(newNode->first, cur->first) < 0)) {
      break;
    }

    prev = cur;
    cur = cur->next;
  }

  if (prev == NULL) {
    newNode->next = head;
    return newNode;
  } else {
    prev->next = newNode;
    newNode->next = cur;
    return head;
  }
}

/* ---------- DELETE ---------- */
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
      printf("book deleted\n");
      return head;
    }

    prev = cur;
    cur = cur->next;
  }

  printf("book does not exit\n");
  return head;
}

/* ---------- PRINT ---------- */
void print_list(book *head) {
  printf("Title\t\t\t\t\tFirst Name\tLast Name\tRequests  Price\n");

  while (head != NULL) {
    printf("%-40s %-15s %-15s %5d %8.2f\n", head->title, head->first,
           head->last, head->requests, head->price);
    head = head->next;
  }

  printf("\n");
}

/* ---------- CLEAR ---------- */
void clear_list(book *head) {
  book *temp;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

/* ---------- READ LINE ---------- */
void read_line(char str[], int n) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (i < n - 1)
      str[i++] = ch;
  }
  str[i] = '\0';
}
