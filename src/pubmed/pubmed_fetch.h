#ifndef PUBMED_FETCH_H
#define PUBMED_FETCH_H

#include "pubmed_types.h"

void pubmed_free_pmids(char **pmids, int count);

int pubmed_fetch_articles(const char **pmids, int pmid_count, PubMedArticle **out_articles, int *out_count);

void pubmed_free_articles(PubMedArticle *articles, int count);

int pubmed_parse_idlist(const char *json, char ***out_pmids, int *out_count);

#endif
