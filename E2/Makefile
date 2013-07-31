main: main.o rational.o vector.o
	g++ -std=c++0x -o main main.o vector.o rational.o

main.o: main.cpp rational.h vector.h
	g++ -std=c++0x -c -o main.o main.cpp

rational.o: rational.cpp rational.h
	g++ -std=c++0x -c -o rational.o rational.cpp

vector.o: vector.cpp vector.h rational.h
	g++ -std=c++0x -c -o vector.o vector.cpp

clean:
	rm -f *.o main *.exe
