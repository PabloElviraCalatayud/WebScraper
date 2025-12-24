#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char *strdup_safe(const char *s) {
  if (!s) {
    return NULL;
  }

  size_t len = strlen(s) + 1;
  char *copy = malloc(len);
  if (copy) {
    memcpy(copy, s, len);
  }
  return copy;
}

static size_t curl_write_cb(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  HttpBuffer *mem = userp;

  char *ptr = realloc(mem->data, mem->size + realsize + 1);
  if (!ptr) {
    return 0;
  }

  mem->data = ptr;
  memcpy(&(mem->data[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->data[mem->size] = '\0';

  return realsize;
}

int http_get(const char *url, HttpBuffer *out) {
  if (!url || !out) {
    return -1;
  }

  CURL *curl = curl_easy_init();
  if (!curl) {
    return -2;
  }

  out->data = malloc(1);
  out->size = 0;

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "softbot/0.1");

  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if (res != CURLE_OK) {
    http_buffer_free(out);
    return -3;
  }

  return 0;
}

void http_buffer_free(HttpBuffer *buf) {
  if (!buf) {
    return;
  }

  free(buf->data);
  buf->data = NULL;
  buf->size = 0;
}
