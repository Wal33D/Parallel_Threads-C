CC = gcc
CFLAGS = -Wall -g -Iinclude
TARGET = pthreads
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Update the SRC variable if necessary
SRC = $(SRCDIR)/pthreads.c $(SRCDIR)/utils.c

# Update OBJ to place object files in the build directory
OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

all: $(BUILDDIR) $(BUILDDIR)/$(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Update this rule to place the executable in the build directory
$(BUILDDIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(BUILDDIR) # Also remove the build directory on clean

# Update the pattern rule for object files to use the build directory
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
