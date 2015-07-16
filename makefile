CC=cc
CCFlags=
SOURCES=main.c parser.c
OBJECTS=$(SOURCES:.c=.o)
OUT_FOLDER=bin

all: shell

shell: objects
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(OUT_FOLDER)/shell

objects: 
	$(CC) -c $(SOURCES)

parser:
	$(CC) $(CCFLAGS) parser.c -o $(OUT_FOLDER)/parser

cd:
	$(CC) $(CCFLAGS) builtins/cd.c -o $(OUT_FOLDER)/cd

clean:
	rm *.o
