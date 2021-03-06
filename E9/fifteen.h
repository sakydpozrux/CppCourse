#ifndef __FIFTEEN_H__
#define __FIFTEEN_H__

#include "move.h"
#include <vector>
#include <iostream>

typedef unsigned int uint;

class fifteen 
{
   unsigned int table [4][4];
      // We use the numbers 1 .. 15 for the tiles,
      // and 0 for the missing tile. 

   unsigned int x;
   unsigned int y; 
      // Position of the open place. If you want, you can omit these
      // fields, but then you have to search for the open place, everytime
      // a move is made. 
   
   std::vector< move > history;
      // We store in this vector how the state is obtained from
      // the starting state. 

public: 
   fifteen( );
      // Default constructor constructs the puzzle in solved position.

   fifteen( unsigned int[4][4] );

   unsigned int distance( ) const;
      // Estimated distance from solution. 
      // (See the wikipedia article for some reasomable measures.) 
        
   void makemove( move ) throw( illegalmove );
      // Note that throw( ) does not mean the same in C++ as
      // in Java. In Java, it is guaranteed that only exceptions
      // in the list are thrown. In C++, it means that exeptions
      // that are not in the list, don't have to be caught.
      // A move is illegal if it would move the hole out of the board.

   bool issolved( ) const;
      // True if the puzzle is in the solved state.      

   friend std::ostream& operator << ( std::ostream& stream, const fifteen &f );

   friend struct fifteen_cmp;
};

struct fifteen_cmp
{
   bool operator( ) ( const fifteen& f1, const fifteen& f2 );
      // Compare the two states of the 15-puzzle.
      // Goal of this comparison operator is to be able to put 
      // them in an std::map< >. 
};

struct fifteen_better 
{
   bool operator( ) ( const fifteen& f1, const fifteen& f2 )
   {
      return f1. distance( ) > f2. distance( );
         // It is possible that you have to reverse this. 
   }
};

std::ostream& operator << ( std::ostream& stream, const fifteen &f );
fifteen solve( const fifteen &f );
#endif // __FIFTEEN_H__
