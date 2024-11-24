# Choose the platform: "linux" or "windows"
PLATFORM ?= windows

# Compiler and Flags
CC=gcc
CFLAGS=-std=c17 -Wextra -Wall -pedantic -D_FORTIFY_SOURCE=2 -O1 -Iinclude

# Linker Flags based on platform
ifeq ($(PLATFORM), windows)
    LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32
else ifeq ($(PLATFORM), linux)
    LDFLAGS = -Llib -lraylib -lm -Wl,-rpath,$(PWD)/lib  # Embed the library path
else
    $(error Unsupported platform: $(PLATFORM))
endif

# Engine source and object files
ENGINE=engineCore
BIN=bin
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
ENGINESRCS=$(wildcard $(ENGINE)/*.c)
OBJS=$(SRCS:$(SRC)/%.c=$(BIN)/%.o)
ENGINEOBJS=$(ENGINESRCS:$(ENGINE)/%.c=$(BIN)/%.o)
EXEC=$(BIN)/main

# Default target (based on the selected platform)
all: $(EXEC) clean-objects

# Build executable for the selected platform
$(EXEC): $(OBJS) $(ENGINEOBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(ENGINEOBJS) $(LDFLAGS) lib/libraylib.a

# Rule for compiling source files (from SRC or ENGINE)
$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN)/%.o: $(ENGINE)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean object files (Linux)
clean-objects:
ifeq ($(PLATFORM), windows)
	del /Q $(BIN)\*.o
else
	rm -f $(BIN)/*.o
endif

# Clean everything (executables and object files)
clean:
ifeq ($(PLATFORM), windows)
	del /Q $(BIN)\*.o $(EXEC)
else
	rm -f $(BIN)/*.o $(EXEC)
endif
