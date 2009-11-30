# Generic Makefile compiling all cpp files as standalone executables

LIBS = X11

# compile everything with maximum warning level and debugging symbols
CXXFLAGS += -Wall -g $(patsubst %,-l%,$(LIBS))

ALL_TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))

all: $(ALL_TARGETS)

clean:
	rm -f $(ALL_TARGETS)

