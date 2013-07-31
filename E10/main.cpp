#include <iostream>
#include <string>

template< typename A, typename B >
class unionof;

template< typename A, typename B >
std::ostream& operator << ( std::ostream& stream, const unionof< A, B > & );


template< typename A, typename B >
class unionof
{
	A* a;
	B* b;

	// Invariant: Exactly one of them is non-zero.
public:
	friend std::ostream& operator << < > ( std::ostream& stream, const unionof< A, B > & );

	unionof( const A& _a )
		: a(new A(_a)), b(nullptr)
	{ }

	unionof( const B& _b )
		: b(new B(_b)), a(nullptr)
	{ }

	unionof( const unionof& u )
	   : a(u.a ? new A(u.first()) : nullptr), b(u.a ? nullptr : new B(u.second()))
	{ }


	void operator = ( const A& _a )
	{
		delete a;
		delete b;
		a = new A(_a);
		b = nullptr;
	}

	void operator = ( const B& _b )
	{
		delete a;
		delete b;
		a = nullptr;
		b = new B(_b);
	}

	void operator = ( const unionof& u )
	{
		if (this != &u)
		{
			delete a;
			delete b;

			a = nullptr;
			b = nullptr;

			if (u.hasfirst())
				a = new A(u.first());
			else
				b = new B(u.second());
		}
	}


	const A& first( ) const
	{
		return *a;
	}

	A& first( )
	{
		return *a;
	}


	const B& second( ) const
	{
		return *b;
	}

	B& second( )
	{
		return *b;
	}


	bool hasfirst( ) const
	{
		return a != nullptr;
	}

	bool hassecond( ) const
	{
		return b != nullptr;
	}


	~unionof( )
	{
		delete a;
		delete b;
	}
};

template< typename A, typename B >
std::ostream& operator << ( std::ostream& stream, const unionof< A, B > & u )
{
	if (u.hasfirst())
		stream << "A: " << u.first();
	else
		stream << "B: " << u.second();

	return stream;
}


int main()
{
	unionof<int, double> int_double(4);

	std::cout << "\nunionof<int, double> int_double(4):\n" << int_double << std::endl;


	int_double = 3.14;

	std::cout << "\nint_double = 3.14:\n" << int_double << std::endl;


    int_double = 44;

	std::cout << "\nint_double = 44:\n" << int_double << std::endl;


	unionof<int, double> int_double2(int_double);

	std::cout << "\nunionof<int, double> int_double2(int_double):\n" << int_double2 << std::endl;

    int_double2 =  2.1223;
    int_double = int_double2;
    std::cout << "\nint_double:\n" << int_double << std::endl;

	unionof<std::string, int> string_int( std::string("example text") );

	std::cout << "\nunionof<std::string, int> string_int( std::string(\"example text\") ):\n" << string_int << std::endl;


	string_int = 4;

	std::cout << "\nstring_int = 4:\n" << string_int << std::endl;
	


	return 0;
}
