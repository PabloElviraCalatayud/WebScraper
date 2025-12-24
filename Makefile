CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc -Itests/unity
CFLAGS += -D_POSIX_C_SOURCE=200809L

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = tests/unity

SRC_FILES = \
  $(SRC_DIR)/tokenizer.c \
  $(SRC_DIR)/main.c

TEST_FILES = \
  $(TEST_DIR)/test_tokenizer.c \
  $(SRC_DIR)/tokenizer.c \
  $(UNITY_DIR)/unity.c

APP = app
TEST_APP = test_tokenizer

.PHONY: all clean test

all: $(APP)

$(APP): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_APP)
	./$(TEST_APP)

$(TEST_APP): $(TEST_FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(APP) $(TEST_APP)
