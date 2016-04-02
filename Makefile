SOURCEDIR=src
LIBSDIR=libs
BUILDDIR=build
EXECUTABLE=shadowgl
SOURCES=$(wildcard $(SOURCEDIR)/**/*.c $(SOURCEDIR)/*.c)
SOURCES+=$(wildcard $(LIBSDIR)/*/src/*.c $(LIBSDIR)/*/src/**/*.c)
HEADERS=$(wildcard $(SOURCEDIR)/**/*.h $(SOURCEDIR)/*.h)
HEADERS+=$(wildcard $(LIBSDIR)/*/include/*.h $(LIBSDIR)/*/include/**/*.h)
INCLUDEDIRS=$(wildcard $(LIBSDIR)/*/include)
INCLUDES=$(foreach dir,$(INCLUDEDIRS),-I$(dir))
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
CC=gcc
CFLAGS=-Wall -g -static $(INCLUDES)
USE_LUAJIT?=0

ifeq ($(USE_LUAJIT), 1)
	LUA=luajit
	CFLAGS+=-DLUAJIT
else
	LUA=lua
endif

CFLAGS+=$(shell pkg-config --cflags glfw3 $(LUA))
LIBS=$(shell pkg-config --libs glfw3 $(LUA))

UNAME=$(shell uname -s)

ifeq ($(UNAME),Darwin)
	LIBS+=-framework OpenGL
	ifeq ($(USE_LUAJIT), 1)
		# This is a special option for linking against LuaJIT on OS X
		# See <http://luajit.org/install.html> for more info
		LDFLAGS=-pagezero_size 10000 -image_base 100000000
	endif
else
	LIBS+=-lGL
endif

.PHONY: default all clean

default: $(BUILDDIR)/$(EXECUTABLE)
all: default
dev: clean all run
run:
	$(BUILDDIR)/$(EXECUTABLE)

print-%:
	@echo $* = $($*)

.PRECIOUS: $(BUILDDIR)/$(EXECUTABLE) $(OBJECTS)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) $(LDFLAGS) -o $@

clean:
	-rm -rf $(BUILDDIR)/*
	-rm -rf $(OBJECTS)
