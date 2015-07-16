CC = cc
CFLAGS = -Wall -g
LIBS = -lreadline
SOURCES = shell.c parser.c
OBJECTS = $(SOURCES:.c=.o)
OUT_FOLDER = bin
BUILTINS = builtins
DEPS =

all: $(OBJECTS) shell parser cd

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

shell: $(OBJECTS)
	$(CC) -o $(OUT_FOLDER)/$@ $^ $(CFLAGS) $(LIBS)

parser: $(OBJECTS)
	$(CC) $< $@.c -o $(OUT_FOLDER)/$@ $(CFLAGS) $(LIBS)

cd:
	$(CC) $(BUILTINS)/$@.c -o $(OUT_FOLDER)/$@ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) *.o
