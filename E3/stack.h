#ifndef STACK_H
#define STACK_H
#include <iostream>

class stack
{
	unsigned int current_size;
	unsigned int current_capacity;
	double* tab;
		// class invariant is that tab is always
		// allocated with a block with current_capacity.

	void ensure_capacity( unsigned int c );
		// Ensure that stack has capacity of at least c.

	friend std::ostream& operator << ( std::ostream& stream, const stack& s );



	public:
		stack( );
			// Constructs empty stack.
		stack( const stack& s ); // These are the 3 life cycle methods:
		~stack( );
		void operator = ( const stack& s );
		void push( double d );
			// Use ensure_capacity, so that
			// pushing is always possible, as
			// long as memory is not full.

		void reset( unsigned int s ); // Resets the stack to length of
								// s < size( ).
		
		// PRECONDITION: i < current_size
		double operator [ ] ( unsigned int i ) const;
		double& operator [ ] ( unsigned int i );
			// Be careful, s[0] is equal to top of stack.
			// s[ s. size( ) - 1 ] is the deepest element.

		double top( ) const;
		double& top( );

		void pop( );
			// Remove one element from the stack. It’s OK to write
			// code that crashes, as long as you write clearly what are
			// your preconditions, so:
			// PRECONDITION: The stack is not empty.
		unsigned int size( ) const { return current_size; }
		bool nonempty( ) const { return current_size; }



};

#endif