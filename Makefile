CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11
LIBS    := -lcurl -lxml2

INCLUDES := \
  -Isrc \
  -Isrc/tokenizer \
  -Isrc/repository \
  -Isrc/translator \
  -Isrc/utils \
  -Isrc/pubmed \
  -Isrc/csv \
  -Itests/unity/src

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

APP_NAME := app

APP_SRCS := \
  src/main.c \
  $(COMMON_SRCS)

.PHONY: all clean

all: $(APP_NAME)

$(APP_NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(APP_SRCS) -o $(APP_NAME) $(LIBS)

clean:
	rm -f $(APP_NAME)
