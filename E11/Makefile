Flags = -g -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
Link = -lGL -lGLU -lsfml-graphics -lsfml-window -lsfml-system
CPP = g++

life: life.o grid.o
	$(CPP) $(Flags) grid.o life.o $(Link) -o life 

life.o: life.cpp
	$(CPP) -c $(Flags) life.cpp -o life.o

grid.o: grid.cpp
	$(CPP) -c $(Flags) grid.cpp -o grid.o

clean:
	rm *.o life
