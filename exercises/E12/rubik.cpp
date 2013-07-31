
#include "sequence.h"
#include "cube.h"
#include "solve.h" 
#include <stdio.h>
#include <initializer_list>


// If you want to use graphics, switch this on.
// It works in Room 7. 

// #include <SFML/Window.hpp>

int main( int argc, char* argv [ ] )
{
   cube c = example3( );
   // Use of graphics. Switch it on, if you want to use
   // graphics.

#if 0 
   sf::Window
          wind( sf::VideoMode( 1024, 500, 32 ), "Rubik Cube" );

   char q = ' ';
   while( q != 'q' )
   {
      plot(c); 
      wind. Display( ); 

      q = getchar( ); 
   } 
#endif
   return 0; 
}

