#include "move.h"
#include <iostream>

std::ostream& operator << ( std::ostream& stream,
                                   move m )
{
   switch(m)
   {
   case move_up : stream << "move-up"; return stream;
   case move_left : stream << "move-left"; return stream;
   case move_right: stream << "move-right"; return stream;
   case move_down: stream << "move-down"; return stream;
   }
}


std::ostream& operator << ( std::ostream& stream,
                                   illegalmove i )
{
   stream << "doing " << i.m << " is illegal!\n";
   return stream;
}
