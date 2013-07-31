#include "stack.h"

void stack::ensure_capacity( unsigned int c )
{
	if( current_capacity < c )
	{
		// New capacity will be the greater of c and
		// 2 * current_capacity.
		if( c < 2 * current_capacity )
			c = 2 * current_capacity;
		
		double* newtab = new double[ c ];
		for( unsigned int i = 0; i < current_size; ++ i )
			newtab[i] = tab[i];
		
		current_capacity = c;
		delete[] tab;
		tab = newtab;
	}
}

stack::stack()
{
	current_size = 0;
	current_capacity = 8;
	tab = new double[8];
}

stack::stack( const stack& s ) // copy constructor
{
	current_size = s.current_size;
	current_capacity = s.current_capacity;
	tab = new double[s.current_capacity];

	for( unsigned int i = 0; i < s.current_capacity; ++ i )
			tab[i] = s.tab[i];
}

stack::~stack( )
{
	delete [] tab;
}


void stack::operator = ( const stack& s )
{
  current_size = s.current_size;
  current_capacity = s.current_capacity;

  // ensure_capacity here would copy the old tab and then I would must to copy it again from new tab

  double* newtab = new double[current_capacity];
  for( unsigned int i = 0; i < current_size; ++ i )
    newtab[i] = s.tab[i];
  
  delete [] tab;
  tab = newtab;
}


void stack::push( double d )
	// Use ensure_capacity, so that
	// pushing is always possible, as
	// long as memory is not full.
{
	ensure_capacity(current_size + 1);
	tab[current_size] = d;
	//tab[current_size++] = d; ???
	current_size++;
}

void stack::reset( unsigned int s ) // Resets the stack to length of
						// s < size( ).
{
	double* newtab = new double[ s ];
	for( unsigned int i = 0; i < s; ++ i )
		newtab[i] = tab[i];
	
	current_capacity = s;
	delete[] tab;
	tab = newtab;
}

double stack::operator [ ] ( unsigned int i ) const
{
	return tab[current_size - i - 1];
}

double& stack::operator [ ] ( unsigned int i )
	// Be careful, s[0] is equal to top of stack.
	// s[ s. size( ) - 1 ] is the deepest element.
{
	return tab[current_size - i - 1];
}

double stack::top( ) const
{
	return tab[current_size - 1];
}

double& stack::top( )
{
	return tab[current_size - 1];
}

void stack::pop( )
	// Remove one element from the stack. It’s OK to write
	// code that crashes, as long as you write clearly what are
	// your preconditions, so:
	// PRECONDITION: The stack is not empty.
{
	current_size--;
	// reset(current_size); ??? not time optimal
}

std::ostream& operator << ( std::ostream& stream, const stack& s )
{
	for( unsigned int i = 0; i < s.current_size; ++ i )
		stream << ' ' << s.tab[i];

	stream << std::endl;

	return stream;
}
