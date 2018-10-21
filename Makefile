#!/usr/bin/make -f

DIR_EXEC := bin
DIR_EXEC_SRC := src
DIR_LIB := lib

VPATH = $(DIR_EXEC_SRC)

DIRS := \
	$(DIR_EXEC) \
	$(DIR_EXEC_SRC) \
	$(DIR_LIB)

CC := gcc

EXECS := $(patsubst %.c,$(DIR_EXEC)/%,$(notdir $(wildcard $(DIR_EXEC_SRC)/*.c)))

F_GENERAL := --std=c11
F_ERRORS := -Wall -Wextra -Wpedantic

C_FLAGS := \
	$(F_GENERAL) \
	$(F_ERRORS)

all: $(EXECS) | $(DIRS)

$(DIR_EXEC)/% : %.c
	$(CC) $(C_FLAGS) $^ -o $@

$(DIRS):
	@[ -d $@ ] || mkdir -p $@
