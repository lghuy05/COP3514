// Yui Luong
// UID: 09663368
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

typedef struct Node {
  int value;
  struct Node *next;
} Node;

/* Provided-style helper: parse an integer strictly, with no extra chars */
int parse_int_strict(const char *s, int *out) {
  char *endptr;
  long value;

  if (s == NULL || out == NULL || strlen(s) == 0) {
    return 0;
  }

  value = strtol(s, &endptr, 10);

  if (*s == '\0' || *endptr != '\0') {
    return 0;
  }

  *out = (int)value;
  return 1;
}

/* Provided-style helper: check for +, -, *, / */
int is_operator(const char *s) {
  if (s == NULL || strlen(s) != 1) {
    return 0;
  }

  return (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
}

/* Count nodes so we can detect "not enough operands" */
int list_size(Node *head) {
  int count = 0;
  Node *curr = head;

  while (curr != NULL) {
    count++;
    curr = curr->next;
  }

  return count;
}

Node *add_end(Node *head, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  Node *curr;

  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }

  new_node->value = value;
  new_node->next = NULL;

  if (head == NULL) {
    return new_node;
  }

  curr = head;
  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = new_node;
  return head;
}

Node *remove_last(Node *head, int *out) {
  Node *curr;
  Node *prev;

  if (out == NULL) {
    printf("Function remove_last called without proper arguments\n");
    exit(EXIT_FAILURE);
  }

  if (head == NULL) {
    return head;
  }

  if (head->next == NULL) {
    *out = head->value;
    free(head);
    return NULL;
  }

  prev = NULL;
  curr = head;

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
  Node *curr = head;

  printf("The linked list contains:");

  if (curr != NULL) {
    printf(" ");
  }

  while (curr != NULL) {
    printf("[%d]", curr->value);
    curr = curr->next;
  }

  printf("\n");
}

void clear_list(Node **head) {
  Node *curr;
  Node *next_node;

  if (head == NULL) {
    return;
  }

  curr = *head;
  while (curr != NULL) {
    next_node = curr->next;
    free(curr);
    curr = next_node;
  }

  *head = NULL;
}

int main(void) {
  Node *head = NULL;
  char input[INPUT_SIZE];
  int c;

  printf("Welcome to our RPN calculator!\n");

  while (1) {
    int value;
    int right_operand;
    int left_operand;
    int result;

    printf("Enter an operand or operator: ");

    if (scanf("%1023s", input) != 1) {
      break;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
      /* discard rest of the line */
    }

    if (strcmp(input, "exit") == 0) {
      break;
    }

    if (parse_int_strict(input, &value)) {
      head = add_end(head, value);
      print_list(head);
    } else if (is_operator(input)) {
      if (list_size(head) < 2) {
        printf("--> ERROR: Not Enough Operands entered so far\n");
        continue;
      }

      head = remove_last(head, &right_operand);
      head = remove_last(head, &left_operand);

      if (input[0] == '+') {
        result = left_operand + right_operand;
      } else if (input[0] == '-') {
        result = left_operand - right_operand;
      } else if (input[0] == '*') {
        result = left_operand * right_operand;
      } else {
        result = left_operand / right_operand;
      }

      printf("Applying operator %c to operands %d and %d for a result of %d\n",
             input[0], right_operand, left_operand, result);

      head = add_end(head, result);
      print_list(head);
    } else {
      printf("--> ERROR: Invalid Input: \"%s\"\n", input);
    }
  }

  clear_list(&head);
  printf("Thank you for using the RPN calculator!\n");

  return 0;
}
