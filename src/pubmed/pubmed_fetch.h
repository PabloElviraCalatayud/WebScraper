#ifndef PUBMED_FETCH_H
#define PUBMED_FETCH_H

typedef struct {
  char *title;
  char *authors;
  char *abstract;
  char *doi;
} PubMedArticle;

int pubmed_parse_idlist(const char *json, char ***out_pmids, int *out_count);

void pubmed_free_pmids(char **pmids, int count);

int pubmed_fetch_articles(const char **pmids, int pmid_count, PubMedArticle **out_articles, int *out_count);

void pubmed_free_articles(PubMedArticle *articles, int count);

#endif
