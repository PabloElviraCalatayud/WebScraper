#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "repository_parser.h"

Repository parse_repository(const char *str){
    if(!str){
        return REPO_UNKNOWN;
    }

    if(strcasecmp(str,"pubmed") == 0){
        return REPO_PUBMED;
    }
    
    return REPO_UNKNOWN;
}

const char *repo_name(Repository repo){
    switch (repo)
    {
    case REPO_PUBMED:
        return "PubMed";
        break;
    default:
        return "Unknown";
        break;
    }
}