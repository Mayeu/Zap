#
# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42):
# <mayeu.tik@gmail.com> and <pierrealain.toret@gmail.com> wrote this file. As 
# long as you retain this notice you can do whatever you want with this stuff. 
# If we meet some day, and you think this stuff is worth it, you can buy us a
# beer in return. Matthieu Maury & Pierre-Alain Toret
# ----------------------------------------------------------------------------
#

# Zap Makefile
#
# Project directory
PROJECT_DIR = .

# Source directory
SRC = $(PROJECT_DIR)/src
SRC_LIB = $(SRC)/libzap
SRC_ZAP = $(SRC)
SRC_TEST = $(SRC)/test

# Bin directory
BIN = $(PROJECT_DIR)/bin
BUILD = $(PROJECT_DIR)/build

# Object files
OBJS_LIB = $(addprefix $(BUILD)/, zpts.o)
OBJS_ZAP = $(addprefix $(BUILD)/, zap.o)
OBJS_TEST = #$(addprefix $(BUILD)/, test_zpts.o)
TEST_DEPS = #$(addprefix $(SRC_TEST), test_zpts.c)

#Compiler
CC = gcc
# GCC flags
CFLAGS = -ggdb -Werror -Wall -I$(SRC)/include

# By default indent, build the project, the project and the doc
all: link linktest indent doc

# Lib
lib: $(OBJS_LIB)

$(BUILD)/%.o: $(SRC_LIB)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Test
test: $(OBJS_TEST) lib

$(BUILD)/test.o: $(SRC_TEST)/test.c $(TEST_DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

# Zap
zap: $(OBJS_ZAP)

$(BUILD)/%.o: $(SRC_ZAP)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Link
link: $(BIN)/zap zap lib

$(BIN)/zap: $(OBJS_ZAP) $(OBJS_LIB)
	$(LD) $(ARCH) -o $@ $^

# Link Test
link: $(BIN)/testzap test lib

$(BIN)/testzap: $(OBJS_LIB) $(OBJS_TEST)
	$(LD) $(ARCH) -o $@ $^


# Indent everything
IDT_OPT=-gnu -bli0 -npcs -c33 -di16 -nut

indent:
	indent $(IDT_OPT) $(SRC)/include/*.h
	indent $(IDT_OPT) $(SRC_ZAP)/*.c
	indent $(IDT_OPT) $(SRC_ZAP)/*.h
	indent $(IDT_OPT) $(SRC_LIB)/*.c
	indent $(IDT_OPT) $(SRC_LIB)/*.h
	indent $(IDT_OPT) $(SRC_TEST)/*.c
	indent $(IDT_OPT) $(SRC_TEST)/*.h
