#!/usr/bin/make -f

DIR_EXEC := bin
DIR_EXEC_SRC := src
DIR_LIB := lib
DIR_GL3W := gl3w

vpath %.c\
	$(DIR_EXEC_SRC) \
	$(DIR_LIB)

DIRS := \
	$(DIR_EXEC) \
	$(DIR_EXEC_SRC) \
	$(DIR_LIB) \
	$(DIR_GL3W)

CC := gcc

F_GENERAL := --std=c11
F_DEBUG:= -g
F_ERRORS := -Wall -Wextra -Wpedantic
F_LIBS := -I$(DIR_LIB) -I$(DIR_GL3W)/include

F_GRAPHICS := -lGLEW -lglfw3 -lGL -lX11 -lXrandr -lXi -lXxf86vm \
							-ldl -lXinerama -lXcursor -lrt -lz

C_FLAGS := \
	$(F_GENERAL) \
	$(F_DEBUG) \
	$(F_ERRORS) \
	$(F_GRAPHICS) \
	$(F_LIBS)

EXECS := $(patsubst %.c,$(DIR_EXEC)/%,$(notdir $(wildcard $(DIR_EXEC_SRC)/*.c)))
FILES_LIB := $(wildcard $(DIR_LIB)/*)

# all recipe and executables.
# ---------------------------

all: $(EXECS)

$(EXECS) : $(FILES_LIB) Makefile | $(DIRS)

$(DIR_EXEC)/% : %.c
	$(CC) $(C_FLAGS) $(filter %.c,$^) -o $@

# gl3w related.
# -------------

%/gl3w_gen.py :
	git clone https://github.com/skaslev/gl3w $(DIR_GL3W)

%/gl3w.h : $(DIR_GL3W)/gl3w_gen.py
	cd $(dir $^) && python $(notdir $^)

# Directory management.
# ---------------------

$(DIR_GL3W) : $(DIR_GL3W)/include/GL/gl3w.h

$(DIRS):
	@[ -d $@ ] || mkdir -p $@

# Special targets.
# ----------------

.PRECIOUS : gl3w_gen.py
