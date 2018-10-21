#!/usr/bin/make -f

DIR_EXEC := bin
DIR_EXEC_SRC := src
DIR_LIB := lib

VPATH := \
	$(DIR_EXEC_SRC) \
	$(DIR_LIB)

DIRS := \
	$(DIR_EXEC) \
	$(DIR_EXEC_SRC) \
	$(DIR_LIB)

CC := gcc

F_GENERAL := --std=c11
F_ERRORS := -Wall -Wextra -Wpedantic

C_FLAGS := \
	$(F_GENERAL) \
	$(F_ERRORS)

EXECS := $(patsubst %.c,$(DIR_EXEC)/%,$(notdir $(wildcard $(DIR_EXEC_SRC)/*.c)))

all: $(EXECS)

$(EXECS) : | $(DIRS)

$(DIR_EXEC)/% : %.c
	$(CC) $(C_FLAGS) $^ -o $@

$(DIRS):
	@[ -d $@ ] || mkdir -p $@
