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
  printf("  made token of type ");
  print_token_enum(type);
  return t;
}

void free_token(struct token_t* t) {
  free(t->value);
  free(t);
}

void print_token_enum(enum token token) {
  switch (token) {
    case INT:
      printf("INT\n");
      break;
    case MUL:
      printf("MUL\n");
      break;
    case DIV:
      printf("DIV\n");
      break;
    case END_OF_FILE:
      printf("END_OF_FILE\n");
      break;
    default:
    break;
  }
}

void print_token(struct token_t* t) {
  switch (t->type) {
    case INT:
      printf("Got token of type INT\n");
      printf("  Val %s\n", t->value);
    break;
    case MUL:
      printf("Got token of type MUL\n");
      printf("  Val %s\n", t->value);
    break;
    case DIV:
      printf("Got token of type DIV\n");
      printf("  Val %s\n", t->value);
    break;
    case END_OF_FILE:
      printf("Got token of type END_OF_FILE\n");
    break;
    default:
    break;
  }
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

struct token_t* read_int(char* input, int* start_index) {
  int len = strlen(input);
  int end_index = -1;
  for (int i = (*start_index); i < len; i++) {
    char c = input[i];
    if (end_index == -1 && isspace(c)) {
      (*start_index)++;
    } else if (isdigit(c)) {
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
  char* ret_str = substr((*start_index), end_index, input);
  *start_index = end_index;
  #ifdef DEBUG
  printf("Return string is: %s\n", ret_str);
  #endif
  return make_token(INT, ret_str);
}
