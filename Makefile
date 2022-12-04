SOURCES=$(wildcard *.cpp)
BINS=$(SOURCES:.cpp=)

CC=g++
CXX-FLAGS+= -Werror -Wall -pedantic #-lsimlib
TRAILING+=-lglut -lGLU -lGL

all: model.o
	$(CC) $(CXX-FLAGS) model.o cell.hpp spread_matrix.hpp definitions.hpp -o model $(TRAILING)

model.o: model.cpp model.hpp
	$(CC) $(CXX-FLAGS) -c model.cpp model.hpp

.PHONY: clean

clean:
	$(RM) *.o *.gch model

run: all
	./$(BINS)
