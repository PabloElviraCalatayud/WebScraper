#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "translator.h"
#include "utils.h"


QueryNode *query_node_create(const char *text) {
  QueryNode *node = malloc(sizeof(QueryNode));
  if (!node) {
    return NULL;
  }

  node->text = strdup_safe(text);
  node->next = NULL;
  return node;
}

void query_node_append(QueryNode **head, QueryNode **tail, QueryNode *node) {
  if (!node) {
    return;
  }

  if (*head == NULL) {
    *head = node;
    *tail = node;
  } else {
    (*tail)->next = node;
    *tail = node;
  }
}

void free_query(QueryNode *head) {
  while (head) {
    QueryNode *next = head->next;
    free(head->text);
    free(head);
    head = next;
  }
}

static char *translate_term_to_pubmed(const char *term) {
  char buffer[256];

  if (strncmp(term, "tit:", 4) == 0) {
    snprintf(buffer, sizeof(buffer), "%s[ti]", term + 4);
  } else if (strncmp(term, "abs:", 4) == 0) {
    snprintf(buffer, sizeof(buffer), "%s[ab]", term + 4);
  } else if (strncmp(term, "year:", 5) == 0) {
    snprintf(buffer, sizeof(buffer), "%s[dp]", term + 5);
  } else {
    snprintf(buffer, sizeof(buffer), "%s[tiab]", term);
  }

  return strdup_safe(buffer);
}

QueryNode *translate_uql_to_pubmed(const Token *tokens) {
  QueryNode *head = NULL;
  QueryNode *tail = NULL;

  const Token *current = tokens;

  while (current) {
    switch (current->type) {
      case TOKEN_TERM: {
        char *translated = translate_term_to_pubmed(current->value);
        query_node_append(&head, &tail, query_node_create(translated));
        free(translated);
        break;
      }

      case TOKEN_AND:
        query_node_append(&head, &tail, query_node_create(" AND "));
        break;

      case TOKEN_OR:
        query_node_append(&head, &tail, query_node_create(" OR "));
        break;

      case TOKEN_LEFT_PAREN:
        query_node_append(&head, &tail, query_node_create("("));
        break;

      case TOKEN_RIGHT_PAREN:
        query_node_append(&head, &tail, query_node_create(")"));
        break;
    }

    current = current->next;
  }

  return head;
}

char *query_to_string(const QueryNode *head) {
  size_t total_len = 0;
  const QueryNode *current = head;

  while (current) {
    total_len += strlen(current->text);
    current = current->next;
  }

  char *result = malloc(total_len + 1);
  if (!result) {
    return NULL;
  }

  result[0] = '\0';

  current = head;
  while (current) {
    strcat(result, current->text);
    current = current->next;
  }

  return result;
}
