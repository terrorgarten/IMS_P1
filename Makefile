SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
BINS=$(SOURCES:.cpp=)

CFLAGS+=-MMD -lglut -lGLU -lGL #-lsimlib
CXXFLAGS+=-MMD -lglut -lGLU -lGL#-lsimlib

all: $(BINS)

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)

run: all
	./$(BINS)

-include $(DEPS)