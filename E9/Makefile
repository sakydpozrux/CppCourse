main: main.o fifteen.o move.o
	g++ -g -std=c++0x main.o fifteen.o move.o -o main

%.o: %.cpp
	g++ -g -std=c++0x -c $< -o $@

clean:
	rm -f *.o main *.exe
 
