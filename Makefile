SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard conten/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))

CC=clang++
CFLAGS=-g --std=c++11 -Wall -Wextra
LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer

EXECUTABLE=sdl-launcher

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb $(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR) $(EXECUTABLE)

.PHONY: all run debug clean
