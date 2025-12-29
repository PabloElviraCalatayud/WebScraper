#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "repository_parser.h"
#include "tokenizer.h"
#include "translator.h"

#include "pubmed_url.h"
#include "pubmed_fetch.h"
#include "pubmed_xml_parser.h"
#include "pubmed_types.h"

#include "csv_writer.h"
#include "utils.h"
#include "csv_to_json.h"

#define MIN_ARGC 4
#define HELP "<query> <file-name.csv> <repo_1> <repo_N> [--download]"

#define PUBMED_PAGE_SIZE 20
#define PUBMED_PAGES     10

static char *build_pubmed_url(const char *pmid) {
  const char *base = "https://pubmed.ncbi.nlm.nih.gov/";
  size_t len = strlen(base) + strlen(pmid) + 2;

  char *url = malloc(len);
  if (!url) {
    return NULL;
  }

  snprintf(url, len, "%s%s/", base, pmid);
  return url;
}

int main(int argc, char *argv[]) {
  int download_enabled = 0;

  if (argc < MIN_ARGC) {
    printf("Missing parameters: %s\n", HELP);
    return -1;
  }

  for (int i = 3; i < argc; i++) {
    if (strcmp(argv[i], "--download") == 0) {
      download_enabled = 1;
    }
  }

  FILE *fout = fopen(argv[2], "w");
  if (!fout) {
    perror("csv");
    return -2;
  }

  csv_write_header(fout);

  Token *tokens = tokenize(argv[1]);
  if (!tokens) {
    fclose(fout);
    return -3;
  }

  for (int i = 3; i < argc; i++) {
    if (strcmp(argv[i], "--download") == 0) {
      continue;
    }

    Repository repo = parse_repository(argv[i]);
    if (repo != REPO_PUBMED) {
      continue;
    }

    QueryNode *query = translate_uql_to_pubmed(tokens);
    char *query_str = query_to_string(query);

    for (int page = 0; page < PUBMED_PAGES; page++) {
      char *search_url = pubmed_build_search_url(
        query_str,
        page * PUBMED_PAGE_SIZE,
        PUBMED_PAGE_SIZE
      );

      HttpBuffer search_response = {0};
      if (http_get(search_url, &search_response) != 0) {
        free(search_url);
        continue;
      }

      char **pmids = NULL;
      int pmid_count = 0;

      if (pubmed_parse_idlist(search_response.data, &pmids, &pmid_count) != 0 ||
          pmid_count == 0) {
        http_buffer_free(&search_response);
        free(search_url);
        continue;
      }

      char *efetch_url =
        pubmed_build_efetch_url((const char **)pmids, pmid_count);

      HttpBuffer efetch_response = {0};
      if (http_get(efetch_url, &efetch_response) != 0) {
        pubmed_free_pmids(pmids, pmid_count);
        http_buffer_free(&search_response);
        free(search_url);
        free(efetch_url);
        continue;
      }

      PubMedArticle *articles = NULL;
      int article_count = 0;

      if (pubmed_parse_efetch_xml(
            efetch_response.data,
            &articles,
            &article_count) == 0) {

        for (int j = 0; j < article_count; j++) {

          if (!articles[j].doi && articles[j].pmid) {
            articles[j].doi = build_pubmed_url(articles[j].pmid);
          }


          csv_write_article(fout, "PubMed", &articles[j]);

          if (download_enabled && articles[j].pmcid) {
            pubmed_download_pmc(
              articles[j].pmcid,
              articles[j].title,
              "downloads/PubMed"
            );
          }
        }
      }

      pubmed_free_articles(articles, article_count);
      pubmed_free_pmids(pmids, pmid_count);
      http_buffer_free(&search_response);
      http_buffer_free(&efetch_response);
      free(search_url);
      free(efetch_url);
    }

    free(query_str);
    free_query(query);
  }

  free_tokens(tokens);
  fclose(fout);

  char json_path[256];
  strcpy(json_path, argv[2]);
  strcpy(strrchr(json_path, '.'), ".json");
  csv_to_json(argv[2], json_path);

  return 0;
}
