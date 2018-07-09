CXX=g++
CXXFLAGS=-std=c++11 -DNDEBUG
main: main.o
	$(CXX) -o main main.o $(CXXFLAGS)

main.o:
	$(CXX) -c main.cpp $(CXXFLAGS)

clean:
	rm -rf *.o main
