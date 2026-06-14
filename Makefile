CC ?= gcc
CXX ?= g++
AR ?= ar
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -O2 -g -Iinclude
LDFLAGS ?=
OUT := out
KERNEL_SRCS := $(shell find kernel -name '*.c' | sort)
ASM_SRCS := $(shell find kernel -name '*.S' | sort)
CPP_SRCS := $(shell find services -name '*.cpp' | sort)
LIB_SRCS := $(shell find libs -name '*.c' | sort)
USER_SRCS := $(shell find userland -name '*.c' | sort)
TEST_SRCS := $(shell find tests -name '*.c' | sort)
OBJS := $(patsubst %.c,$(OUT)/%.o,$(KERNEL_SRCS) $(LIB_SRCS) $(USER_SRCS)) $(patsubst %.cpp,$(OUT)/%.o,$(CPP_SRCS))
TEST_BINS := $(patsubst tests/%.c,$(OUT)/tests/%,$(TEST_SRCS))

.PHONY: all clean test image docs
all: $(OUT)/bolun-host

$(OUT)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -std=c++17 -Wall -Wextra -Werror -O2 -g -Iinclude -c $< -o $@

$(OUT)/tools/mkmainos: tools/mkmainos.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/tools/gen_feature_docs: tools/gen_feature_docs.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/bolun-host: $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OUT)/tests/%: tests/%.c $(filter-out $(OUT)/userland/init/main.o,$(OBJS))
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

test: $(OUT)/tools/mkmainos $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo RUN $$t; $$t; done

image: all $(OUT)/tools/mkmainos
	$(OUT)/tools/mkmainos $(OUT)/bolun-host packaging/mainos.json $(OUT)/bolun-mainos.img

docs: $(OUT)/tools/gen_feature_docs
	$(OUT)/tools/gen_feature_docs

clean:
	rm -rf $(OUT)
