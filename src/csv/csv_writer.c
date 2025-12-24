#include "csv_writer.h"
#include "pubmed_types.h"
#include <string.h>

/* Escapa comillas dobles para CSV */
static void csv_escape_and_write(FILE *f, const char *text) {
  fputc('"', f);

  for (const char *p = text; *p; p++) {
    if (*p == '"') {
      fputc('"', f);
      fputc('"', f);
    } else {
      fputc(*p, f);
    }
  }

  fputc('"', f);
}

void csv_write_header(FILE *f) {
  fprintf(
    f,
    "Repository,Title,Authors,Abstract,DOI\n"
  );
}

void csv_write_article(FILE *f,const char *repository,const PubMedArticle *article) {
  csv_escape_and_write(f, repository);
  fputc(',', f);

  csv_escape_and_write(f, article->title ? article->title : "");
  fputc(',', f);

  csv_escape_and_write(f, article->authors ? article->authors : "");
  fputc(',', f);

  csv_escape_and_write(f, article->abstract ? article->abstract : "");
  fputc(',', f);

  csv_escape_and_write(f, article->doi ? article->doi : "");
  fputc('\n', f);
}
