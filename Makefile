CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11

# Include paths
INCLUDES := \
  -Isrc \
  -Isrc/tokenizer \
  -Isrc/repository \
  -Itests/unity/src

# =====================
# Application
# =====================

APP_NAME := app

APP_SRCS := \
  src/main.c \
  src/tokenizer/tokenizer.c \
  src/repository/repository_parser.c

# =====================
# Tests
# =====================

TEST_NAME := test_runner

TEST_SRCS := \
  tests/test_main.c \
  tests/test_tokenizer.c \
  tests/test_repository_parser.c \
  src/tokenizer/tokenizer.c \
  src/repository/repository_parser.c \
  tests/unity/src/unity.c

# =====================
# Rules
# =====================

.PHONY: all clean test

all: $(APP_NAME)

$(APP_NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(APP_SRCS) -o $(APP_NAME)

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME):
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRCS) -o $(TEST_NAME)

clean:
	rm -f $(APP_NAME) $(TEST_NAME)
