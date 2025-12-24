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

#endif
