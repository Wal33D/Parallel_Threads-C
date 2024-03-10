CC = gcc
CFLAGS =
OBJECTS = build/PThreads.o
INCFLAGS = 
LDFLAGS =
LIBS =  -lpthread
BUILDDIR = build

all: $(BUILDDIR)/PThreads

$(BUILDDIR)/PThreads: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES: .c .cc .C .cpp .o

$(BUILDDIR)/%.o : %.c
	mkdir -p $(BUILDDIR)
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/PThreads
