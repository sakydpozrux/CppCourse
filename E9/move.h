#ifndef __MOVE_H__
#define __MOVE_H__
#include <iostream>

enum move { move_up, move_left, move_right, move_down };

struct illegalmove
{
   move m; 

   illegalmove( move m ) : m(m) { }
};

std::ostream& operator << ( std::ostream& stream,
                                   move m );

std::ostream& operator << ( std::ostream& stream,
                                   illegalmove i );
#endif // __MOVE_H__
