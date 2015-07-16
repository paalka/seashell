CC=cc
CFLAGS=-Wall -g
LIBS=-lreadline
SOURCES=shell.c parser.c
OBJECTS=$(SOURCES:.c=.o)
OUT_FOLDER=bin
BUILTINS=builtins
RM=rm -fr
DEPS=

all: $(OBJECTS) shell cd

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJECTS)
	$(CC) -o $(OUT_FOLDER)/$@ $^ $(CFLAGS) $(LIBS)

cd:
	$(CC) $(BUILTINS)/$@.c -o $(OUT_FOLDER)/$@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) *.o $(OUT_FOLDER)/*
