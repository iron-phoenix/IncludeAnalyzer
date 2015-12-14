CXX = g++
FLAGS = -std=c++11 -Wall
LDFLAGS = -lboost_filesystem -lboost_system
SOURCES = analyzer.cpp include_finder.cpp include_frequency.cpp node.cpp tree_printer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = analyzer

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) $(FLAGS) -c $<

clean:
	rm -f *.o analyzer
