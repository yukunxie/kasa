CXX=g++ -g
CXXFLAGS= -std=c++11 -DNDEBUG
OUTPUT= ./debug

all: kasa

OBJS = kasa_parser.o  \
       main.o    \
       kasa_tokens.o  \
	   ast.o \

main: main.o
	$(CXX) -o main main.o $(CXXFLAGS)

kasa_parser.cpp: kasa.y
	bison -d -o $@ $^

kasa_tokens.cpp: kasa.l ast.h
	flex -o $@ $^ 


kasa: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

clean:
	rm -rf *.o kasa kasa_parser.cpp kasa_parser.hpp  kasa_tokens.cpp
