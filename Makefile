CC=cc
CFLAGS=-Wall -g -std=c99
LIBS=-lreadline
SOURCES=shell.c parser.c builtin.c
OBJECTS_FOLDER=obj
OBJECTS=$(patsubst %, $(OBJECTS_FOLDER)/%, $(SOURCES:.c=.o))
OUT_FOLDER=bin
RM=rm -fr

all: $(OBJECTS) shell

$(OBJECTS_FOLDER)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJECTS)
	$(CC) -o $(OUT_FOLDER)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS_FOLDER)/* $(OUT_FOLDER)/*
