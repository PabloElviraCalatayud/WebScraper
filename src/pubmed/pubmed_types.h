#ifndef PUBMED_TYPES_H
#define PUBMED_TYPES_H

typedef struct {
  char *title;
  char *authors;
  char *abstract;
  char *doi;
} PubMedArticle;

#endif
