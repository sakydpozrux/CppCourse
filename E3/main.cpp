#include "stack.h"

int main( int argc, char* argv [ ] )
{
   stack s1;
   s1.push(1);
   s1.push(2);
   s1.push(3);
   std::cout << s1;
   
   s1.pop();
   s1.push(4);
   std::cout << s1;

   s1.push(5); s1.push(6); s1.push(7); s1.push(8); s1.push(9); s1.push(10);
   std::cout << s1;

   std::cout << s1[1] << std::endl;
   //const stack& s2 = s1; // This won't compile
   s1[1] = 99;
   std::cout << s1;


   return 0; 
}

