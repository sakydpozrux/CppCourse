
#include "cube.h"
#include "rotation.h"
#include "sequence.h" 

cube::color cube::solvedcolor( side s )
{
   switch(s)
   {
   case side::left:  return color::yellow;
   case side::front: return color::white;
   case side::right: return color::green;
   case side::back:  return color::blue;
   case side::up:    return color::red;
   case side::down:  return color::orange;
   }

   return color::yellow;   // Unreachable, but otherwise the compiler whines. 
}


std::ostream& operator << ( std::ostream& stream, cube::side s )
{
   switch(s)
   {
   case cube::side::left:    stream << 'L'; return stream;
   case cube::side::right:   stream << 'R'; return stream;
   case cube::side::up:      stream << 'U'; return stream;
   case cube::side::down:    stream << 'D'; return stream;
   case cube::side::front:   stream << 'F'; return stream;
   case cube::side::back:    stream << 'B'; return stream;
   }

   QUIT( );
}


std::ostream& operator << ( std::ostream& stream, cube::color c )
{
   switch(c)
   {
   case cube::color::white:   stream << "white "; return stream;
   case cube::color::red:     stream << "red   "; return stream;
   case cube::color::orange:  stream << "orange" ; return stream;
   case cube::color::green:   stream << "green "; return stream;
   case cube::color::blue:    stream << "blue  ";  return stream;  
   case cube::color::yellow:  stream << "yellow"; return stream;
   }

   QUIT( );
}


std::vector< cube::side > cube::allsides( ) 
{
   return 
      { side::left, side::right, side::up, side::down,  
        side::front, side::back };
}


cube::cube( unsigned int size )
   : size( size )
{
   ASSERT( size > 1 );

   for( unsigned int i = 0; i < 6; ++ i )
   {
      color col = solvedcolor( getside(i) ); 

      for( unsigned int j = 0; j < size * size; ++ j )
         sides. push_back( col );
   }
}

 
std::ostream& operator << ( std::ostream& stream,
                            const cube& c )
{
   for( unsigned int i = 0; i < 6; ++ i )
   {
      stream << cube::getside(i) << ": "; 
      for( unsigned int j = 0; j < c. size * c. size; ++ j ) 
      {
         stream << c. sides [ i * c. size * c. size + j ] << " "; 
         if( ( j + 1 ) % c. size == 0 )
            stream << " | "; 
      }
      stream << "\n";
   }
   return stream;
}


   // If you have openGL, you can use this:

#if 0 
#include <SFML/Window.hpp>

void plot( const cube& c )
{
   glClearColor( 0, 0, 0, 1 );
   glClearDepth(1);
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glEnable( GL_DEPTH_TEST );
   glDepthFunc( GL_LEQUAL );

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity( );

   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity( ); 
   glOrtho( 0, 5 * c. size, 0, 4 * c. size, -1, 1 ); 

   for( unsigned int s = 0; s < 6; ++ s )
   {
      // We determine where to start plotting:

      double x, y;   // Will be the position of upper left corner of
                     // the i-th surface. 

      switch(s)
      {
      case 0: 
         x = 0; y = 2; break;
      case 1:
         x = 1; y = 2; break;
      case 2:
         x = 2; y = 2; break;
      case 3:
         x = 3; y = 2; break;
      case 4:
         x = 1; y = 3; break;
      case 5:
         x = 1; y = 1; break;
      }

      x = ( x + 0.5 ) * c. size;
      y = ( y + 0.5 ) * c. size;

      for( unsigned int i = 0; i < c. size; ++ i )
         for( unsigned int j = 0; j < c. size; ++ j )
         {
            // We set the color:

            switch( c[ cube::getside(s) ][i][j] )
            {
            case cube::white:
               glColor3f( 1, 1, 1 ); break;
            case cube::red:
               glColor3f( 1, 0, 0 ); break;
            case cube::orange:
               glColor3f( 1, 0.6, 0 ); break;
            case cube::green:
               glColor3f( 0, 1, 0 ); break;  
            case cube::blue:
               glColor3f( 0, 0, 1 ); break; 
            case cube::yellow:
               glColor3f( 1, 1, 0 ); break; 
            }

            // and we plot:

            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            glBegin( GL_POLYGON );
 
            glVertex2f( x + j,       y - i );  
            glVertex2f( x + j,       y - i - 0.8 );
            glVertex2f( x + j + 0.8, y - i - 0.8 );
            glVertex2f( x + j + 0.8, y - i );
            
            glEnd( );
         }
   }

   glFlush( ); 
}

#endif

