SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
BINS=$(SOURCES:.cpp=)

#CFLAGS+=-MMD #-lsimlib
#CXXFLAGS+=-MMD #-lsimlib

all: $(BINS)

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)

run: all
	./$(BINS)

-include $(DEPS)