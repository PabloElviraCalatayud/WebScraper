#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {
  TOKEN_TERM,
  TOKEN_AND,
  TOKEN_OR,
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN
} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
  struct Token *next;
} Token;

Token *tokenize(const char *input);
void free_tokens(Token *head);

#endif
