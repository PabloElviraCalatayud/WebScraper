#include "unity.h"
#include "repository_parser.h"

void test_parse_pubmed_lowercase(void) {
  Repository r = parse_repository("pubmed");
  TEST_ASSERT_EQUAL(REPO_PUBMED, r);
}

void test_parse_pubmed_uppercase(void) {
  Repository r = parse_repository("PubMed");
  TEST_ASSERT_EQUAL(REPO_PUBMED, r);
}

void test_parse_unknown_repo(void) {
  Repository r = parse_repository("ieee");
  TEST_ASSERT_EQUAL(REPO_UNKNOWN, r);
}

void test_repo_name(void) {
  TEST_ASSERT_EQUAL_STRING("PubMed", repo_name(REPO_PUBMED));
  TEST_ASSERT_EQUAL_STRING("Unknown", repo_name(REPO_UNKNOWN));
}
