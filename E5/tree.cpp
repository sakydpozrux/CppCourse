
#include "tree.h"
#include <sstream>


tree::tree( const tree& t ) : pntr(t.pntr)
{
	(pntr->refcnt)++;
	//std::cout << "tree(" << pntr->f << "): " << pntr->refcnt << std::endl;
}


void tree::operator = ( const tree& t )
{
	((t.pntr)->refcnt)++;
	(pntr->refcnt)--;
	if ((pntr->refcnt) == 0) delete pntr;

	pntr = t.pntr;
}


tree::~tree()
{
	((*pntr).refcnt)--;
	//std::cout << "~tree(" << pntr->f << "): " << pntr->refcnt << std::endl;

	if (((*pntr).refcnt) == 0) delete pntr;

}


const std::string& tree::functor( ) const
{
	return pntr->f;
}

const tree& tree::operator [ ] ( unsigned int i ) const
{
	return pntr->subtrees[i];
}

const unsigned int tree::nrsubtrees() const
{
	return pntr->subtrees.size();
}

std::ostream& operator << ( std::ostream& stream, const tree& t )
{
	t.print(stream, 0);
	return stream;
}


void tree::print( std::ostream& stream, unsigned int indent) const
{
	for( unsigned int i = 0; i < indent; ++i )
		stream << "    ";

	stream << functor( ) << std::endl;
	for( unsigned int i = 0; i < nrsubtrees( ); ++i )
		(*this)[i].print( stream, indent + 1 );
}


std::string& tree::functor( )
{
	ensure_not_shared();
	return pntr->f;
}

tree& tree::operator [ ] ( unsigned int i )
{
	ensure_not_shared();
	return pntr->subtrees[i];
}

void tree::ensure_not_shared( )
{
	if ( pntr->refcnt > 1 )
	{
		(pntr->refcnt)--;
		pntr = new trnode( functor(), subtrees(), 1 );
	}
}

const std::vector< tree > tree::subtrees() const
{
	return pntr->subtrees;
}

tree subst( const tree& t, const std::string& var, const tree& val )
{
	tree tnew = t;

	for (unsigned int i; i < tnew.nrsubtrees(); ++i)
		if (tnew[i].functor() == var) tnew[i] = val;

	return tnew;
}


tree tree::subst(const std::string& var, const tree& val ) const
{
	tree tnew = *this;

	for (unsigned int i; i < tnew.nrsubtrees(); ++i)
		if (tnew[i].functor() == var) tnew[i] = val;

	return tnew;
}




bool tree::isunsigned( ) const
{
	// Numbers don’t have subtrees:
	if( pntr -> subtrees. size( ) != 0 )
		return false;
	const std::string& s = pntr -> f;
	for( auto p = s. begin( ); p != s. end( ); ++ p )
	{
		if( *p < '0' || *p > '9' ) return false;
	}
	return true;
}


unsigned int tree::getunsigned( ) const
{
	// We make a stringstream from the string, and
	// read the unsigned from it.
	std::istringstream s( pntr -> f );
	unsigned int res = 0;
	s >> res;
	return res;
}


tree::tree( unsigned int i )
: pntr(0)
{
	// This is a rare case where immediate initialization is not possible.
	std::ostringstream s;
	s << i;
	pntr = new trnode( s. str( ), { }, 1 );
}


tree diff( const tree& t, const std::string& var )
{
	if (t.isunsigned()) return tree(0);
	else if (t.functor() == var && t. nrsubtrees() == 0) return tree(1);
	else if (t.functor() == "*" && t. nrsubtrees() == 2)
	{
		return tree( std::string("+"), { tree( std::string("*"), { diff(t[0],var), t[1] } ), tree( std::string("*"), { t[0], diff(t[1], var) } ) } );
	}
	else if (t.functor() == "/" && t. nrsubtrees() == 2)
	{
		tree tright( std::string("*"), { t[0], t[0] });
		tree tleft( std::string("-"), { tree( std::string("*"), { diff(t[0],var), t[1] } ), tree( std::string("*"), { t[0], diff(t[1], var) } ) } );
		return tree( std::string("/"), { tleft, tright } );
	}
	else if (t.functor() == "+" && t. nrsubtrees() == 2)
	{
		return tree( std::string( "+" ), { diff( t[0], var ), diff( t[1], var ) } );
	}
	else if (t.functor() == "-" && t. nrsubtrees() == 2)
	{
		return tree( std::string( "-" ), { diff( t[0], var ), diff( t[1], var ) } );
	}
	else if (t.functor() == "-" && t. nrsubtrees() == 1)
	{
		return tree( std::string( "-" ), { diff( t[0], var ) } );
	}
	else if (t.functor() == "sin" && t. nrsubtrees() == 1)
	{
		return tree( std::string( "*"), { tree(std::string( "cos" ), { t[0] }) , diff( t[0], var ) } );
	}
	else if (t.functor() == "cos" && t. nrsubtrees() == 1)
	{
		return tree( std::string("-"), { std::string( "sin" ), diff( t[0], var ) } );
	}
	else if (t.functor() == "e^x" && t. nrsubtrees() == 1)
	{
		return tree( std::string( "e^x" ), { t[0], var } );
	}

}