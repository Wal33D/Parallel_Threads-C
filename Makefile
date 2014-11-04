CC = gcc
CFLAGS = -g -Wall
OBJECTS = PThreads.o
INCFLAGS = -lpthread
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

all: PThreads

PThreads: $(OBJECTS)
	$(CC) -o PThreads $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
