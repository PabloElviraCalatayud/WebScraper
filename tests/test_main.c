#include "unity.h"

/* Declaración de todos los tests */
void test_single_term(void);
void test_and_operator(void);

void test_parse_pubmed_lowercase(void);
void test_parse_pubmed_uppercase(void);
void test_parse_unknown_repo(void);
void test_repo_name(void);

void test_translate_single_term(void);
void test_translate_title_prefix(void);
void test_translate_abstract_prefix(void);
void test_translate_year_prefix(void);
void test_translate_and_operator(void);
void test_translate_or_operator(void);
void test_translate_parentheses(void) ;
void test_translate_complex_query(void);

void test_pubmed_url_simple_query(void);
void test_pubmed_url_with_spaces(void);
void test_pubmed_url_with_operators(void);
void test_pubmed_url_with_parentheses(void);
void test_pubmed_url_null_query(void);


/* Hooks globales */
void setUp(void) {}
void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();

  printf("\n-----------------TOKENIZER TEST-----------------\n");
  RUN_TEST(test_single_term);
  RUN_TEST(test_and_operator);

  printf("\n-----------------REPOSITORY PARSER TEST-----------------\n");
  RUN_TEST(test_parse_pubmed_lowercase);
  RUN_TEST(test_parse_pubmed_uppercase);
  RUN_TEST(test_parse_unknown_repo);
  RUN_TEST(test_repo_name);

  printf("\n-----------------UQL TRANSLATOR TEST-----------------\n");
  RUN_TEST(test_translate_single_term);
  RUN_TEST(test_translate_title_prefix);
  RUN_TEST(test_translate_abstract_prefix);
  RUN_TEST(test_translate_year_prefix);
  RUN_TEST(test_translate_and_operator);
  RUN_TEST(test_translate_or_operator);
  RUN_TEST(test_translate_parentheses);
  RUN_TEST(test_translate_complex_query);

  printf("\n-----------------PUBMED URL----------------\n");
  RUN_TEST(test_pubmed_url_simple_query);
  RUN_TEST(test_pubmed_url_with_spaces);
  RUN_TEST(test_pubmed_url_with_operators);
  RUN_TEST(test_pubmed_url_with_parentheses);
  RUN_TEST(test_pubmed_url_null_query);


  return UNITY_END();
}
