MIX    := mix
CC     := gcc
CFLAGS += -pedantic-errors -O3 -Wall -Wextra

ERLANG_PATH := $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)

BUILD_DIR := priv
OBJ_DIR   := $(BUILD_DIR)
INCLUDE   := -I$(ERLANG_PATH) -Iinclude/
SRC       := $(wildcard src/*.c)
OBJS      := $(SRC:%.c=$(OBJ_DIR)/%.o)
TARGET    := linalg_nif.so

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -shared $(LDFLAGS) $(OBJS) -o $@

clean:
	-$(MIX) clean
	-rm -rf $(BUILD_DIR)

