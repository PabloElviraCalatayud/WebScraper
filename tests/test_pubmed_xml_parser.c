#include "unity.h"
#include "pubmed_xml_parser.h"
#include "pubmed_fetch.h"

#include <stdlib.h>
#include <string.h>

void test_parse_single_article(void) {
  const char *xml =
    "<PubmedArticleSet>"
      "<PubmedArticle>"
        "<MedlineCitation>"
          "<Article>"
            "<ArticleTitle>Cancer therapy advances</ArticleTitle>"
            "<Abstract>"
              "<AbstractText>This is an abstract.</AbstractText>"
            "</Abstract>"
            "<AuthorList>"
              "<Author>"
                "<LastName>Smith</LastName>"
                "<ForeName>John</ForeName>"
              "</Author>"
            "</AuthorList>"
          "</Article>"
        "</MedlineCitation>"
        "<PubmedData>"
          "<ArticleIdList>"
            "<ArticleId IdType=\"doi\">10.1234/example</ArticleId>"
          "</ArticleIdList>"
        "</PubmedData>"
      "</PubmedArticle>"
    "</PubmedArticleSet>";

  PubMedArticle *articles = NULL;
  int count = 0;

  int rc = pubmed_parse_efetch_xml(xml, &articles, &count);

  TEST_ASSERT_EQUAL_INT(0, rc);
  TEST_ASSERT_EQUAL_INT(1, count);
  TEST_ASSERT_NOT_NULL(articles);

  TEST_ASSERT_EQUAL_STRING("Cancer therapy advances", articles[0].title);
  TEST_ASSERT_EQUAL_STRING("This is an abstract.", articles[0].abstract);
  TEST_ASSERT_EQUAL_STRING("John Smith", articles[0].authors);
  TEST_ASSERT_EQUAL_STRING("10.1234/example", articles[0].doi);

  pubmed_free_articles(articles, count);
}

void test_parse_multiple_articles(void) {
  const char *xml =
    "<PubmedArticleSet>"
      "<PubmedArticle>"
        "<Article>"
          "<ArticleTitle>Title One</ArticleTitle>"
          "<Abstract><AbstractText>Abstract One</AbstractText></Abstract>"
          "<AuthorList>"
            "<Author><LastName>A</LastName><ForeName>X</ForeName></Author>"
          "</AuthorList>"
        "</Article>"
        "<PubmedData>"
          "<ArticleIdList>"
            "<ArticleId IdType=\"doi\">doi-1</ArticleId>"
          "</ArticleIdList>"
        "</PubmedData>"
      "</PubmedArticle>"

      "<PubmedArticle>"
        "<Article>"
          "<ArticleTitle>Title Two</ArticleTitle>"
          "<Abstract><AbstractText>Abstract Two</AbstractText></Abstract>"
          "<AuthorList>"
            "<Author><LastName>B</LastName><ForeName>Y</ForeName></Author>"
            "<Author><LastName>C</LastName><ForeName>Z</ForeName></Author>"
          "</AuthorList>"
        "</Article>"
        "<PubmedData>"
          "<ArticleIdList>"
            "<ArticleId IdType=\"doi\">doi-2</ArticleId>"
          "</ArticleIdList>"
        "</PubmedData>"
      "</PubmedArticle>"
    "</PubmedArticleSet>";

  PubMedArticle *articles = NULL;
  int count = 0;

  int rc = pubmed_parse_efetch_xml(xml, &articles, &count);

  TEST_ASSERT_EQUAL_INT(0, rc);
  TEST_ASSERT_EQUAL_INT(2, count);

  TEST_ASSERT_EQUAL_STRING("Title One", articles[0].title);
  TEST_ASSERT_EQUAL_STRING("X A", articles[0].authors);

  TEST_ASSERT_EQUAL_STRING("Title Two", articles[1].title);
  TEST_ASSERT_EQUAL_STRING("Y B; Z C", articles[1].authors);

  pubmed_free_articles(articles, count);
}

void test_parse_missing_optional_fields(void) {
  const char *xml =
    "<PubmedArticleSet>"
      "<PubmedArticle>"
        "<Article>"
          "<ArticleTitle>Only Title</ArticleTitle>"
        "</Article>"
      "</PubmedArticle>"
    "</PubmedArticleSet>";

  PubMedArticle *articles = NULL;
  int count = 0;

  int rc = pubmed_parse_efetch_xml(xml, &articles, &count);

  TEST_ASSERT_EQUAL_INT(0, rc);
  TEST_ASSERT_EQUAL_INT(1, count);

  TEST_ASSERT_EQUAL_STRING("Only Title", articles[0].title);
  TEST_ASSERT_NULL(articles[0].abstract);
  TEST_ASSERT_NULL(articles[0].authors);
  TEST_ASSERT_NULL(articles[0].doi);

  pubmed_free_articles(articles, count);
}

void test_parse_no_articles(void) {
  const char *xml =
    "<PubmedArticleSet>"
    "</PubmedArticleSet>";

  PubMedArticle *articles = NULL;
  int count = 0;

  int rc = pubmed_parse_efetch_xml(xml, &articles, &count);

  TEST_ASSERT_EQUAL_INT(0, rc);
  TEST_ASSERT_EQUAL_INT(0, count);
  TEST_ASSERT_NULL(articles);
}
