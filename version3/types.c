#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

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

char* substr(int start_pos, int end_pos, char* str) {
  printf("in substr, star pos: %d, end pos: %d\n", start_pos, end_pos);
  int ret_val_len = (end_pos - start_pos);
  char* ret_val = malloc(ret_val_len + 1);
  for (size_t i = 0; i <= ret_val_len; i++) {
    ret_val[i] = str[i + start_pos];
  }
  ret_val[ret_val_len + 1] = '\0';
  return ret_val;
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
  #ifdef DEBUG
    printf("Current char: '%c'\n", input[i]);
  #endif
  }
  if (end_index == -1) {
    printf("returning null\n");
    return NULL;
  }
  char* ret_str = substr(start_index, end_index, input);
  #ifdef DEBUG
  printf("Return string is: %s\n", ret_str);
  #endif
  return make_token(INT, ret_str);
}
