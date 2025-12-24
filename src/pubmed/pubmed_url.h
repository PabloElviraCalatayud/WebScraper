#ifndef PUBMED_URL_H
#define PUBMED_URL_H

char *pubmed_build_search_url(const char *query, int retstart, int retmax);

char *pubmed_build_efetch_url(const char **pmids, int pmid_count);

#endif
