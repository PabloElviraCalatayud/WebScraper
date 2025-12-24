#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "pubmed_url.h"

static char *url_encode(const char *input) {
  size_t len = 0;
  const unsigned char *p = (const unsigned char *)input;

  while (*p) {
    if (isalnum(*p) || *p == '-' || *p == '_' || *p == '.' || *p == '~') {
      len += 1;
    } 
    else if (*p == ' ') {
      len += 1;
    } 
    else {
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
    } 
    else if (*p == ' ') {
      *q++ = '+';
    } 
    else {
      sprintf(q, "%%%02X", *p);
      q += 3;
    }
    p++;
  }

  *q = '\0';
  return out;
}

char *pubmed_build_search_url(
  const char *query,
  int retstart,
  int retmax
) {
  const char *base =
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi";

  char *encoded_query = url_encode(query);
  if (!encoded_query) {
    return NULL;
  }

  int needed = snprintf(
    NULL,
    0,
    "%s?db=pubmed&term=%s&retmode=json&retstart=%d&retmax=%d",
    base,
    encoded_query,
    retstart,
    retmax
  );

  char *url = malloc(needed + 1);
  if (!url) {
    free(encoded_query);
    return NULL;
  }

  snprintf(
    url,
    needed + 1,
    "%s?db=pubmed&term=%s&retmode=json&retstart=%d&retmax=%d",
    base,
    encoded_query,
    retstart,
    retmax
  );

  free(encoded_query);
  return url;
}
