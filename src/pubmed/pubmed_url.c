#include "pubmed_url.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PUBMED_ESEARCH_BASE \
  "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"

#define PUBMED_EFETCH_BASE \
  "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi"

char *pubmed_build_search_url(const char *query, int retstart, int retmax) {
  if (!query) {
    return NULL;
  }

  size_t len =
    strlen(PUBMED_ESEARCH_BASE) +
    strlen("?db=pubmed&term=&retmode=json&retstart=&retmax=") +
    strlen(query) + 32;

  char *url = malloc(len);
  if (!url) {
    return NULL;
  }

  snprintf(
    url,
    len,
    "%s?db=pubmed&term=%s&retmode=json&retstart=%d&retmax=%d",
    PUBMED_ESEARCH_BASE,
    query,
    retstart,
    retmax
  );

  return url;
}

char *pubmed_build_efetch_url(const char **pmids, int pmid_count) {
  if (!pmids || pmid_count == 0) {
    return NULL;
  }

  size_t len =
    strlen(PUBMED_EFETCH_BASE) +
    strlen("?db=pubmed&id=&retmode=xml");

  for (int i = 0; i < pmid_count; i++) {
    len += strlen(pmids[i]) + 1;
  }

  char *url = malloc(len + 1);
  if (!url) {
    return NULL;
  }

  strcpy(url, PUBMED_EFETCH_BASE);
  strcat(url, "?db=pubmed&id=");

  for (int i = 0; i < pmid_count; i++) {
    strcat(url, pmids[i]);
    if (i < pmid_count - 1) {
      strcat(url, ",");
    }
  }

  strcat(url, "&retmode=xml");
  return url;
}
