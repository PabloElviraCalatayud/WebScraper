#include "unity.h"
#include "pubmed_fetch.h"
#include <stdlib.h>
#include <string.h>

static const char *sample_esearch_json =
"{"
"  \"esearchresult\": {"
"    \"idlist\": ["
"      \"111\","
"      \"222\","
"      \"333\""
"    ]"
"  }"
"}";

void test_pubmed_parse_idlist_basic(void) {
  char **pmids = NULL;
  int count = 0;

  int rc = pubmed_parse_idlist(sample_esearch_json, &pmids, &count);

  TEST_ASSERT_EQUAL(0, rc);
  TEST_ASSERT_EQUAL(3, count);

  TEST_ASSERT_EQUAL_STRING("111", pmids[0]);
  TEST_ASSERT_EQUAL_STRING("222", pmids[1]);
  TEST_ASSERT_EQUAL_STRING("333", pmids[2]);

  pubmed_free_pmids(pmids, count);
}

void test_pubmed_parse_idlist_empty(void) {
  const char *json =
  "{ \"esearchresult\": { \"idlist\": [] } }";

  char **pmids = NULL;
  int count = -1;

  int rc = pubmed_parse_idlist(json, &pmids, &count);

  TEST_ASSERT_EQUAL(0, rc);
  TEST_ASSERT_EQUAL(0, count);
  TEST_ASSERT_NULL(pmids);
}

void test_pubmed_parse_idlist_missing_idlist(void) {
  const char *json = "{ \"foo\": 123 }";

  char **pmids = NULL;
  int count = 0;

  int rc = pubmed_parse_idlist(json, &pmids, &count);

  TEST_ASSERT_NOT_EQUAL(0, rc);
}
