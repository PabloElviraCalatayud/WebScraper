#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "repository_parser.h"
#include "tokenizer.h"
#include "translator.h"
#include "pubmed_url.h"
#include "utils.h"

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

    QueryNode *query = translate_uql_to_pubmed(tokens);
    char *query_str = query_to_string(query);
    for (int page = 0; page < PUBMED_PAGES; page++) {
      int retstart = page * PUBMED_PAGE_SIZE;

      char *url = pubmed_build_search_url(query_str, retstart, PUBMED_PAGE_SIZE);

      HttpBuffer response;
      if (http_get(url, &response) == 0) {
        printf("Page %d response:\n%s\n", page + 1, response.data);
        http_buffer_free(&response);
      }

      free(url);
    }

    free(query_str);
    free_query(query);
  }

  free_tokens(tokens);
  fclose(fout);
  return 0;
}
