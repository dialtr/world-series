CXX=g++
CXXFLAGS=-Wall -Werror -std=c++17 -g

.PHONY:
all: series

.PHONY:
clean:
	-rm -f series *.o

.PHONY:
format:
	clang-format -style=Google -i *.cc

series: main.o
	$(CXX) $(CXXFLAGS) -o series $^

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<
