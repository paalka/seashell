CC=c++
CCFlags=
SOURCES=main.cpp parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=seashell


all: shell

shell: objects
	$(CC) $(CCFLAGS) $(OBJECTS)

objects: 
	c++ -c $(SOURCES)

clean:
	rm *o
