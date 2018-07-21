CXX=g++
CXXFLAGS='-std=c++11' -DNDEBUG -g
OUTPUT= ./debug

all: kasa

OBJS = kasa.tab.o  	\
       main.o    		\
       lex.o  	\
	   ast.o 			\
	   object.o 		\
	   kasa_assert.o 	\
	   kasa_log.o		\
	   interpreter.o 	\
	   object_code.o	\

main: main.o
	$(CXX) -o main main.o $(CXXFLAGS)

kasa.tab.cpp: kasa.y
	bison -d -o $@ $^

lex.cpp: kasa.l ast.h
	flex --nounistd -o $@ $^ 

kasa: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

clean:
	rm -rf *.o kasa  lex.* kasa.tab.*
