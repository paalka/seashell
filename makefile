CC=cc
CCFlags=
SOURCES=main.c parser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=seashell

all: shell

shell: objects
	$(CC) $(CCFLAGS) $(OBJECTS) -o shell

objects: 
	$(CC) -c $(SOURCES)

clean:
	rm *.o
