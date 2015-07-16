CC = cc
CFLAGS = -Wall -g
LIBS = -lreadline
SOURCES = shell.c parser.c
OBJECTS = $(SOURCES:.c=.o)
OUT_FOLDER = bin
BUILTINS = builtins
DEPS =

all: objects shell parser cd

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJECTS)
	$(CC) -o $(OUT_FOLDER)/$@ $^ $(CFLAGS) $(LIBS)

parser: $(OBJECTS)
	$(CC) $(CFLAGS) $< $@.c -o $(OUT_FOLDER)/$@

cd:
	$(CC) $(CFLAGS) $(BUILTINS)/$@.c -o $(OUT_FOLDER)/$@

.PHONY: clean
clean:
	$(RM) *.o
