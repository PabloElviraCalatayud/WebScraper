#include "pubmed_url.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define PUBMED_ESEARCH_BASE \
  "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"

#define PUBMED_EFETCH_BASE \
  "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi"

/* ============================
 * URL encoder interno
 * ============================ */

static char *url_encode(const char *input) {
  size_t len = 0;
  const unsigned char *p = (const unsigned char *)input;

  while (*p) {
    if (isalnum(*p) || *p == '-' || *p == '_' || *p == '.' || *p == '~') {
      len += 1;
    } else if (*p == ' ') {
      len += 1;
    } else {
      len += 3;
    }
    p++;
  }

  char *out = malloc(len + 1);
  if (!out) {
    return NULL;
  }

  char *q = out;
  p = (const unsigned char *)input;

  while (*p) {
    if (isalnum(*p) || *p == '-' || *p == '_' || *p == '.' || *p == '~') {
      *q++ = *p;
    } else if (*p == ' ') {
      *q++ = '+';
    } else {
      sprintf(q, "%%%02X", *p);
      q += 3;
    }
    p++;
  }

  *q = '\0';
  return out;
}

/* ============================
 * URL builders
 * ============================ */

char *pubmed_build_search_url(const char *query, int retstart, int retmax) {
  if (!query) {
    return NULL;
  }

  char *encoded_query = url_encode(query);
  if (!encoded_query) {
    return NULL;
  }

  size_t len =
    strlen(PUBMED_ESEARCH_BASE) +
    strlen("?db=pubmed&term=&retmode=json&retstart=&retmax=") +
    strlen(encoded_query) + 32;

  char *url = malloc(len);
  if (!url) {
    free(encoded_query);
    return NULL;
  }

  snprintf(
    url,
    len,
    "%s?db=pubmed&term=%s&retmode=json&retstart=%d&retmax=%d",
    PUBMED_ESEARCH_BASE,
    encoded_query,
    retstart,
    retmax
  );

  free(encoded_query);
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
