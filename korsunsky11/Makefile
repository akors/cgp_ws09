# Generic Makefile compiling all cpp files as standalone executables

# compile everything with maximum warning level and debugging symbols
CXXFLAGS += -Wall -g -pedantic

ALL_TARGETS := 01_cardgame

all: $(ALL_TARGETS)

01_cardgame: 01_cardgame.cpp game.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(ALL_TARGETS)

