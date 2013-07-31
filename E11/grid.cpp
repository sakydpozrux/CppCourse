#include "grid.h"


grid::grid( const grid& g )
	: xsize( g.xsize ),
	  ysize( g.ysize ),
	  c( new cell [g.xsize * g.ysize] )
{
	for (unsigned int x = 0; x < xsize; ++x)
		for (unsigned int y = 0; y < ysize; ++y)
			(*this)[x][y] = g[x][y];
}

void grid::operator = (const grid& g )
{
	xsize = g.xsize;
	ysize = g.ysize;

	cell* c_new = new cell [xsize * ysize];

	for (unsigned int x = 0; x < xsize; ++x)
		for (unsigned int y = 0; y < ysize; ++y)
			(*this)[x][y] = g[x][y];

	delete[] c;
	c = c_new;
}

grid::~grid( )
{
	delete[] c;
}


void grid::clear( )
{
	unsigned int size = xsize * ysize;
	for (unsigned int a = 0; a < size; ++a)
	{
		c[a].s0 = 0;
		c[a].s1 = 0;
	}
}

// It doesnt check bounds
void grid::add(unsigned int x, unsigned int y, const std::vector< std::vector< bool >> & pattern)
{
	x %= xsize;
	y %= ysize;

	int xvec = pattern[0].size();
	int yvec = pattern.size();

	for (int a = 0; a < pattern[0].size(); ++a)
		for (int b = 0; b < pattern.size(); ++b)
			(*this)[(x + a) % xsize][(y + b) % ysize].s0 = pattern[yvec - 1 - b][a];
}

void grid::plot() const {
	for (int y = 0; y < ysize; ++y)
		for (int x = 0; x < xsize; x++)
			if ( (*this)[x][y].s0 == true )
			{
				x -= xsize/2;
				y -= ysize/2;
				glBegin( GL_POLYGON );
					glVertex3f( x, y, 0 );
					glVertex3f( x + 1, y, 0 );
					glVertex3f( x + 1, y + 1, 0 );
					glVertex3f( x, y + 1, 0 );
				glEnd( );
				x += xsize/2;
				y += ysize/2;
			}

	glFlush();
}

void grid::nextgeneration()
{
	for (unsigned int x = 0; x < xsize; ++x)
		for (unsigned int y = 0; y < ysize; ++y)
		{
			unsigned int neightbours = 0;
			unsigned int left = x-1, right = x+1, up = y+1, down = y-1;

			if (x == 0) left = xsize - 1;
			else if (x == xsize-1) right = 0;

			if (y == 0) down = ysize - 1;
			else if (y == ysize-1) up = 0;

			neightbours += (*this)[left][up].s0;
			neightbours += (*this)[left][y].s0;
			neightbours += (*this)[left][down].s0;
			neightbours += (*this)[x][up].s0;
			neightbours += (*this)[x][down].s0;
			neightbours += (*this)[right][up].s0;
			neightbours += (*this)[right][y].s0;
			neightbours += (*this)[right][down].s0;

			// if (x == 2 && y == 10)
			// {
			// 	std::cout << neightbours << '\n';
			// 	std::cout << "left: " << left << '\n';
			// 	std::cout << "right: " << right << '\n';
			// 	std::cout << "down: " << down << '\n';
			// 	std::cout << "up: " << up << '\n';
			// }

			if ((*this)[x][y].s0)
			{
				if (neightbours >= 2 && neightbours <= 3 ) (*this)[x][y].s1 = 1;
				else (*this)[x][y].s1 = 0;
			}
			else 
			{
				if (neightbours == 3 ) (*this)[x][y].s1 = 1;
				else (*this)[x][y].s1 = 0;
			}
		}

	for (unsigned int x = 0; x < xsize; ++x)
		for (unsigned int y = 0; y < ysize; ++y)
			(*this)[x][y].s0 = (*this)[x][y].s1;
}

std::ostream& operator << ( std::ostream& stream, const grid& g)
{
	// for (unsigned int x = 0; x < g.xsize * g.ysize; ++x)
	// {
	// 	if (g.c[x].s0 == 1) stream << 'X';
	// 	else stream << '.';

	// 	if (x % g.ysize == 0) stream << '\n';
	// }
	// return stream;

	for (int y = g.ysize - 1; y >= 0; --y)
	{
		for (int x = 0; x < g.xsize; ++x)
		{
			if (g[x][y].s0 == 1) stream << 'X';
			else stream << '.';
		}

		stream << '\n';
	}

	return stream;
}