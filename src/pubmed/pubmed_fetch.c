#include "pubmed_fetch.h"
#include "pubmed_url.h"
#include "pubmed_types.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <curl/curl.h>

void pubmed_free_pmids(char **pmids, int count) {
  for (int i = 0; i < count; i++) {
    free(pmids[i]);
  }
  free(pmids);
}

int pubmed_fetch_articles(const char **pmids, int pmid_count, PubMedArticle **out_articles, int *out_count) {
  if (!pmids || pmid_count == 0) {
    *out_articles = NULL;
    *out_count = 0;
    return 0;
  }

  PubMedArticle *articles = calloc(pmid_count, sizeof(PubMedArticle));
  if (!articles) {
    return -1;
  }

  for (int i = 0; i < pmid_count; i++) {
    articles[i].title = strdup_safe("TODO: Title");
    articles[i].authors = strdup_safe("TODO: Authors");
    articles[i].abstract = strdup_safe("TODO: Abstract");
    articles[i].doi = strdup_safe(pmids[i]);
  }

  *out_articles = articles;
  *out_count = pmid_count;
  return 0;
}

void pubmed_free_articles(PubMedArticle *articles, int count) {
  for (int i = 0; i < count; i++) {
    free(articles[i].title);
    free(articles[i].authors);
    free(articles[i].abstract);
    free(articles[i].doi);
  }

  free(articles);
}

int pubmed_parse_idlist(const char *json, char ***out_pmids, int *out_count) {
  if (!json || !out_pmids || !out_count) {
    return -1;
  }

  const char *idlist = strstr(json, "\"idlist\"");
  if (!idlist) {
    return -1;
  }

  const char *p = strchr(idlist, '[');
  if (!p) {
    return -1;
  }

  p++;

  char **pmids = NULL;
  int count = 0;

  while (*p && *p != ']') {
    while (*p == ' ' || *p == '\n' || *p == ',') {
      p++;
    }

    if (*p != '"') {
      break;
    }

    p++;
    const char *start = p;

    while (*p && *p != '"') {
      p++;
    }

    if (*p != '"') {
      break;
    }

    size_t len = p - start;
    char *pmid = malloc(len + 1);
    if (!pmid) {
      break;
    }

    memcpy(pmid, start, len);
    pmid[len] = '\0';

    char **tmp = realloc(pmids, sizeof(char *) * (count + 1));
    if (!tmp) {
      free(pmid);
      break;
    }

    pmids = tmp;
    pmids[count++] = pmid;
    p++;
  }

  *out_pmids = pmids;
  *out_count = count;
  return 0;
}

int pubmed_download_pmc(const char *pmcid, const char *title, const char *out_dir) {
  if (!pmcid || !title) {
    return -1;
  }

  char safe_title[256];
  utils_sanitize_filename(title, safe_title, sizeof(safe_title));

  char url[512];
  snprintf(url, sizeof(url),
           "https://www.ncbi.nlm.nih.gov/pmc/articles/%s/?page=xml",
           pmcid);

  char path[512];
  snprintf(path, sizeof(path),
           "%s/%s.xml",
           out_dir, safe_title);

  return http_download_file(url, path);
}