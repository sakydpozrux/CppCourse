
#ifndef RATIONAL_INCLUDED
#define RATIONAL_INCLUDED 1

#include <iostream>

struct rational
{
   int num;
   int denum;

   rational( ) 
      : num(0),
        denum(0)
   { }

   rational( int i )
      : num(i), 
        denum(1)
   { }

   static int gcd( int num, int denum )
      // Use Euclidean Algorithm. 
   { 
     if (num < 0) num *= -1;
     if (denum < 0) denum *= -1;

     if (num == 0) return denum;

     while (denum != 0)
     {
       if (num > denum) num = num -= denum;
       else denum -= num;
     }

     return num;
   }

   rational( int num2, int denum2 )
      : num( num2 ),
        denum( denum2 )
      // I'm sure rationals will be in the simpliest form
   { }

   static rational normalise(rational x)
   {
     if (x.num < 0 && x.denum < 0)
     {
      x.num *= -1;
      x.denum *= -1;
     }

     int d = gcd(x.num, x.denum);
     return rational(x.num / d, x.denum / d);
   }
};

// While I agree that normally these functions would be inline,
// it is not allowed in this task, because this task is about
// how one normally puts a C++ program in different files.

rational operator - ( const rational& r );

rational operator + ( const rational& r1, const rational& r2 );  
rational operator - ( const rational& r1, const rational& r2 ); 
rational operator * ( const rational& r1, const rational& r2 );
rational operator / ( const rational& r1, const rational& r2 );

bool operator == ( const rational& r1, const rational& r2 );
bool operator != ( const rational& r1, const rational& r2 );
bool operator < ( const rational& r1, const rational& r2 );
bool operator > ( const rational& r1, const rational& r2 );
bool operator <= ( const rational& r1, const rational& r2 );
bool operator >= ( const rational& r1, const rational& r2 );

std::ostream& operator << ( std::ostream& stream, const rational& r ); 

#endif

