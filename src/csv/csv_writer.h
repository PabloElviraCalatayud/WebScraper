#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <stdio.h>

typedef struct {
  char *title;
  char *authors;
  char *abstract;
  char *doi;
} PubMedArticle;

void csv_write_header(FILE *f);

void csv_write_article(
  FILE *f,
  const char *repository,
  const PubMedArticle *article
);

#endif
