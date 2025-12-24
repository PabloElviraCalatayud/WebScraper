#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum{
    REPO_PUBMED,
    REPO_UNKNOWN
}Repository;

Repository parse_repository(const char *);

const char *repo_name(Repository);