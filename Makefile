CXXFLAGS=-O2 -g -std=gnu++20

main: main.o dispatch.o
	clang++ $(CXXFLAGS) main.o dispatch.o -o main

main.o: main.cpp common.hpp
	clang++ $(CXXFLAGS) main.cpp -c -o main.o

dispatch.o: dispatch.cpp common.hpp
	clang++ $(CXXFLAGS) dispatch.cpp -c -o dispatch.o

clean:
	rm -rf main.o dispatch.o main
