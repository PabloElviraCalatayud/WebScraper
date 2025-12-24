#include <stdio.h>
#include <string.h>
#include "repository_parser.h"
#include "tokenizer.h"

#define MIN_ARGC 4
#define HELP "<query><file-name.csv><repo_1><repo_N>"
#define SUPPORTED_REPOS "PubMed"

int main(int argc, char *argv[]) {
  if (argc < MIN_ARGC) {
    printf("Missing parameters: %s\n" HELP);
    printf("Supported repositories: %s\n", SUPPORTED_REPOS);
    return -1;
  }

  const char *ext = strrchr(argv[2], '.');
  if (!ext || strcmp(ext, ".csv") != 0) {
    printf("Output file must be .csv\n");
    return -2;
  }

  FILE *fout;
  if (!(fout = fopen(argv[2], "w"))) {
    perror("Error while opening output file");
    return -3;
  }

  for(int i = 3; i < argc; i++){
    Repository repo = parse_repository(argv[i]);

    if (repo == REPO_UNKNOWN) {
      printf("Unknown repository %s\n", argv[i]);
      continue;
    }

    printf("Processing repository: %s\n", repo_name(repo));
  }

  Token *tokens = tokenize(argv[1]);

  free_tokens(tokens);
  fclose(fout);
  return 0;
}
