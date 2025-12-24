#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <stdio.h>
#include "pubmed_types.h"

void csv_write_header(FILE *f);
void csv_write_article(FILE *f, const char *repo, const PubMedArticle *article);

#endif
