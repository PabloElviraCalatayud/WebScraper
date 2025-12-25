#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct {
  char *data;
  size_t size;
} HttpBuffer;


char *strdup_safe(const char *s);

int http_get(const char *url, HttpBuffer *out);
void http_buffer_free(HttpBuffer *buf);

void utils_mkdir_recursive(const char *path);

void utils_sanitize_filename(const char *in, char *out, size_t maxlen);
int http_download_file(const char *url, const char *path);

#endif
