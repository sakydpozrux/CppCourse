#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <chrono> // C++11
#include <assert.h>


// ############################################################################
// VECTOR functions
// ############################################################################

/*The function should read the complete text file name, and return its
contents as a vector of strings. The strings are the words occurring in
name.*/
std::vector< std::string> VectReadfile( const std::string& name )
{
	std::ifstream input( name. c_str( ));
	std::vector< std::string > vec;
	std::string word;
	
	while( input. good( ) && !input. eof( ))
	{
		int c = input. get( );

		if(isspace(c))
		{
			if(!word.empty())
			{
				vec.push_back( std::move(word) );
			}
		}
		else word.push_back(c);
	}

	// case when after last word is EOF instead of space
	if(!word.empty())
	{
		vec.push_back( std::move(word) );
	}

	// remove strange symbol at the end
	assert( vec. back( ). back( ) == EOF );
	vec.back().pop_back();
	
	return vec;
}


// 2-nd argument is vector of strings from above function
std::ostream& operator << ( std::ostream& stream,
							const std::vector< std::string > & vect )
{
	for( std::vector< std::string > :: const_iterator p = vect. begin( ); p != vect. end( ); ++ p )
	{
		stream << *p << "\n";
	}
	return stream;
}


void VectSortCopy( std::vector< std::string > & v )
{
	for( unsigned int j = 0; j < v. size( ); ++ j )
		for( unsigned int i = 0; i < j; ++ i )
		{
			if( v[i] > v[j] )
			{
				// string is copied
				std::string s = v[i];
				v[i] = v[j];
				v[j] = s;
			}
		}
}

void VectSortMove( std::vector< std::string > & v )
{
	for( unsigned int j = 0; j < v. size( ); ++ j )
		for( unsigned int i = 0; i < j; ++ i )
		{
			if( v[i] > v[j] )
			{
				// string is moved (not copied) = should be faster
				// but argument of move is empty after it's call
				std::string s = std::move( v[i] );
				v[i] = std::move( v[j] );
				v[j] = std::move( s );
			}
		}
}

void VectSortCopyIter( std::vector< std::string > & v )
{
	for( auto p = v.begin(); p != v.end(); ++p )
		for( auto q = v.begin(); p != q; ++q ) // p<q is wrong here
		{
			if( *q > *p )
			{
				// string is copied
				std::string s = *q;
				*q = *p;
				*p = s;
			}
		}
}

void VectSortMoveIter( std::vector< std::string > & v )
{
	for( auto p = v.begin(); p != v.end(); ++p)
		for( auto q = v.begin(); p != q; ++q )
		{
			if( *q > *p )
			{
				// string is moved (not copied)
				// but argument of move is cleared
				std::string s = std::move( *q);
				*q = std::move( *p );
				*p = std::move( s );
			}
		}
}

void VectSortSwapIter( std::vector< std::string > & v )
{
	for( auto p = v.begin(); p != v.end(); ++p)
		for( auto q = v.begin(); p != q; ++q )
			if( *q > *p )
				p->swap(*q);
}



// ############################################################################
// LIST functions
// ############################################################################

std::list< std::string> ListReadfile( const std::string& name )
{
	std::ifstream input( name. c_str( ));
	std::list< std::string > list;
	std::string word;
	
	while( input. good( ) && !input. eof( ))
	{
		int c = input. get( );

		if(isspace(c))
		{
			if(!word.empty())
			{
				list.push_back( std::move(word) );
			}
		}
		else word.push_back(c);
	}

	// case when after last word is EOF instead of space
	if(!word.empty())
	{
		list.push_back( std::move(word) );
	}

	// remove strange symbol at the end
	list.back().back() = ' ';

	return list;
}


std::ostream& operator << ( std::ostream& stream, const std::list< std::string > & list )
{
	for( std::list< std::string > :: const_iterator p = list. begin( ); p != list. end( ); ++ p )
	{
		stream << *p << "\n";
	}
	return stream;
}


void ListSortCopyIter( std::list< std::string > & list )
{
	for( auto p = list.begin(); p != list.end(); ++p)
		for( auto q = list.begin(); p != q; ++q ) // p<q is wrong here
		{
			if( *q > *p )
			{
				// string is copied
				std::string s = *q;
				*q = *p;
				*p = s;
			}
		}
}

void ListSortMoveIter( std::list< std::string > & list )
{
	for( auto p = list.begin(); p != list.end(); ++p)
		for( auto q = list.begin(); p != q; ++q )
		{
			if( *q > *p )
			{
				// string is moved (not copied)
				// but argument of move is cleared
				std::string s = std::move( *q);
				*q = std::move( *p );
				*p = std::move( s );
			}
		}
}

void ListSortSwapIter( std::list< std::string > & list )
{
	for( auto p = list.begin(); p != list.end(); ++p)
		for( auto q = list.begin(); p != q; ++q )
			if( *q > *p )
				p->swap(*q);
}


void RemoveShortStrings( std::list< std::string > & list, unsigned int len )
{
	list.remove_if( [&len](const std::string& s)->bool { return s.size() < len;});
}




// ############################################################################
// MAIN
// ############################################################################

int main( int argc, char* argv [ ] )
{
	typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    Clock::time_point begin, end;
    milliseconds ms;

    std::vector< std::string > vec;
    std::list< std::string > list;

	// 1
	std::cout << "##### VECTOR ##########################################\n";

	std::cout << VectReadfile("short.txt");

	std::cout << "## time tests #####\n";

	// 2
    	// copying
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		vec = VectReadfile("minishroom.txt");
		VectSortCopy(vec);
	}
	end = Clock::now();

	ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "VectSortCopy: " << ms.count() << "ms\n";

    	// moving
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		vec = VectReadfile("minishroom.txt");
		VectSortMove(vec);
	}
	end = Clock::now();
    
    ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "VectSortMove: " << ms.count() << "ms\n";


    // 3
    	// copying
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		vec = VectReadfile("minishroom.txt");
		VectSortCopyIter(vec);
	}
	end = Clock::now();

	ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "VectSortCopyIter: " << ms.count() << "ms\n";

    	// moving
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		vec = VectReadfile("minishroom.txt");
		VectSortMoveIter(vec);
	}
	end = Clock::now();
    
    ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "VectSortMoveIter: " << ms.count() << "ms\n";

    	// swapping
    begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		vec = VectReadfile("minishroom.txt");
		VectSortSwapIter(vec);
	}
	end = Clock::now();
    
    ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "VectSortSwapIter: " << ms.count() << "ms\n";


    // 4
    std::cout << "##### LIST ############################################\n";

    std::cout << ListReadfile("short.txt");

    std::cout << "## time tests #####\n";


       	// copying
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		list = ListReadfile("minishroom.txt");
		ListSortCopyIter(list);
	}
	end = Clock::now();

	ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "ListSortCopyIter: " << ms.count() << "ms\n";

    	// moving
	begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		list = ListReadfile("minishroom.txt");
		ListSortMoveIter(list);
	}
	end = Clock::now();
    
    ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "ListSortMoveIter: " << ms.count() << "ms\n";

    	// swapping
    begin = Clock::now();
	for (unsigned int i = 0; i < 100; ++i)
	{
		list = ListReadfile("minishroom.txt");
		ListSortSwapIter(list);
	}
	end = Clock::now();

	ms = std::chrono::duration_cast<milliseconds>(end - begin);
    std::cout << "ListSortSwapIter: " << ms.count() << "ms\n";


    //5
    std::cout << "##### ERASE LIST TEST #################################\n";

    std::list< std::string > erasetestlist = ListReadfile("short.txt");
    RemoveShortStrings(erasetestlist, 6);
    std::cout << erasetestlist << "\n";




	return 0;
}



