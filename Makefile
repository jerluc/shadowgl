SOURCEDIR=src
BINDIR=bin
BUILDDIR=build
EXECUTABLE=shadowgl
OBJECTS=$(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(wildcard $(SOURCEDIR)/*.c))
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADERS=$(wildcard $(SOURCEDIR)/*.h)
LIBS=-lglfw3 -framework OpenGL
CC=gcc
CFLAGS=-Wall -g -static -I$(SOURCEDIR)

ENABLE_LUAJIT?=1

ifeq ($(ENABLE_LUAJIT), 1)
	LIBS += -lluajit
	CFLAGS += -I/usr/local/include/luajit-2.0
	LDFLAGS += -pagezero_size 10000 -image_base 100000000
else
	LIBS += -llua
endif

.PHONY: default all clean

default: $(BINDIR)/$(EXECUTABLE)
all: default


$(BUILDDIR)/%.o: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(BUILDDIR)/$(EXECUTABLE) $(OBJECTS)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(LDFLAGS) -o $@

clean:
	-rm -rf $(BUILDDIR)/*
