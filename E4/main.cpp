
#include "tree.h"


int main( int argc, char* argv [ ] )
{
	for (unsigned int i = 0; i < 1; i++)
	{
		tree t1( std::string( "a" ), { tree( std::string( "x" )  )});
		std::cout << t1 << std::endl;

		tree t2( std::string( "b" )); 
		std::cout << t2 << std::endl;

		tree t3 = tree( std::string( "x" ), { t1, t2 } );
		std::cout << t3 << std::endl;

		std::cout << "\n-----------\n\n";

		tree t4( std::string( "hai" ));
		tree t5 = t4;
		
		std::cout << "Before change functor() - t4: " << t4 << ", t5: " << t5 << '\n';
		
		t5. functor( ) = "hallo";

		std::cout << "After change functor() - t4: " << t4 << ", t5: " << t5 << '\n';

		std::cout << "\n-----------\n\n";

		tree t6 = tree( std::string( "y" ), { t2, t4 } );

		std::cout << "Finally - t6: " << t6 << '\n';

		std::cout << "\n-----------";
		std::cout << "\n-----------\n";

		tree y1( std::string( "a" ), { tree( std::string( "x" )  )});
		tree y2( std::string( "x" ), { tree( std::string( "x" )), tree( std::string( "c" ))}); 
		tree y3 = tree( std::string( "x" ), { y1, y2 } );

		tree y4( std::string( "y" ));

		std::cout << "before : " << y3 << std::endl;

		tree y5 = subst(y3, "x", y4);

		std::cout << "after  : " << y5 << std::endl;


	}
   
}



