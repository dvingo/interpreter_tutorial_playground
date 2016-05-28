#include <stdio.h>

int main() {
  fprintf(stdout, "hi\n");
  char *const filename = "test.c";

  FILE *f;
  f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error: Unable to open input file: %s\n", filename);
    return 8;
  }
  char content[100][100];
  int i = 0;
  fgets(content[i], sizeof(content[i]), f);
  fprintf(stdout, "Got lint: %s", content[i]);
  i++;
  fgets(content[i], sizeof(content[i]), f);
  fprintf(stdout, "Got lint: %s", content[i]);

  fclose(f);

  return 0;
}
