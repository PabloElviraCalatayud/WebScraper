#include <stdio.h>
#include "tokenizer.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error not enough arguments, expected UQL_string\n");
    return -1;
  }

  Token *tokens = tokenize(argv[1]);
  Token *current = tokens;

  while (current) {
    switch (current->type) {
      case TOKEN_TERM:
        printf("TOKEN_TERM (%s)\n", current->value);
        break;
      case TOKEN_AND:
        printf("TOKEN_AND\n");
        break;
      case TOKEN_OR:
        printf("TOKEN_OR\n");
        break;
      case TOKEN_LEFT_PAREN:
        printf("TOKEN_LEFT_PAREN\n");
        break;
      case TOKEN_RIGHT_PAREN:
        printf("TOKEN_RIGHT_PAREN\n");
        break;
    }
    current = current->next;
  }

  free_tokens(tokens);
  return 0;
}
