#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./dbl_linked_list.h"

enum token_t {
  INTEGER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  END_OF_FILE
};

struct token {
  enum token_t type;
  char* value;
  int position;
};

void print_token(void*, int);
void print_token_list(DblList);
struct token* get_next_token(char*, int);
int parse_list(DblList);
void free_token(void*);

int main() {
  while (1) {
    printf("%%> ");
    char buffer[512];
    char* res = fgets(buffer, sizeof(buffer), stdin);
    if (res != buffer) {
      printf("Res is different than buffer!\n");
      exit(1);
    }

    // printf("Got input: '%s'", buffer);
    DblList token_list = new_linked_list();
    struct token* token = get_next_token(buffer, 0);
    while (token->type != END_OF_FILE) {
      int pos = token->position + strlen(token->value);
      add_to_list(token_list, token, free_token);
      token = get_next_token(buffer, pos);
    }
    add_to_list(token_list, token, free_token);
    // print_token_list(token_list);
    parse_list(token_list);
    free_linked_list(token_list);
  }

  return 0;
}

int str_is_num(char* str) {
  char c;
  for (int i = 0; i < strlen(str); i++) {
    c = str[i];
    if (!isdigit(c)) { return 0; }
  }
  return 1;
}

int call_operator(int num1, int num2, char* operator) {
  if (strcmp(operator, "+") == 0) {
    return num1 + num2;
  } else if (strcmp(operator, "-") == 0) {
    return num1 - num2;
  } else if (strcmp(operator, "*") == 0) {
    return num1 * num2;
  } else if (strcmp(operator, "/") == 0) {
    return num1 / num2;
  } else {
    printf("Unknown operator passed to call_operator: %s\n", operator);
    return -1;
  }
}

/**
 * Parse the list of tokens to an integer performing the arithmetic
 * operations.
 */
int parse_list(DblList list) {
  int result = 0;
  int temp1_set = 0;
  int temp1 = 0;
  int temp2 = 0;
  char* operator = NULL;
  DblNode current_node = list->tail;
  if (list->tail->prev) {
    current_node = list->tail->prev;
  } else {
    printf("Invalid list passed to parse_list\n");
    return 1;
  }
  struct token* token = (struct token*)current_node->value;
  while (token->value) {
    printf("Loop: current val: %s\n", token->value);
    if (!token->value) {
      printf("Val is NULL!\n");
    }
    char val[strlen(token->value) + 1];
    strcpy(val, token->value);
    if (str_is_num(val)) {
      if (temp1_set) {
        temp2 = atoi(val);
        printf("Got num: %d\n", temp2);
      } else {
        temp1 = atoi(val);
        temp1_set = 1;
        printf("Got num: %d\n", temp1);
      }
      if (operator) {
        printf("Operator is: %s\n", operator);
        printf("computing: %d %s %d\n", temp1, operator, temp2);
         result = call_operator(temp1, temp2, operator);
         temp1 = result; temp2 = 0;
         printf("Got result: %d\n", result);
      }
    } else {
      if (strcmp(val, "+") == 0) {
        operator = "+";
      } else if (strcmp(val, "-") == 0) {
        operator = "-";
      } else if (strcmp(val, "*") == 0) {
        operator = "*";
      } else if (strcmp(val, "/") == 0) {
        operator = "/";
      } else {
        printf("Unknown operator: %s\n", operator);
      }
    }
    current_node = current_node->prev;
    token = (struct token*)current_node->value;
  }
  return result;
}

void print_type(enum token_t type) {
  switch(type) {
    case INTEGER:
      printf("INTEGER");
      break;
    case PLUS:
      printf("PLUS");
      break;
    case MINUS:
      printf("MINUS");
      break;
    case MULTIPLY:
      printf("MULTIPLY");
      break;
    case DIVIDE:
      printf("DIVIDE");
      break;
    case END_OF_FILE:
      printf("END_OF_FILE");
      break;
    default:
      printf("UNKNOWN_TYPE");
      break;
  }
}

void print_token(void* a_token, int i) {
  struct token* token = (struct token*)a_token;
  printf("  Type: \t");
  print_type(token->type);
  printf("\n");
  printf("  Value: \t%s\n", token->value);
  printf("  Position: \t%d\n", token->position);
}

void print_token_list(DblList list) {
  each_of_list_reverse(list, print_token);
}

void free_token(void* a_token) {
  struct token* token = (struct token*)a_token;
  free(token->value);
  free(token);
}

struct token* new_eof_token(int position) {
  struct token* return_token = malloc(sizeof(struct token));
  return_token->type = END_OF_FILE;
  return_token->value = NULL;
  return_token->position = position;
  return return_token;
}

struct token* new_digit_token(char* buffer, int position) {
  int len = strlen(buffer);
  struct token* token = malloc(sizeof(struct token));
  token->type = INTEGER;
  token->value = malloc(len);
  token->position = position;
  strcpy(token->value, buffer);
  return token;
}

struct token* new_operator_token(char* buffer, enum token_t type, int position) {
  int len = strlen(buffer);
  struct token* token = malloc(sizeof(struct token));
  token->type = type;
  token->position = position;
  token->value = malloc(len);
  strcpy(token->value, buffer);
  return token;
}

/**
 * Takes a buffer of input and a position to start reading from.
 * Returns a token or NULL if there is no match.
 */
struct token* consume_integer(char* input, int pos) {
  int len = strlen(input) + 1;
  int start_pos = pos;
  int length_left = len - pos;
  char *return_buffer = malloc(length_left);
  if (return_buffer == NULL) {
    printf("Failed allocating buffer, returning\n");
    return NULL;
  }

  for (int i = 0; i < length_left; i++) {
    char current_char = input[pos];

    if (current_char == '\0') {
      return_buffer[i] = '\0';
      break;
    }

    if (isdigit(current_char)) {
      return_buffer[i] = current_char;
      pos++;
    } else {
      return_buffer[i] = '\0';
      break;
    }
  }

  struct token* return_token = new_digit_token(return_buffer, start_pos);
  free(return_buffer);
  return return_token;
}

struct token* consume_operator(char* input, int pos) {
  // printf("Consuming operator at pos: %d\n", pos);
  int len = strlen(input) + 1;
  int length_left = len - pos;

  for (int i = 0; i < length_left; i++) {
    char current_char = input[pos];
    if (current_char == '+') {
      return new_operator_token("+", PLUS, pos);
    }
    else if (current_char == '-') {
      return new_operator_token("-", MINUS, pos);
    }
    else if (current_char == '*') {
      return new_operator_token("*", MULTIPLY, pos);
    }
    else if (current_char == '/') {
      return new_operator_token("/", DIVIDE, pos);
    }
  }
  return NULL;
}

int isoperator(char input) {
  return (input == '+' || input == '-' || input == '*' || input == '/');
}

struct token* get_next_token(char *buffer, int position) {
  char current_char = buffer[position];

  while (current_char) {
    if (isspace(current_char)) {
      // printf("get_next_token got space\n");
      position++;
      current_char = buffer[position];
    }
    else if (isdigit(current_char)) {
      // printf("get_next_token got digit\n");
      return consume_integer(buffer, position);
    }
    else if (isoperator(current_char)) {
      // printf("get_next_token got operator\n");
      return consume_operator(buffer, position);
    }
  }
  return new_eof_token(position);
}
