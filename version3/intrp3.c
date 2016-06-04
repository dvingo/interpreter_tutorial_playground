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

/*
5 * 2 / 3
*/
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
