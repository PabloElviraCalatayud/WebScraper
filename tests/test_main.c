#include "unity.h"

/* Declaración de todos los tests */
void test_single_term(void);
void test_and_operator(void);

void test_parse_pubmed_lowercase(void);
void test_parse_pubmed_uppercase(void);
void test_parse_unknown_repo(void);
void test_repo_name(void);

/* Hooks globales */
void setUp(void) {}
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();

  /* Tokenizer tests */
  printf("\n-----------------TOKENIZER TEST-----------------\n");
  RUN_TEST(test_single_term);
  RUN_TEST(test_and_operator);

  /* Repository parser tests */
  printf("\n-----------------REPOSITORY PARSER TEST-----------------\n");
  RUN_TEST(test_parse_pubmed_lowercase);
  RUN_TEST(test_parse_pubmed_uppercase);
  RUN_TEST(test_parse_unknown_repo);
  RUN_TEST(test_repo_name);

  return UNITY_END();
}
