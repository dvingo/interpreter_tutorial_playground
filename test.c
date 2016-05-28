#include <string.h>
#include <ctype.h>
#include <stdio.h>

int str_is_num(char* str) {
  char c;
  for (int i = 0; i < strlen(str); i++) {
    c = str[i];
    printf("testing char: %c\n", c);
    printf("is digit? : %d\n", isdigit(c));
    if (!isdigit(c)) {
      return 0;
    }
  }
  return 1;
}

int main() {
  printf("is \"5\" a num?\n");
  printf("%d\n", str_is_num("5"));
  return 0;
}
