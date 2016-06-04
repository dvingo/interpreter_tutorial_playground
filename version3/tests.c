#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

void test_read_int() {
  char input[] = "    3 * 5";
  struct token_t* t = read_int(input);
  assert(strcmp(t->value, "3") == 0);
  assert(t->type == INT);
  free_token(t);
}

void test_substr() {
  char input[] = "   this is a test";
  char *output = substr(3, 6, input);
  assert(strcmp(output, "this") == 0);
  free(output);
}

int main() {
   test_substr();
   test_read_int();
  return 0;
}
