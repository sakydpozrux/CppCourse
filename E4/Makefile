
main : tree.o main.o
	g++ -g -o main tree.o main.o

tree.o : tree.cpp tree.h
	g++ -g -c -o tree.o -std=c++0x tree.cpp

main.o : main.cpp tree.h
	g++ -g -c -o main.o -std=c++0x main.cpp

clean :
	rm main *.o
