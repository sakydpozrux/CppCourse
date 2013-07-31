
#ifndef CUBE_INCLUDED	
#define CUBE_INCLUDED   1

#include <vector>
#include <iostream>

#include "assert.h"

struct rotation;
struct sequence;

struct cube_cmp;

class cube
{
public: 
   enum class side { left, right, up, down, front, back };
   enum class color { white, red, orange, green, blue, yellow };

private: 
   unsigned int size; 
   std::vector< color > sides;
      // It has a size of 6 * size * size; 

      // We use the following convention: 
      // (I defined suitable index operators, so you don't need to 
      //  worry about this.)
      // 
      // sides [ 0 * d * d ] : left
      // sides [ 1 * d * d ] : front
      // sides [ 2 * d * d ] : right
      // sides [ 3 * d * d ] : back
      // sides [ 4 * d * d ] : up
      // sides [ 5 * d * d ] : down. 


      static unsigned int offset( side s )
      {
         switch(s)
         {
         case side::left: return 0;
         case side::front: return 1;
         case side::right: return 2;
         case side::back: return 3;
         case side::up: return 4;
         case side::down: return 5;
         }
         ASSERT( false ); return 0;
            // Without return, compiler complains. 
      }

      // Inverse of offset( ):

      static side getside( unsigned int i )
      {
         switch(i)
         {
         case 0: return side::left;
         case 1: return side::front;
         case 2: return side::right;
         case 3: return side::back;
         case 4: return side::up;
         case 5: return side::down;
         }
         ASSERT( false ); return side::left;
            // Without return, compiler complains. 
      }
           
      // We have to define a sequence of intermediate index
      // data structures. It is unpleasant.

      struct row_index
      {
         std::vector< color > :: iterator p;
         unsigned int size;

         color& operator [] ( unsigned int j ) const
         {
            ASSERT( j < size );
            return p[j];
         }

         row_index( std::vector< color > :: iterator p,
                    unsigned int size )
            : p(p), size(size)  
         { } 
      };

      struct row_const_index
      {
         std::vector< color > :: const_iterator p;
         unsigned int size;

         color operator [] ( unsigned int j ) const
         {
            ASSERT( j < size );
            return p[j];
         }

         row_const_index( std::vector< color > :: const_iterator p,
                          unsigned int size )
            : p(p), size(size)
         { } 
      };
         
      struct side_index
      {
         std::vector< color > :: iterator p;
         unsigned int size;
 
         row_index operator [] ( unsigned int i ) const
         {
            ASSERT( i < size ); 
            return row_index( p + size * i, size );
         } 

         side_index( std::vector< color > :: iterator p,
                     unsigned int size )
            : p(p), size(size)
         { }
      };

      struct side_const_index
      {  
         std::vector< color > :: const_iterator p;
         unsigned int size;

         row_const_index operator [] ( unsigned int i ) const
         {
            ASSERT( i < size );
            return row_const_index( p + size * i, size );
         }

         side_const_index( std::vector< color > :: const_iterator p,
                           unsigned int size )
            : p(p), size(size)
         { }
      }; 

public: 
      side_index operator [] ( side s ) 
      {
         return side_index( sides. begin( ) + offset(s) * size * size,
                            size );
      }

      side_const_index operator [] ( side s ) const
      {
         return side_const_index( sides. begin( ) + offset(s) * size * size,
                                  size );
      }

   static color solvedcolor( side s );
      // Returns the color that side s has, when the cube is solved.
      // The choice is arbitrary, but we have to choose something.
      // I chose the colors of my own cube.
      // 
      // left : yellow,
      // front  : white, 
      // right :  green,
      // back : blue,
      // up : red,
      // down : orange.

   static std::vector< side > allsides( );
      // This is useful when you want to enumerate all possible
      // moves. 

   explicit cube( unsigned int size ); 
   unsigned int getsize( ) const { return size; }

   static void rotate( int d, color& c1, color& c2, color& c3, color& c4 );
      // Rotate colors right over distance i.

   void rotate_surface_only( side s, int d ); 
      // Rotate a surface. (This function is incomplete, 
      // because it doesn't rotate neighbouring faces.)

   void rotate_neighbours( side s, int d, unsigned int j );
      // d is the amount of rotation, j in [1 .. size ] is the distance
      // from surface s. 

   void rotate( const rotation& rot ); 
   void rotate( const sequence& seq ); 

   unsigned int distance( ) const;

   friend std::ostream& operator << ( std::ostream& , const cube& ); 
   friend void plot( const cube& ); 
   friend struct cube_cmp;
};

std::ostream& operator << ( std::ostream& stream, cube::side s ); 
std::ostream& operator << ( std::ostream& stream, cube::color c );
std::ostream& operator << ( std::ostream& stream, const cube& c ); 

#endif

