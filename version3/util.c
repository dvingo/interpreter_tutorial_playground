#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
