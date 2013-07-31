
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>

#include "fifteen.h"
#include "move.h"

typedef unsigned int uint;

fifteen solve( const fifteen& f )
{
   std::map< fifteen, bool, fifteen_cmp > reached;
   reached [f] = true;

   std::priority_queue< fifteen, std::vector< fifteen > , fifteen_better > 
      unchecked; 
   unchecked. push(f);

   std::vector< move > moves;
   moves. push_back( move_up );
   moves. push_back( move_down );
   moves. push_back( move_left );
   moves. push_back( move_right );


   while( unchecked. size( ))
   {
      fifteen best = unchecked. top();
      unchecked.pop();

      //std::cout << best << std::endl;
      if( best.issolved() )
        return best;

      for( std::vector<move>::const_iterator m = moves.begin(); m != moves.end(); ++m )
      {
        fifteen newElem = best; // default copy constructor
        try
        {
          newElem.makemove(*m);
        }
         
        catch( illegalmove i )
        {
          continue;
        }

        if( !reached[newElem] )
        {
          reached[newElem] = true;
          unchecked.push(newElem);
        }
      }
   }
}

fifteen::fifteen() : x(3), y(3) {
  table[0][0] = 1;
  table[0][1] = 2;
  table[0][2] = 3;
  table[0][3] = 4;

  table[1][0] = 5;
  table[1][1] = 6;
  table[1][2] = 7;
  table[1][3] = 8;

  table[2][0] = 9;
  table[2][1] = 10;
  table[2][2] = 11;
  table[2][3] = 12;

  table[3][0] = 13;
  table[3][1] = 14;
  table[3][2] = 15;
  table[3][3] = 0;

  std::cout << distance() << std::endl;
}

unsigned int fifteen::distance( ) const
{
   unsigned int sum = 0;

   for (unsigned int i = 1; i < 16; ++i)
   {
      std::pair<unsigned int, unsigned int> actPos;

      // Position of i as std::pair
      for (unsigned int x = 0; x < 4; ++x)
         for (unsigned int y = 0; y < 4; ++y)
            if (table[x][y] == i)
               actPos = std::pair<unsigned int, unsigned int>(x, y);

      unsigned int il = i - 1;
      std::pair<unsigned int, unsigned int> mustPos =
         std::pair<unsigned int, unsigned int>(il / 4, il % 4);

      unsigned int dist = 0;
      dist += actPos.first > mustPos.first ?
              actPos.first - mustPos.first :
              mustPos.first - actPos.first;
      dist += actPos.second > mustPos.second ?
              actPos.second - mustPos.second :
              mustPos.second - actPos.second;

      sum += dist * dist; 
   }

   return sum;
}


fifteen::fifteen( uint _table[4][4] ) {
  for( uint i = 0; i < 4; ++i ) {
    for( uint j = 0; j < 4; ++j ) {
      if( _table[i][j] == 0 ) {
        x = i; y = j;
      }
      table[i][j] = _table[i][j];
    }
  }
}


void fifteen::makemove( move p ) throw( illegalmove ) {
  switch( p ) {
    case move_up:
      if( y == 0 )
        throw illegalmove(p);
      else {
        std::swap( table[x][y], table[x][y-1] ); 
        y -= 1;
        history.push_back(p);
      }
      break;
    case move_left:
      if( x == 0 )
        throw illegalmove(p);
      else {
        std::swap( table[x][y], table[x-1][y] );
        x -= 1;
        history.push_back(p);
      }
      break;
    case move_right:
      if( x == 3 )
        throw illegalmove(p);
      else {
        std::swap( table[x][y], table[x+1][y] );
        x += 1;
        history.push_back(p);
      }
      break;
    case move_down:
      if( y == 3 )
        throw illegalmove(p);
      else {
        std::swap( table[x][y], table[x][y+1] );
        y += 1;
        history.push_back(p);
      }
      break;
  }
}

bool fifteen::issolved() const {
  return distance() == 0;
}

bool fifteen_cmp::operator() ( const fifteen &f1, const fifteen &f2 )
{
  for( uint x = 0; x < 4; ++x ) {
    for( uint y = 0; y < 4; ++y ) {
      if( f1.table[x][y] < f2.table[x][y] )
        return false;
      if( f1. table[x][y] > f2. table [x] [y] )
        return true;
    }
  }
  return false; 
}

std::ostream& operator << ( std::ostream& stream, const fifteen& f ) {
  stream.width(4);
  stream.fill(' ');
  stream << "Fifteen puzzle positions: " << std::endl;
  for( uint i = 0; i < 4; ++i ) {
    for( uint j = 0; j < 4; ++j ) {
      stream << f.table[i][j] << "   ";
    }
    stream << std::endl;
  }
  stream << "Moves made: " << f.history.size() << std::endl;
  for( std::vector<move>::const_iterator x = f.history.begin(); x != f.history.end(); ++x ) {
    stream << *x << " ";
  }
  stream << std::endl;
  return stream;
}
