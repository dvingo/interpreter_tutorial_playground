#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum token_t {
	INTEGER,
	PLUS,
	MINUS,
	END_OF_FILE
};

struct token* consume_integer(char*, int*);
struct token* consume_operator(char*, int*);
void consume_whitespace(char*, int*);

struct token {
	enum token_t type;
	char* value;
};

int main(void) {
	printf("%%> ");
	char buffer[512];
	gets(buffer);
	printf("Got input: %s\n", buffer);

	int pos = 0;

	consume_whitespace(buffer, &pos);
	struct token* first_int = consume_integer(buffer, &pos);
	int first_num = atoi(first_int->value);
	consume_whitespace(buffer, &pos);

	struct token* operator = consume_operator(buffer, &pos);
	if (operator == NULL) {
		printf("Missing operator!\n");
		free(first_int->value);
		free(first_int);
		return -1;
	}

	printf("Got operator: %s\n", (*operator).value);
	consume_whitespace(buffer, &pos);

	struct token* second_int = consume_integer(buffer, &pos);
	int second_num = atoi(second_int->value);
	int output;
	switch (operator->type) {
		case PLUS:
			output = first_num + second_num;
			break;
		default:
			output = -1;
  }

	printf("Got a full expression: %d %s %d = %d\n", first_num, operator->value, second_num, output);

	free(first_int->value);
	free(first_int);
	free(operator->value);
	free(operator);
	free(second_int->value);
	free(second_int);
	return 0;
}

void consume_whitespace(char* input, int* pos) {
	for (int i = *pos; i < strlen(input); i++) {
		char current_char = input[i];
		if (isspace(current_char)) {
			(*pos)++;
		} else {
			break;
		}
	}
}

/**
 * Takes a buffer of input and a position to start reading from.
 * Returns a token or NULL if there is no match.
 */
struct token* consume_integer(char* input, int* pos) {
	int len = strlen(input) + 1;
	int length_left = len - (*pos);
	char *return_buffer = malloc(length_left);
	if (return_buffer == NULL) {
		printf("Failed allocating buffer, returning\n");
		return NULL;
	}

	for (int i = 0; i < length_left; i++) {
		char current_char = input[(*pos)];

		if (current_char == '\0') {
			return_buffer[i] = '\0';
			break;
	  }

		if (isdigit(current_char)) {
			return_buffer[i] = current_char;
			(*pos)++;
		} else {
			return_buffer[i] = '\0';
			break;
		}
	}
	struct token* return_token = malloc(sizeof(struct token));
	return_token->type = INTEGER;

	return_token->value = malloc(length_left);
	strcpy(return_token->value, return_buffer);
	free(return_buffer);

	return return_token;
}

struct token* consume_operator(char* input, int* pos) {
	int len = strlen(input) + 1;
	int length_left = len - (*pos);

	for (int i = 0; i < length_left; i++) {
		char current_char = input[*pos];

		if (current_char == '+') {
			struct token* return_token = malloc(sizeof(struct token));
			return_token->type = PLUS;
			return_token->value = malloc(2);
			strcpy(return_token->value, "+");
			(*pos)++;
			return return_token;
		}

	}
	return NULL;
}
