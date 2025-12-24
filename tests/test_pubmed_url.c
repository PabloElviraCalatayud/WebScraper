#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include "pubmed_url.h"

void test_pubmed_url_simple_query(void) {
  char *url = pubmed_build_search_url("cancer", 0, 20);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_EQUAL_STRING(
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"
    "?db=pubmed&term=cancer&retmode=json&retstart=0&retmax=20",
    url
  );

  free(url);
}

void test_pubmed_url_with_spaces(void) {
  char *url = pubmed_build_search_url("lung cancer", 0, 10);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_EQUAL_STRING(
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"
    "?db=pubmed&term=lung+cancer&retmode=json&retstart=0&retmax=10",
    url
  );

  free(url);
}

void test_pubmed_url_with_operators(void) {
  char *url = pubmed_build_search_url(
    "cancer[tiab] AND therapy[tiab]",
    5,
    50
  );

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_EQUAL_STRING(
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"
    "?db=pubmed&term=cancer%5Btiab%5D+AND+therapy%5Btiab%5D"
    "&retmode=json&retstart=5&retmax=50",
    url
  );

  free(url);
}

void test_pubmed_url_with_parentheses(void) {
  char *url = pubmed_build_search_url(
    "(cancer OR tumor)[ti]",
    0,
    25
  );

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_EQUAL_STRING(
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"
    "?db=pubmed&term=%28cancer+OR+tumor%29%5Bti%5D"
    "&retmode=json&retstart=0&retmax=25",
    url
  );

  free(url);
}

void test_pubmed_url_null_query(void) {
  char *url = pubmed_build_search_url("", 0, 10);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_EQUAL_STRING(
    "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi"
    "?db=pubmed&term=&retmode=json&retstart=0&retmax=10",
    url
  );

  free(url);
}
