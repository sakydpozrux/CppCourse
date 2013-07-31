
// A vector is always 3-dimensional.

#ifndef LINALG_VECTOR_INCLUDED
#define LINALG_VECTOR_INCLUDED   1

#include <iostream>
#include "rational.h"


namespace linalg
{

   struct vector
   {
      rational x;
      rational y;
      rational z;


      vector( rational x, rational y, rational z )
         : x(x), y(y), z(z)
      { }       

      rational norm( ) const
      {
         return x * x + y * y + z * z;
      }

   };


   inline vector operator - ( const vector& v )
   {
      return vector( -v.x, -v.y, -v.z );
   }


   inline vector operator + ( const vector& v1, const vector& v2 )
   {
      return vector( v1. x + v2. x, 
                     v1. y + v2. y,
                     v1. z + v2. z );
   }


   inline vector operator - ( const vector& v1, const vector& v2 )
   {
      return vector( v1. x - v2. x,
                     v1. y - v2. y, 
                     v1. z - v2. z );
   }


   inline vector operator * ( rational d, const vector& v )
   {
      return vector( d * v.x, d * v.y, d * v.z );
   }


   inline vector operator * ( const vector& v, rational d )
   {
      return vector( v.x * d, v.y * d, v.z * d );
   }


   inline vector operator / ( const vector& v, rational d )
   {
      return vector( v.x/d, v.y/d, v.z/d );
   }

   rational dotproduct( const vector& v1, const vector& v2 );
   vector crossproduct( const vector& v1, const vector& v2 );

   std::ostream& operator << ( std::ostream& stream, const vector& v ); 
}


#endif


