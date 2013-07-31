
#include "tree.h"


int main( int argc, char* argv [ ] )
{
	//for (unsigned int i = 0; i < 1000000; i++)
	{
		tree t1( std::string( "-" ), { tree( std::string("x") ), tree(2) });
		tree t2( std::string( "/" ), { t1, tree(2) }); 
		tree t3( std::string( "*" ), { tree(3), tree( std::string("x") ) });
		tree tx( std::string( "+" ), { t3, t2 });

		std::cout << "t_1=\n" << tx << std::endl;
		std::cout << "\n\nt_1'=\n" << diff(tx,"x") << "\n";

		std::cout << "\n-----------\n\n";

		tree t01( std::string( "x" ));
	    tree t02( std::string( "sin" ), { tree(1) });
	    tree t03 = tree( std::string( "+" ), { t01, t02 } );
	    tree t04 = tree( std::string( "*" ), { t01, t03 } );

	    std::cout << "t_2=\n" << t04 << std::endl;
		std::cout << "\n\nt_2'=\n" << diff(t04,"x") << "\n";

		std::cout << "\n-----------\n-----------\n-----------\n\n";


		tree tr0( std::string("sin"), { tree(std::string( "*"), { tree( std::string( "x" )), tree( std::string( "x" )) } ) } );
	    std::cout << "tr0=\n" << tr0 << std::endl;
		std::cout << "\n\ntr0'=\n" << diff(tr0,"x") << "\n";
	}
   
}



