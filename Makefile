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
F_LIBS := -I$(DIR_LIB)

C_FLAGS := \
	$(F_GENERAL) \
	$(F_ERRORS) \
	$(F_LIBS)

EXECS := $(patsubst %.c,$(DIR_EXEC)/%,$(notdir $(wildcard $(DIR_EXEC_SRC)/*.c)))
FILES_LIB := $(wildcard $(DIR_LIB)/*)

all: $(EXECS)

$(EXECS) : $(FILES_LIB) | $(DIRS)

$(DIR_EXEC)/% : %.c
	$(CC) $(C_FLAGS) $(filter %.c,$^) -o $@

$(DIRS):
	@[ -d $@ ] || mkdir -p $@
