CC := g++
CFLAGS := -g -Wall

BINDIR := bin

SRCDIR := src
SRCEXT := cpp
INCLUDE := -I src

BUILDDIR := build
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

T_DIR := target
T_SOURCES := $(shell find $(T_DIR) -type f -name *.$(SRCEXT))
T_OBJECTS := $(patsubst $(T_DIR)/%, $(BUILDDIR)/%, $(T_SOURCES:.$(SRCEXT)=.o))

C_TARGET := client
S_TARGET := server

all: $(C_TARGET) $(S_TARGET)

$(S_TARGET): $(OBJECTS) $(BUILDDIR)/server.o
	@echo "Linking server..."
	$(CC) $^ -o $(S_TARGET)
	mv $(S_TARGET) $(BINDIR)

$(C_TARGET): $(OBJECTS) $(BUILDDIR)/client.o
	@echo "Linking client..."
	$(CC) $^ -o $(C_TARGET)
	mkdir -p $(BINDIR)
	mv $(C_TARGET) $(BINDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(T_DIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "Cleaning ..."
	rm -r $(BUILDDIR) $(BINDIR)/$(S_TARGET) $(BINDIR)/$(C_TARGET)

.PHONY: clean
