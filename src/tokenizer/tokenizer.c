#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"
#include "../utils/utils.h"

static Token *create_token(TokenType type, const char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value ? strdup_safe(value) : NULL;
    token->next = NULL;

    return token;
}

Token *tokenize(const char *input) {
    Token *head = NULL;
    Token *tail = NULL;

    size_t i = 0;

    while(input[i]){
        if(isspace(input[i])){
            i++;
            continue;
        }
        
        Token *token = NULL;

        switch(input[i]){
            case '(':
                token = create_token(TOKEN_LEFT_PAREN,NULL);
                i++;
                break;
            case ')':
                token = create_token(TOKEN_RIGHT_PAREN,NULL);
                i++;
                break;
            default:
                if(isalpha(input[i])){
                    size_t start = i;
                    while(isalnum(input[i]) || input[i] == ':'){
                        i++;
                    }

                    size_t len = i - start;
                    char *word = malloc(len + 1);
                    memcpy(word, input + start, len);
                    word[len] = 0;

                    if(strcmp(word,"AND") == 0){
                        token = create_token(TOKEN_AND,NULL);
                    }
                    else if(strcmp(word, "OR") == 0){
                        token = create_token(TOKEN_OR,NULL);
                    }
                    else{
                        token = create_token(TOKEN_TERM,word);
                    }
                    free(word);
                }
                else{
                    i++;
                }
                break;
        }
        if(token){
            if(!head){
                head = token;
                tail = token;
            }
            else{
                tail->next = token;
                tail = token;
            }
        }
    }
    return head;
}

void free_tokens(Token *head) {
    while(head != NULL){
        Token *temp = head->next;
        free(head->value);
        free(head);
        head = temp;
    }
}
