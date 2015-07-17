CC=cc
CFLAGS=-Wall -g
LIBS=-lreadline
SOURCES=shell.c parser.c
OBJECTS_FOLDER=obj
OBJECTS=$(patsubst %, $(OBJECTS_FOLDER)/%, $(SOURCES:.c=.o))
OUT_FOLDER=bin
BUILTINS=builtins
RM=rm -fr
DEPS=

all: $(OBJECTS) shell cd

$(OBJECTS_FOLDER)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJECTS)
	$(CC) -o $(OUT_FOLDER)/$@ $^ $(CFLAGS) $(LIBS)

cd:
	$(CC) $(BUILTINS)/$@.c -o $(OUT_FOLDER)/$@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJECTS_FOLDER)/* $(OUT_FOLDER)/*
