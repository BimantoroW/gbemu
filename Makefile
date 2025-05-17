SRC_DIR = src
LIB_DIR = lib
OUT_DIR = bin
OUT_LIB_DIR = $(OUT_DIR)/shared
INCLUDE_DIR = include

MAIN_SRC = $(SRC_DIR)/main.c
LIB_SRC = $(wildcard $(LIB_DIR)/*.c)
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.h)

OBJ_OUT = $(patsubst $(LIB_DIR)/%.c,$(OUT_LIB_DIR)/%.o,$(LIB_SRC))
LIB_OUT = $(OUT_LIB_DIR)/libgbemu.so
EXE_OUT = $(OUT_DIR)/gbemu

CC = gcc
CPPFLAGS = -I./include/
CFLAGS = -Wall -pedantic -O3

all: $(EXE_OUT)

clean:
	rm -f $(OBJ_OUT)
	rm -f $(LIB_OUT)
	rm -f $(EXE_OUT)

$(EXE_OUT): $(MAIN_SRC) $(LIB_OUT)
	$(CC) $(CPPFLAGS) $(CFLAGS) -L$(OUT_LIB_DIR) -Wl,-rpath=$(OUT_LIB_DIR) -o $@ $< -lgbemu

$(LIB_OUT): $(OBJ_OUT)
	$(CC) -shared $^ -o $@

$(OUT_LIB_DIR)/%.o: $(LIB_DIR)/%.c $(INCLUDES)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -fpic -o $@ $<
