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

/* ---------- FUNCTION PROTOTYPES ---------- */
book *add_to_ordered_list(book *head);
book *delete_from_list(book *head);
void print_list(book *head);
void clear_list(book *head);
void read_line(char str[], int n);

/* ---------- MAIN ---------- */
int main() {
  book *head = NULL;
  char op;

  while (1) {
    printf("Enter operation code: ");
    scanf(" %c", &op);
    getchar(); // consume newline

    if (op == 'a') {
      head = add_to_ordered_list(head);
    } else if (op == 'd') {
      head = delete_from_list(head);
    } else if (op == 'p') {
      print_list(head);
    } else if (op == 'q') {
      clear_list(head);
      break;
    }
  }

  return 0;
}

/* ---------- ADD BOOK ---------- */
book *add_to_ordered_list(book *head) {
  char title[TITLE_LEN], first[NAME_LEN], last[NAME_LEN];

  printf("Enter book title: ");
  read_line(title, TITLE_LEN);

  printf("Enter author's first name: ");
  read_line(first, NAME_LEN);

  printf("Enter author's last name: ");
  read_line(last, NAME_LEN);

  /* Check duplicate */
  book *cur = head;
  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {
      printf("book already exists\n");
      return head;
    }
    cur = cur->next;
  }

  /* Create node */
  book *newNode = (book *)malloc(sizeof(book));
  if (!newNode) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  strcpy(newNode->title, title);
  strcpy(newNode->first, first);
  strcpy(newNode->last, last);

  printf("Enter book's price: ");
  scanf("%lf", &newNode->price);

  printf("Enter number of requests: ");
  scanf("%d", &newNode->requests);
  getchar();

  newNode->next = NULL;

  /* Insert sorted */
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

/* ---------- DELETE BOOK ---------- */
book *delete_from_list(book *head) {
  char title[TITLE_LEN], first[NAME_LEN], last[NAME_LEN];

  printf("Enter book title: ");
  read_line(title, TITLE_LEN);

  printf("Enter author's first name: ");
  read_line(first, NAME_LEN);

  printf("Enter author's last name: ");
  read_line(last, NAME_LEN);

  book *cur = head;
  book *prev = NULL;

  while (cur != NULL) {
    if (strcmp(cur->title, title) == 0 && strcmp(cur->first, first) == 0 &&
        strcmp(cur->last, last) == 0) {

      if (prev == NULL) {
        head = cur->next;
      } else {
        prev->next = cur->next;
      }

      free(cur);
      printf("book deleted\n");
      return head;
    }

    prev = cur;
    cur = cur->next;
  }

  printf("book not found\n");
  return head;
}

/* ---------- PRINT LIST ---------- */
void print_list(book *head) {
  printf("Title First Name Last Name Requests Price\n");

  while (head != NULL) {
    printf("%s %s %s %d %.2f\n", head->title, head->first, head->last,
           head->requests, head->price);
    head = head->next;
  }
}

/* ---------- CLEAR LIST ---------- */
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
    if (i < n - 1) {
      str[i++] = ch;
    }
  }
  str[i] = '\0';
}
