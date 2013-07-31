
#include "rational.h"

std::ostream& operator << ( std::ostream& stream, const rational& r ) 
{
   stream << r. num << " / " << r. denum;
   return stream;
}

rational operator - ( const rational& r ) 
{
  return rational::normalise(rational(-r.num, r.denum));
}
  
rational operator + ( const rational& r1, const rational& r2 )
{
  return rational::normalise(rational(r1.num * r2.denum + r1.denum * r2.num, r1.denum * r2.denum));
}

rational operator - ( const rational& r1, const rational& r2 )  
{
  return rational::normalise(rational(r1 + (-r2)));
}

rational operator * ( const rational& r1, const rational& r2 ) 
{
  return rational::normalise(rational(r1.num * r2.num, r1.denum * r2.denum));
}

rational operator / ( const rational& r1, const rational& r2 ) 
{
  return rational::normalise(rational(r1.num * r2.denum , r1.denum * r2.num));

}

int compare(const rational& r1, const rational& r2)
    // 0 if equal, -1 if r1 < r2, 1 if r1 > r2
{
  if ((r1.num == r2.num) && (r1.denum == r2.denum)) return 0;
  if (r1.num * r2.denum < r2.num * r1.denum) return -1;
  else return 1;
}

bool operator == ( const rational& r1, const rational& r2 ) 
{
  if (compare(r1, r2) == 0) return 1;
  return 0;
}

bool operator != ( const rational& r1, const rational& r2 ) 
{
  if (compare(r1, r2) != 0) return 1;
  return 0;
}

bool operator < ( const rational& r1, const rational& r2 )
{
  if (compare(r1, r2) == -1) return 1;
  return 0;
}

bool operator > ( const rational& r1, const rational& r2 ) 
{
  if (compare(r1, r2) == 1) return 1;
  return 0;
}

bool operator <= ( const rational& r1, const rational& r2 ) 
{
  if (compare(r1, r2) <= 0) return 1;
  return 0;
}

bool operator >= ( const rational& r1, const rational& r2 ) 
{
  if (compare(r1, r2) >= 0) return 1;
  return 0;
}
