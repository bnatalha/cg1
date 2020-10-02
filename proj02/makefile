#
# Originally from https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
#

# CC := g++
CC := clang++
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/main

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11
INC := -Isrc -Isrc/external -Isrc/core

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)/external $(BUILDDIR)/core
	@mkdir -p (CC) $^ -o $(TARGET) $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p (CC) $^ -o $(TARGET) $(CFLAGS)
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

val:
	valgrind ./$(TARGET)

.PHONY: clean, val, libs
