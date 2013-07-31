
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

   rational( int num, int denum )
      : num( num ), denum( denum )
   { }

   static int gcd( int num, int denum );
      // Use Euclidean Algorithm. 
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

