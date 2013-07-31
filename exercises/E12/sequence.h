
#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED  1

// A sequence is a sequence of cube rotations:

#include "rotation.h"
#include <vector>
#include <initializer_list>


struct sequence
{

   std::vector< rotation > rot;


   sequence( std::initializer_list< rotation > init )
   {
      for( auto p = init. begin( );
                p != init. end( );
                ++ p )
      { 
         rot. push_back( *p );
      }
   }

   sequence( ) { } 
   sequence( const rotation& r ) { rot. push_back(r); } 

   sequence inverse( ) const; 

   unsigned int length( ) const { return rot. size( ); }

};

sequence repeat( const sequence& seq, unsigned int i );
   // Constructs sequence that repeats seq i times.

sequence operator * ( const sequence& seq1, const sequence& seq2 );
   // Construct sequence that first does seq1, after that seq2.

std::ostream& operator << ( std::ostream& stream, const sequence& seq );


#endif

