#include "unity.h"
#include "pubmed_url.h"
#include <string.h>
#include <stdlib.h>

void test_pubmed_build_search_url_basic(void) {
  char *url = pubmed_build_search_url("cancer[ti]", 0, 20);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_NOT_NULL(strstr(url, "db=pubmed"));
  TEST_ASSERT_NOT_NULL(strstr(url, "term=cancer[ti]"));
  TEST_ASSERT_NOT_NULL(strstr(url, "retstart=0"));
  TEST_ASSERT_NOT_NULL(strstr(url, "retmax=20"));

  free(url);
}

void test_pubmed_build_search_url_second_page(void) {
  char *url = pubmed_build_search_url("cancer[ti]", 20, 20);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_NOT_NULL(strstr(url, "retstart=20"));
  TEST_ASSERT_NOT_NULL(strstr(url, "retmax=20"));

  free(url);
}

void test_pubmed_build_efetch_url_single_pmid(void) {
  const char *pmids[] = { "12345678" };

  char *url = pubmed_build_efetch_url(pmids, 1);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_NOT_NULL(strstr(url, "efetch.fcgi"));
  TEST_ASSERT_NOT_NULL(strstr(url, "id=12345678"));
  TEST_ASSERT_NOT_NULL(strstr(url, "retmode=xml"));

  free(url);
}

void test_pubmed_build_efetch_url_multiple_pmids(void) {
  const char *pmids[] = { "1", "2", "3" };

  char *url = pubmed_build_efetch_url(pmids, 3);

  TEST_ASSERT_NOT_NULL(url);
  TEST_ASSERT_NOT_NULL(strstr(url, "id=1,2,3"));

  free(url);
}
