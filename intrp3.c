#include <stdio.h>
#include <string.h>

/**
 * Grammar:
 * expr  : factor ((MUL | DIV) factor) *
 * factor: INTEGER
 */

// void factor() {
//   eat();
// }
//
// void expr() {
// }

int main () {
  while (1) {
    /* Read in user input string */
    printf("%%> ");
    char input[512];
    char* user_response = fgets(input, sizeof(input), stdin);
    if (!user_response) {
      printf("Oh bollocks, something went wrong\n");
      return 1;
    }
    input[strlen(user_response) - 1] = '\0';
    printf("Thanks, you entered: %s\n", input);
  }
  return 0;
}
