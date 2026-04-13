// Yui Luong
// UID: 09663368
//
// DESCRIPTION:
// This program implements a simple Reverse Polish Notation (RPN) calculator
// using a singly linked list. Each valid integer entered by the user is added
// to the end of the list and acts like a value on the calculator stack. When
// the user enters an operator, the program removes the last two values,
// performs the requested calculation, and stores the result back in the list.
// The calculator continues until the user enters "exit", then all allocated
// memory is released before the program ends.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

typedef struct Node {
  int value;
  struct Node *next;
} Node;

/* ===== Provided-style helpers ===== */

int parse_int_strict(const char *s, int *out) {
  char *endptr;
  long val;

  if (s == NULL || out == NULL || strlen(s) == 0)
    return 0;

  // strtol lets us verify that the whole token is a valid integer.
  val = strtol(s, &endptr, 10);

  if (*endptr != '\0')
    return 0;

  *out = (int)val;
  return 1;
}

int is_operator(const char *s) {
  if (s == NULL || strlen(s) != 1)
    return 0;
  return (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
}

/* Linked list functions */

Node *add_end(Node *head, int value) {
  Node *new_node = malloc(sizeof(Node));
  if (!new_node)
    exit(EXIT_FAILURE);

  new_node->value = value;
  new_node->next = NULL;

  if (head == NULL)
    return new_node;

  // Walk to the tail so the newest value behaves like the top of the stack.
  Node *curr = head;
  while (curr->next != NULL)
    curr = curr->next;

  curr->next = new_node;
  return head;
}

Node *remove_last(Node *head, int *out) {
  if (out == NULL) {
    printf("Function remove_last called without proper arguments\n");
    exit(EXIT_FAILURE);
  }

  if (head == NULL)
    return head;

  if (head->next == NULL) {
    *out = head->value;
    free(head);
    return NULL;
  }

  // Keep track of the node before the tail so we can detach the last item.
  Node *prev = NULL;
  Node *curr = head;

  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }

  *out = curr->value;
  prev->next = NULL;
  free(curr);

  return head;
}

void print_list(Node *head) {
  printf("The linked list contains:");

  Node *curr = head;
  if (curr != NULL)
    printf(" ");

  while (curr != NULL) {
    printf("[%d]", curr->value);
    if (curr->next != NULL)
      printf(" ");
    curr = curr->next;
  }

  printf("\n");
}

void clear_list(Node **head) {
  if (head == NULL)
    return;

  Node *curr = *head;
  while (curr != NULL) {
    // Free one node at a time to avoid leaving allocated memory behind.
    Node *tmp = curr;
    curr = curr->next;
    free(tmp);
  }

  *head = NULL;
}

/* Helper */

int list_size(Node *head) {
  int count = 0;
  while (head) {
    count++;
    head = head->next;
  }
  return count;
}

/* MAIN */

int main(void) {
  Node *head = NULL;
  char input[INPUT_SIZE];
  int c;

  printf("Welcome to our RPN calculator!\n\n");

  while (1) {
    printf("Enter an operand or operator: ");

    if (scanf("%1023s", input) != 1)
      break;

    // Clear the rest of the line so each loop handles one clean token.
    while ((c = getchar()) != '\n' && c != EOF)
      ;

    if (strcmp(input, "exit") == 0) {
      printf("\n");
      break;
    }

    int value;

    if (parse_int_strict(input, &value)) {
      head = add_end(head, value);
      print_list(head);
      printf("\n");
    } else if (is_operator(input)) {
      if (list_size(head) < 2) {
        printf("--> ERROR: Not Enough Operands entered so far\n\n");
        continue;
      }

      int right, left, result;

      // The most recently entered value is used first, matching RPN rules.
      head = remove_last(head, &right);
      head = remove_last(head, &left);

      if (input[0] == '+')
        result = left + right;
      else if (input[0] == '-')
        result = left - right;
      else if (input[0] == '*')
        result = left * right;
      else
        result = left / right;

      printf("Applying operator %c to operands %d and %d for a result of %d\n",
             input[0], right, left, result);

      head = add_end(head, result);
      print_list(head);
      printf("\n");
    } else {
      printf("--> ERROR: Invalid Input: \"%s\"\n\n", input);
    }
  }

  clear_list(&head);
  printf("Thank you for using the RPN calculator!\n");

  return 0;
}
