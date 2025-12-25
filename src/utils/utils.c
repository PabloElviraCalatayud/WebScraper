#include "utils.h"
#include <stdlib.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

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

void utils_mkdir_recursive(const char *path) {
  char tmp[1024];
  char *p = NULL;
  size_t len;

  if (!path) {
    return;
  }

  snprintf(tmp, sizeof(tmp), "%s", path);
  len = strlen(tmp);

  if (tmp[len - 1] == '/') {
    tmp[len - 1] = '\0';
  }

  for (p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = '\0';
      mkdir(tmp, 0755);
      *p = '/';
    }
  }

  mkdir(tmp, 0755);
}

static size_t write_file(void *ptr, size_t size, size_t nmemb, void *stream) {
  return fwrite(ptr, size, nmemb, (FILE *)stream);
}

int http_download_file(const char *url, const char *path) {
  CURL *curl = curl_easy_init();
  if (!curl) {
    return -1;
  }

  FILE *f = fopen(path, "wb");
  if (!f) {
    curl_easy_cleanup(curl);
    return -2;
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_file);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,
                   "Mozilla/5.0 (compatible; PubMedBot/1.0)");

  CURLcode res = curl_easy_perform(curl);

  fclose(f);
  curl_easy_cleanup(curl);

  return res == CURLE_OK ? 0 : -3;
}

void utils_sanitize_filename(const char *in, char *out, size_t maxlen) {
  size_t j = 0;

  for (size_t i = 0; in[i] && j < maxlen - 1; i++) {
    unsigned char c = in[i];

    if (isalnum(c)) {
      out[j++] = c;
    } else if (c == ' ' || c == '_' || c == '-') {
      out[j++] = '_';
    }
  }

  out[j] = '\0';

  if (j == 0) {
    strncpy(out, "article", maxlen);
    out[maxlen - 1] = '\0';
  }
}
