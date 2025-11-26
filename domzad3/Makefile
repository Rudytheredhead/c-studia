CXX = g++
CXXFLAGS = -Wall
LFLAGS =
OBJS = run.o Analyzer.o
all: prog
prog: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
clean:
	rm -f *.o prog
.PHONY: all clean
