CC=gcc
CFLAGS=-std=c17 -Wextra -Wall -pedantic -D_FORTIFY_SOURCE=2 -O1 -Iinclude
LDFLAGS=-Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32
SRC=src
ENGINE=engineCore
BIN=bin
SRCS=$(wildcard $(SRC)/*.c)
ENGINESRCS=$(wildcard $(ENGINE)/*.c)
OBJS=$(SRCS:$(SRC)/%.c=$(BIN)/%.o)
ENGINEOBJS=$(ENGINESRCS:$(ENGINE)/%.c=$(BIN)/%.o)
EXEC=$(BIN)/main

all: $(EXEC) clean-objects

$(EXEC): $(OBJS) $(ENGINEOBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(ENGINEOBJS) $(LDFLAGS) lib/libraylib.a  
	
$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<  

$(BIN)/%.o: $(ENGINE)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean-objects:
	del /Q $(BIN)\*.o 

clean:
	del /Q $(BIN)\*.o $(EXEC)  
