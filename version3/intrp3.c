#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "util.h"

/**
 * Grammar:
 * expr  : factor ((MUL | DIV) factor) *
 * factor: INTEGER
 */

struct token_t* get_next_token(char* input, int* position) {
  printf("----Entering get_next_token\n");
  int len = strlen(input);
  if (len < (*position) ||
    input == NULL ||
    (*position) < 0) {
    printf("RETURN NULL\n");
    return NULL;
  }
  if ((*position) > len) {
    printf("RETURN EOF\n");
    return make_token(END_OF_FILE, "");
  }

  char current_char = input[(*position)];
  while (current_char != '\0') {
    if (isspace(current_char)) {
      (*position)++;
      current_char = input[(*position)];
    } else if (isdigit(current_char)) {
      struct token_t* ret = read_int(input, position);
      printf("after read_int position is: %d\n", *position);
      (*position)++;
      return ret;
    } else if (current_char == '*') {
      (*position)++;
      return make_token(MUL, "*");
    } else if (current_char == '/') {
      (*position)++;
      return make_token(DIV, "/");
    } else {
      printf("Got invalid input: %s\n", substr(*position, strlen(input), input));
      exit(1);
    }
  }
  return make_token(END_OF_FILE, "");
}

struct token_t* eat(
  struct token_t *current_token,
  enum token token,
  char* input,
  int* position
) {
  if (current_token == NULL || current_token->type != token) {
    printf("Syntax error, expecting token of type: ");
    print_token_enum(token);
    exit(1);
  }
  return get_next_token(input, position);
}

/*
5 * 2 / 3
*/
int factor(struct token_t **current_token, char* input, int* position) {
  struct token_t* next_t = eat(*current_token, INT, input, position);
  int ret_val = atoi((*current_token)->value);
  free_token(*current_token);
  printf("in factor next_token POINTER: %p\n", next_t);
  *current_token = next_t;
  print_token(*current_token);
  printf("in factor current_token POINTER: %p\n", *current_token);
  return ret_val;
}

int expr(char* input) {
  printf("Entering expr\n");
  int position = 0;
  struct token_t* current_token = get_next_token(input, &position);
  print_token(current_token);
  int result = factor(&current_token, input, &position);
  printf("got result from factor: %d\n", result);
  print_token(current_token);
  enum token current_type = current_token->type;
  struct token_t* next_token;

  while (current_type == MUL || current_type == DIV) {
    printf("\nbeginning of while\n");
    if (current_type == MUL) {
      printf("GOT MUL\n");
      next_token = eat(current_token, MUL, input, &position);
      free_token(current_token);
      result *= factor(&next_token, input, &position);
      print_token(next_token);
      print_token_enum(next_token->type);
      current_type = next_token->type;
    } else if (current_type == DIV) {
      printf("GOT DIV\n");
      next_token = eat(current_token, DIV, input, &position);
      free_token(current_token);
      result /= factor(&next_token, input, &position);
      print_token(current_token);
      print_token_enum(next_token->type);
      current_type = next_token->type;
    }
    current_token = next_token;
  }
  printf("\n\nAfter while loop current position is: %d\n", position);
  printf("current_token 22222 POINTER: %p\n", current_token);
  if (current_token) {
    printf("Freeing\n");
    free_token(current_token);
  }
  return result;
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
