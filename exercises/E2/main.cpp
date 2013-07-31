
#include "rational.h"
#include "vector.h"

int main( int argc, char* argv [ ] )
{

   linalg::vector v1 ( rational(1,3),rational(2,7), rational(4,5) );
   linalg::vector v2 ( {2,7}, {4,8}, {1,8} );

   std::cout << v1 << "\n";
   std::cout << v2 << "\n";
   std::cout << linalg::crossproduct( v1, v2 ) << "\n";
   return 0; 
   
}

