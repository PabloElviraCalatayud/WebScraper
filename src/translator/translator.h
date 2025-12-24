#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "tokenizer.h"

typedef struct QueryNode {
  char *text;
  struct QueryNode *next;
} QueryNode;

QueryNode *query_node_create(const char *text);
void query_node_append(QueryNode **head, QueryNode **tail, QueryNode *node);
QueryNode *translate_uql_to_pubmed(const Token *tokens);
char *query_to_string(const QueryNode *head);
void free_query(QueryNode *head);

#endif
