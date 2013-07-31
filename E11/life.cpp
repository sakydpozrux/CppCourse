#include <iostream>
#include <vector>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "grid.h"


int ifUseRandomGenerator = 1;
int ifTerminalVersion = 0;

int gridSizeX = 90;
int gridSizeY = 50;

const int speed = 10; // less is faster

int main (int argc, char const* argv[])
{	
	if (argc >= 3) // ./life 1 1 <---- random generator + terminal version
	{
		ifUseRandomGenerator = static_cast<int>(atoi(argv[1]));
		ifTerminalVersion = static_cast<int>(atoi(argv[2]));
	}
	
	if (argc == 4) // ./life 1 1 10 <---- random generator + terminal version + size 10x10
	{
		gridSizeX = static_cast<int>(atoi(argv[3]));
		gridSizeY = static_cast<int>(atoi(argv[3]));
	}
	else if (argc == 5) // ./life 1 1 30 20 <---- random generator + terminal version + size 30x20
	{
		gridSizeX = static_cast<int>(atoi(argv[3]));
		gridSizeY = static_cast<int>(atoi(argv[4]));
	}

	if (ifTerminalVersion)
	{
		if (gridSizeX > 32) gridSizeX = 32;
		if (gridSizeY > 32) gridSizeY = 32;
	}

	grid g(gridSizeX, gridSizeY);

	if (ifUseRandomGenerator)
	{
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0,1);

		for (int x = 0; x < gridSizeX; ++x)
			for (int y = 0; y < gridSizeY; ++y)
				if (distribution(generator)) g.add(x, y, { {1} });
	}
	else // use manual element adding
	{
		std::vector< std::vector< bool > > glider {
			{ 0, 1, 0 },
			{ 0, 0, 1 },
			{ 1, 1, 1 }
		};

		std::vector< std::vector< bool > > rpentomino {
			{ 0, 1, 1 },
			{ 1, 1, 0 },
			{ 0, 1, 0 }
		};

		std::vector< std::vector< bool > > acorn {
			{ 0, 1, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0, 0 },
			{ 1, 1, 0, 0, 1, 1, 1 }
		};

		g.add(48, 48, glider);
		g.add(67, 22, rpentomino);
		g.add(14, 74, acorn);
	}

	if (ifTerminalVersion)
	{
		clock_t t = clock();

		while(1) if( t < clock() )
			{
				std::cout << g << '\n';
				g.nextgeneration();
				t += 100000;
			}
	}
	else // Graphics version
	{
		int windowSizeX = gridSizeX;
		int windowSizeY = gridSizeY;

		while (windowSizeX < 500)
		{
			windowSizeX += windowSizeX/2;
			windowSizeY += windowSizeY/2;
		}


		sf::Window window( sf::VideoMode( windowSizeX, windowSizeY ), "Game of Life" );
		window.setVerticalSyncEnabled(true);

		glClearColor( 0.05, 0.05, 0.05, 1.0 );
		glClearDepth( 1.0 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		glScalef( 1.0 / (gridSizeX/2), 1.0 / (gridSizeY/2), 1.0 );


	    bool running = true;
		int frames = 0;
		glColor3f( 0.6, 0.7, 1 );

        // UNCOMMENT LINE BELOW TO MAKE VALGRIND TESTS POSSIBLE
        // ALSO IN LINES 135-136
        //int generations = 0;
	    while (running)
	    {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					running = false;
				else if (event.type == sf::Event::Resized)
					glViewport(0, 0, event.size.width, event.size.height);
			}

			if (frames >= speed)
			{
                // UNCOMMENT LINES BELOW TO MAKE VALGRIND TESTS POSSIBLE
                // ALSO IN LINE 120
                //++generations; 
                //if (generations > 50) return 0;
				frames = 0;
				g.nextgeneration();
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			g.plot();
			frames++;

	        window.display();
	    }
	}

	return 0;
}
