
#include "tree.h"


int main( int argc, char* argv [ ] )
{
   tree t1( std::string( "a" ));
   tree t2( std::string( "b" )); 
   tree t3 = tree( std::string( "f" ), { t1, t2 } ); 
   
}



