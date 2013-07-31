 
make: main 

main: main.o
	g++ -g -Wall -O2 -std=c++0x main.o -o main 
	

main.o: main.cpp
	g++ -g -Wall -O2 -std=c++0x main.cpp -c

clean:
	rm -f *.o main
