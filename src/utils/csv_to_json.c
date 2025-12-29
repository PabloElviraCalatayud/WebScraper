#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_field(char **line) {
  if (**line == '\0' || **line == '\n') {
    return NULL;
  }

  char *start;
  char *out;
  size_t len = 0;

  if (**line == '"') {
    (*line)++;
    start = *line;

    while (**line) {
      if (**line == '"' && (*(*line + 1) == ',' || *(*line + 1) == '\n' || *(*line + 1) == '\0')) {
        break;
      }
      (*line)++;
    }

    len = *line - start;
    out = malloc(len + 1);
    memcpy(out, start, len);
    out[len] = '\0';

    if (**line == '"') {
      (*line)++;
    }
    if (**line == ',') {
      (*line)++;
    }
  } else {
    start = *line;
    while (**line && **line != ',' && **line != '\n') {
      (*line)++;
    }

    len = *line - start;
    out = malloc(len + 1);
    memcpy(out, start, len);
    out[len] = '\0';

    if (**line == ',') {
      (*line)++;
    }
  }

  return out;
}

static void json_escape(FILE *out, const char *s) {
  fputc('"', out);
  for (; *s; s++) {
    unsigned char c = (unsigned char)*s;
    if (c == '"') {
      fputs("\\\"", out);
    } else if (c == '\\') {
      fputs("\\\\", out);
    } else if (c == '\n') {
      fputs("\\n", out);
    } else if (c == '\r') {
      fputs("\\r", out);
    } else if (c == '\t') {
      fputs("\\t", out);
    } else if (c < 0x20) {
      fprintf(out, "\\u%04x", c);
    } else {
      fputc(c, out);
    }
  }
  fputc('"', out);
}

int csv_to_json(const char *csv_path, const char *json_path) {
  FILE *in = fopen(csv_path, "r");
  if (!in) {
    return -1;
  }

  FILE *out = fopen(json_path, "w");
  if (!out) {
    fclose(in);
    return -2;
  }

  char line[16384];
  int first = 1;

  if (!fgets(line, sizeof(line), in)) {
    fclose(in);
    fclose(out);
    return -3;
  }

  fprintf(out, "[\n");

  while (fgets(line, sizeof(line), in)) {
    char *p = line;

    char *repo = read_field(&p);
    char *title = read_field(&p);
    char *authors = read_field(&p);
    char *abstract = read_field(&p);
    char *doi = read_field(&p);

    if (!first) {
      fprintf(out, ",\n");
    }
    first = 0;

    fprintf(out, "  {\n");

    fprintf(out, "    \"repository\": ");
    json_escape(out, repo ? repo : "");
    fprintf(out, ",\n");

    fprintf(out, "    \"title\": ");
    json_escape(out, title ? title : "");
    fprintf(out, ",\n");

    fprintf(out, "    \"authors\": ");
    json_escape(out, authors ? authors : "");
    fprintf(out, ",\n");

    fprintf(out, "    \"abstract\": ");
    json_escape(out, abstract ? abstract : "");
    fprintf(out, ",\n");

    fprintf(out, "    \"doi\": ");
    json_escape(out, doi ? doi : "");
    fprintf(out, "\n");

    fprintf(out, "  }");

    free(repo);
    free(title);
    free(authors);
    free(abstract);
    free(doi);
  }

  fprintf(out, "\n]\n");

  fclose(in);
  fclose(out);
  return 0;
}
