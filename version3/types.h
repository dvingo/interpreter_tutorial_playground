#ifndef TYPES_H
#define TYPES_H

enum token {
  INT, MUL, DIV, END_OF_FILE
};

struct token_t {
  char* value;
  enum token type;
};

char* substr(int start_pos, int end_pos, char* str);
struct token_t* make_token(enum token type, char* val);
void free_token(struct token_t* t);
struct token_t* read_int(char* input);

#endif
