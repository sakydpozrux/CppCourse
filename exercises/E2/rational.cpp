
#include "rational.h"

std::ostream& operator << ( std::ostream& stream, const rational& r ) 
{
   stream << r. num << " / " << r. denum;
   return stream;
}

