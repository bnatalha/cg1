#
# Originally from https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
#

CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/main

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11 -lstdc++fs
# CFLAGS := -Wall -std=c++17
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	@mkdir -p data/out
	@echo " $(CC) $^ -o $(TARGET) -std=c++17 -lstdc++fs"; $(CC) $^ -o $(TARGET) -std=c++17 -lstdc++fs

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(INC) -c -o $@ $< $(CFLAGS)"; $(CC) $(INC) -c -o $@ $< $(CFLAGS)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean