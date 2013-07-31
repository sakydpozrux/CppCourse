#include <iostream>

#include "fifteen.h"

typedef unsigned int uint;

int main( int argc, char* argv [ ] )
{
  uint test[4][4] = {
    {  11,  8,  7,  2 },
    {  0,  10,  9,  1 },
    { 12, 3, 14, 5 },
    { 15,  6,  4, 13 }
  };
  fifteen p(test);

  std::cout << p << std::endl;

  std::cout << solve(p) << std::endl;
  return 0;
}

