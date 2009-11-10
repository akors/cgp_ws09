# Generic Makefile compiling all cpp files as standalone executables

# compile everything with maximum warning level and debugging symbols
CXXFLAGS += -Wall -g

ALL_TARGETS := $(patsubst %.cpp,%,$(wildcard *.cpp))

all: $(ALL_TARGETS)

clean:
	rm -f $(ALL_TARGETS)

