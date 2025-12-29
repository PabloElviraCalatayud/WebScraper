#ifndef PUBMED_TYPES_H
#define PUBMED_TYPES_H

typedef struct {
  char *pmid;
  char *pmcid;
  char *doi;

  char *title;
  char *authors;
  char *abstract;
} PubMedArticle;

#endif
