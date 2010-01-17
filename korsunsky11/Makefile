# Generic Makefile compiling all cpp files as standalone executables

# compile everything with maximum warning level and debugging symbols
CXXFLAGS += -Wall -g -pedantic

ALL_TARGETS := 01_cardgame menutest

all: 01_cardgame

01_cardgame: 01_cardgame.o game.o menu.o
	$(CXX) $(CXXFLAGS) -o $@ $^

menutest: menutest.o menu.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(ALL_TARGETS) *.o

