#include "rational.h"
#include "vector.h"

int main( int argc, char* argv [ ] )
{
   std::cout << "(45/3) + (8/26): " << rational(45,3) + rational(8,26) << "\n";
   std::cout << "\n";

   linalg::vector v1 ( rational(1,2), rational(3,4), rational(1,7) );
   linalg::vector v2 ( rational(1,7), rational(1,8), rational(-1,4) );

   std::cout << "v1: " << v1 << "\n";
   std::cout << "v2: " << v2 << "\n";
   std::cout << "crossproduct(v1,v2): " << linalg::crossproduct( v1, v2 ) << "\n";
   std::cout << "\n";

   linalg::vector v3 ( rational(2,3), rational(3,1), rational(4,1) );
   linalg::vector v4 ( rational(4,3), rational(3,4), rational(6,1) );

   std::cout << "v3: " << v3 << "\n";
   std::cout << "v4: " << v4 << "\n";
   std::cout << "crossproduct(v3,v4): " << linalg::crossproduct( v3, v4 ) << "\n";
   std::cout << "\n";

   std::cout << "gcd(-8,12): " << rational::gcd(-8,12) << "\n";
   std::cout << "normalise(-8,-12): " << rational::normalise( rational(-8,-12) ) << "\n";
   std::cout << "\n";

   std::cout << "distributive test: \n";
   std::cout << "v1 cross (v2 + v3):\t\t" << linalg::crossproduct(v1, v2 + v3)  << "\n";
   std::cout << "v1 cross v2 + v1 cross v3:\t" << linalg::crossproduct(v1, v2) + linalg::crossproduct(v1,v3) << "\n";
   std::cout << "v1 dot (v2 + v3):\t\t" << linalg::dotproduct(v1, v2 + v3) << "\n";
   std::cout << "v1 dot v2 + v1 dot v3:\t\t" << linalg::dotproduct(v1, v2) + linalg::dotproduct(v1,v3) << "\n";
   std::cout << "\n";

   std::cout << "compare rationals test: \n";
   std::cout << "1/3 < 1/2: " << ((rational(1,3) < rational(1,2))?"TRUE":"FALSE") << "\n";
   std::cout << "2/4 < 1/2: " << ((rational(2,4) < rational(1,2))?"TRUE":"FALSE") << "\n";
   std::cout << "1/3 <= 1/3: " << ((rational(1,3) <= rational(1,3))?"TRUE":"FALSE") << "\n";
   std::cout << "1/3 < 1/3: " << ((rational(1,3) < rational(1,3))?"TRUE":"FALSE") << "\n";
   std::cout << "1/3 == 1/3: " << ((rational(1,3) == rational(1,3))?"TRUE":"FALSE") << "\n";
   std::cout << "6/7 >= 7/8: " << ((rational(6,7) >= rational(7,8))?"TRUE":"FALSE") << "\n";
   std::cout << "6/7 <= 7/8: " << ((rational(6,7) <= rational(7,8))?"TRUE":"FALSE") << "\n";


   return 0; 
}

