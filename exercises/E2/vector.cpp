
#include "vector.h"

rational linalg::dotproduct( const linalg::vector& v1, 
                             const linalg::vector& v2 )
{
   return v1.x * v2.x +
          v1.y * v2.y +
          v1.z * v2.z;
}


linalg::vector 
linalg::crossproduct( const linalg::vector& v1, 
                      const linalg::vector& v2 )
{
   return vector( v1. y * v2. z - v1. z * v2. y,
                  v1. z * v2. x - v1. x * v2. z,
                  v1. x * v2. y - v1. y * v2. x );
}


std::ostream& linalg::operator << ( std::ostream& stream, 
                                    const linalg::vector& v )
{
   stream << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
   return stream;
}


