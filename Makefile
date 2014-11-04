CC = gcc
CFLAGS =
OBJECTS = PThreads.o
INCFLAGS = 
LDFLAGS =
LIBS =  -lpthread

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