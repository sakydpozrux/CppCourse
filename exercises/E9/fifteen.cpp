
#include <iostream>
#include <queue>
#include <map>
#include <vector>

#include "assert.h" 

enum class move { up, left, right, down };

inline std::ostream& operator << ( std::ostream& stream,
                                   move m )
{
   switch(m)
   {
   case move::up : stream << "move-up"; return stream;
   case move::left : stream << "move-left"; return stream;
   case move::right: stream << "move-right"; return stream;
   case move::down: stream << "move-down"; return stream;
   }
}

struct illegalmove
{
   move m; 

   illegalmove( move m ) : m(m) { }
};

move operator - ( move m )
{
   switch(m)
   {
   case move::up:
      return move::down;
   case move::left:
      return move::right;
   case move::right:
      return move::left;
   case move::down:
      return move::up;
   }
}

inline std::ostream& operator << ( std::ostream& stream,
                                   illegalmove i )
{
   stream << "doing " << i.m << " is illegal!\n";
   return stream;
}


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
};

std::ostream& operator << ( std::ostream& stream, const fifteen& f );
   // You have to make it friend. 
   
   
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



fifteen solve( const fifteen& f )
{
   std::map< fifteen, bool, fifteen_cmp > reached;
   reached [f] = true;

   std::priority_queue< fifteen, std::vector< fifteen > , fifteen_better > 
      unchecked; 
   unchecked. push(f);

   std::vector< move > moves = 
      { move::up, move::down, move::left, move::right };
      // You don't have to use this, but if you do, it becomes easy to
      // check all moves by writing
      // for( std::vector< move > :: const_iterator 
      //      m = moves. begin( ); m != moves. end( ); ++ m ) 
      // {  .... }


   while( unchecked. size( ))
   {
      fifteen best = unchecked. top( );
         // Take the best state from the priority queue.

      // for each possible move,

             

   }
}

int main( int argc, char* argv [ ] )
{
   move m = move::up;
   std::cout << m << -m << - - m << "\n";
   std::cout << illegalmove(m) << "\n";

   return 0; 
}

