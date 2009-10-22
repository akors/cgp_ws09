# Generic Makefile compiling all cpp files as standalone executables

ALL_TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))

all: $(ALL_TARGETS)

clean:
	rm -f $(ALL_TARGETS)

