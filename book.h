// Yui Luong
// UID: U09663368
// Description: Declarations for the linked list of book requests.
#ifndef BOOK_H
#define BOOK_H

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

book *add_to_ordered_list(book *head);
book *delete_from_list(book *head);
void print_list(book *head);
void clear_list(book *head);

#endif
