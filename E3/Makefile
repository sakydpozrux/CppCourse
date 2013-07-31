main: main.o stack.o
	g++ -std=c++0x -g -o main main.o stack.o

main.o: main.cpp stack.h
	g++ -std=c++0x -g -c -o main.o main.cpp

rational.o: stack.cpp stack.h
	g++ -std=c++0x -g -c -o stack.o stack.cpp

clean:
	rm -f *.o main *.exe
