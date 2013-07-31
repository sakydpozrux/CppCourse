#include <SFML/OpenGL.hpp>
#include <initializer_list>
#include <iostream>
#include <vector>



class grid {
	struct cell {
	bool s0; // Current state.
	bool s1; // Next state.	

	cell( )
		: s0( false ),
		  s1( false ) {}
	};

	unsigned int xsize;
	unsigned int ysize;
	cell* c;

public:
	// Points in the grid are indexed in the computer graphics way, // not in the matrix way.
	// (0,0) is the left bottom corner.
	// (x-1,0) is the right bottom corner.
	// (0,y-1) is the left top corner.
	// (x-1,y-1) is the right top corner.

	grid( unsigned int xsize, unsigned int ysize)
		: xsize( xsize ),
		  ysize( ysize ),
		  c( new cell [xsize * ysize] )
	{ }

	grid( const grid& g );
	void operator = (const grid& g );
	~grid( );

	cell* operator [] ( unsigned int x ) { return c + x * ysize; }

	const cell* operator [] ( unsigned int x ) const { return c + x * ysize; }

	void plot() const;

	void clear( );

	void add(unsigned int x, unsigned int y, const std::vector< std::vector< bool > > & );

	void nextgeneration();

	friend std::ostream& operator << ( std::ostream& stream, const grid& g);
};

std::ostream& operator << ( std::ostream& stream, const grid& g);
