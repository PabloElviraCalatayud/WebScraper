CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = tests/unity

APP_SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/tokenizer/tokenizer.c

TEST_SRC = \
	$(TEST_DIR)/test_tokenizer.c \
	$(SRC_DIR)/tokenizer/tokenizer.c \
	$(UNITY_DIR)/src/unity.c

INCLUDES = \
	-I$(SRC_DIR) \
	-I$(SRC_DIR)/tokenizer \
	-I$(UNITY_DIR)/src

app:
	$(CC) $(CFLAGS) $(INCLUDES) $(APP_SRC) -o app

test:
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) -o test_tokenizer

clean:
	rm -f app test_tokenizer
