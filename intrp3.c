#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Grammar:
 * expr  : factor ((MUL | DIV) factor) *
 * factor: INTEGER
 */

/*
5 * 2 / 3
*/
enum token {
  INT, MUL, DIV, END_OF_FILE
};

struct token_t {
  char* value;
  enum token type;
};


struct token_t* make_token(enum token type, char* val) {
  struct token_t *t = malloc(sizeof(struct token_t));
  t->value = malloc(strlen(val) + 1);
  strcpy(t->value, val);
  t->type = type;
  return t;
}

void free_token(struct token_t* t) {
  free(t->value);
  free(t);
}

struct token_t* read_int(char* input) {
  int len = strlen(input);
  int start_index = 0;
  int end_index = -1;
  for (int i = 0; i < len; i++) {
    char c = input[i];
    if (end_index == -1 && isspace(c)) {
      start_index++;
    }
    else if (isdigit(c)) {
      end_index = i;
    } else {
      break;
    }
    printf("Current char: %c\n", input[i]);
  }
  if (end_index == -1) {
    printf("returning null\n");
    return NULL;
  }
  int ret_val_len = (end_index - start_index) + 1;
  char *ret_str = malloc(ret_val_len + 1);
  strncpy(ret_str, input, ret_val_len);
  ret_str[ret_val_len + 1] = '\0';
  return make_token(INT, ret_str);
}

struct token_t* factor(char* input) {
  struct token_t *t = read_int(input);
  printf("Token is: %s\n", t->value);
  return t;
}

int expr(char* input) {
  struct token_t* result = factor(input);
  int v = atoi(result->value);
  free_token(result);
  return v;
}

char* read_user_input() {
  const int read_length = 512;
  char *input = malloc(read_length);
  if (!fgets(input, read_length, stdin)) {
    fprintf(stderr, "Oh bollocks, something went wrong\n");
    return NULL;
  }
  const int len = strlen(input);
  if (len > 0 && input[len - 1] == '\n') {
    input[len - 1] = '\0';
  }
  return input;
}

int main () {
  while (1) {
    /* Read in user input string */
    printf("%%> ");
    char* user_input = read_user_input();
    if (!user_input) {
      fprintf(stderr, "Oh bollocks, something went wrong\n");
      return 1;
    }
    printf("Thanks, you entered: %s\n", user_input);
    int result = expr(user_input);
    printf("Your result is: %d\n", result);
    free(user_input);
  }
  return 0;
}
