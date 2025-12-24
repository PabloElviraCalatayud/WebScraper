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
#define HELP "<query> <file-name.csv> <repo_1> <repo_N>"
#define SUPPORTED_REPOS "PubMed"

#define PUBMED_PAGE_SIZE 20
#define PUBMED_PAGES     2

int main(int argc, char *argv[]) {
  if (argc < MIN_ARGC) {
    printf("Missing parameters: %s\n", HELP);
    printf("Supported repositories: %s\n", SUPPORTED_REPOS);
    return -1;
  }

  const char *ext = strrchr(argv[2], '.');
  if (!ext || strcmp(ext, ".csv") != 0) {
    printf("Output file must be .csv\n");
    return -2;
  }

  FILE *fout = fopen(argv[2], "w");
  if (!fout) {
    perror("Error while opening output file");
    return -3;
  }

  csv_write_header(fout);

  Token *tokens = tokenize(argv[1]);
  if (!tokens) {
    fclose(fout);
    return -4;
  }

  for (int i = 3; i < argc; i++) {
    Repository repo = parse_repository(argv[i]);

    if (repo != REPO_PUBMED) {
      printf("Unknown repository %s\n", argv[i]);
      continue;
    }

    printf("Processing repository: %s\n", repo_name(repo));

    QueryNode *query = translate_uql_to_pubmed(tokens);
    char *query_str = query_to_string(query);

    for (int page = 0; page < PUBMED_PAGES; page++) {
      printf("Page %d\n", page);

      int retstart = page * PUBMED_PAGE_SIZE;

      char *search_url = pubmed_build_search_url(query_str, retstart, PUBMED_PAGE_SIZE);
      if (!search_url) {
        continue;
      }

      HttpBuffer search_response;
      if (http_get(search_url, &search_response) != 0) {
        free(search_url);
        continue;
      }

      char **pmids = NULL;
      int pmid_count = 0;

      if (pubmed_parse_idlist(search_response.data, &pmids, &pmid_count) != 0 || pmid_count == 0) {
        printf("No PMIDs found\n");
        http_buffer_free(&search_response);
        free(search_url);
        continue;
      }

      printf("PMIDs: %d\n", pmid_count);

      http_buffer_free(&search_response);
      free(search_url);

      char *efetch_url = pubmed_build_efetch_url((const char **)pmids, pmid_count);
      if (!efetch_url) {
        pubmed_free_pmids(pmids, pmid_count);
        continue;
      }

      HttpBuffer efetch_response;
      if (http_get(efetch_url, &efetch_response) != 0) {
        pubmed_free_pmids(pmids, pmid_count);
        free(efetch_url);
        continue;
      }

      PubMedArticle *articles = NULL;
      int article_count = 0;

      if (pubmed_parse_efetch_xml(efetch_response.data, &articles, &article_count) == 0) {
        printf("Articles parsed: %d\n", article_count);
        for (int j = 0; j < article_count; j++) {
          csv_write_article(fout, repo_name(repo), &articles[j]);
        }
      }

      pubmed_free_articles(articles, article_count);
      pubmed_free_pmids(pmids, pmid_count);
      http_buffer_free(&efetch_response);
      free(efetch_url);
    }

    free(query_str);
    free_query(query);
  }

  free_tokens(tokens);
  fclose(fout);

  /* ============================
   * CSV → JSON conversion
   * ============================ */

  char json_path[1024];
  strncpy(json_path, argv[2], sizeof(json_path) - 1);
  json_path[sizeof(json_path) - 1] = '\0';

  char *dot = strrchr(json_path, '.');
  if (dot) {
    strcpy(dot, ".json");
  }

  if (csv_to_json(argv[2], json_path) == 0) {
    printf("JSON generated: %s\n", json_path);
  } else {
    printf("Warning: failed to generate JSON\n");
  }

  return 0;
}
