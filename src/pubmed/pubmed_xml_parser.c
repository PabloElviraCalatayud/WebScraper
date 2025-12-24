#include "pubmed_xml_parser.h"
#include "pubmed_types.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ============================
 * Helpers internos
 * ============================ */

static char *extract_tag(const char *xml, const char *tag) {
  char open[64];
  char close[64];

  snprintf(open, sizeof(open), "<%s>", tag);
  snprintf(close, sizeof(close), "</%s>", tag);

  const char *start = strstr(xml, open);
  if (!start) {
    return NULL;
  }

  start += strlen(open);

  const char *end = strstr(start, close);
  if (!end) {
    return NULL;
  }

  size_t len = end - start;
  char *out = malloc(len + 1);
  if (!out) {
    return NULL;
  }

  memcpy(out, start, len);
  out[len] = '\0';
  return out;
}

static char *extract_doi(const char *xml) {
  const char *open = "<ArticleId IdType=\"doi\">";
  const char *close = "</ArticleId>";

  const char *start = strstr(xml, open);
  if (!start) {
    return NULL;
  }

  start += strlen(open);

  const char *end = strstr(start, close);
  if (!end) {
    return NULL;
  }

  size_t len = end - start;
  char *doi = malloc(len + 1);
  if (!doi) {
    return NULL;
  }

  memcpy(doi, start, len);
  doi[len] = '\0';
  return doi;
}

static char *extract_authors(const char *xml) {
  const char *p = xml;
  char *result = NULL;
  size_t size = 0;

  while ((p = strstr(p, "<Author>")) != NULL) {
    char *last = extract_tag(p, "LastName");
    char *first = extract_tag(p, "ForeName");

    if (last && first) {
      size_t add = strlen(first) + strlen(last) + 3;
      char *tmp = realloc(result, size + add + 1);
      if (!tmp) {
        free(last);
        free(first);
        break;
      }

      result = tmp;

      if (size > 0) {
        strcat(result, "; ");
        size += 2;
      } else {
        result[0] = '\0';
      }

      strcat(result, first);
      strcat(result, " ");
      strcat(result, last);
      size += add;
    }

    free(last);
    free(first);
    p++;
  }

  return result;
}

/* ============================
 * Parser principal
 * ============================ */

int pubmed_parse_efetch_xml(const char *xml, PubMedArticle **out_articles, int *out_count) {
  const char *p = xml;
  int count = 0;
  PubMedArticle *articles = NULL;

  while ((p = strstr(p, "<PubmedArticle>")) != NULL) {
    const char *end = strstr(p, "</PubmedArticle>");
    if (!end) {
      break;
    }

    size_t len = end - p;
    char *block = malloc(len + 1);
    memcpy(block, p, len);
    block[len] = '\0';

    PubMedArticle art = {0};

    art.title = extract_tag(block, "ArticleTitle");
    art.abstract = extract_tag(block, "AbstractText");
    art.authors = extract_authors(block);
    art.doi = extract_doi(block);

    PubMedArticle *tmp = realloc(articles, sizeof(PubMedArticle) * (count + 1));
    if (!tmp) {
      free(block);
      break;
    }

    articles = tmp;
    articles[count++] = art;

    free(block);
    p = end + 1;
  }

  *out_articles = articles;
  *out_count = count;
  return 0;
}
