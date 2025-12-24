CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LIBS := -lcurl -lxml2

# =====================
# Include paths
# =====================

INCLUDES := \
  -Isrc \
  -Isrc/tokenizer \
  -Isrc/repository \
  -Isrc/translator \
  -Isrc/utils \
  -Isrc/pubmed \
  -Isrc/csv \
  -Itests/unity/src

# =====================
# Common sources (NO main)
# =====================

COMMON_SRCS := \
  src/tokenizer/tokenizer.c \
  src/repository/repository_parser.c \
  src/translator/translator.c \
  src/pubmed/pubmed_url.c \
  src/pubmed/pubmed_fetch.c \
  src/pubmed/pubmed_xml_parser.c \
  src/csv/csv_writer.c \
  src/utils/csv_to_json.c \
  src/utils/utils.c

# =====================
# Application
# =====================

APP_NAME := app

APP_SRCS := \
  src/main.c \
  $(COMMON_SRCS)

# =====================
# Tests
# =====================

TEST_NAME := test_runner

TEST_SRCS := \
  tests/test_main.c \
  tests/test_tokenizer.c \
  tests/test_repository_parser.c \
  tests/test_translator.c \
  tests/test_pubmed_url.c \
  tests/test_pubmed_fetch.c \
  tests/test_pubmed_xml_parser.c \
  $(COMMON_SRCS) \
  tests/unity/src/unity.c

# =====================
# Rules
# =====================

.PHONY: all clean test

all: $(APP_NAME)

$(APP_NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(APP_SRCS) -o $(APP_NAME) $(LIBS)

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRCS) -o $(TEST_NAME) $(LIBS)

clean:
	rm -f $(APP_NAME) $(TEST_NAME)
