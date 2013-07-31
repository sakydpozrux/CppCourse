
#include "tree.h"


tree::tree( const tree& t )
: pntr(t.pntr)
{
	(pntr->refcnt)++;
	/*std::cout << "tree(" << pntr->f << "): " << pntr->refcnt << std::endl;*/
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
	(pntr->refcnt)--;
	/*std::cout << "~tree(" << pntr->f << "): " << pntr->refcnt << std::endl;*/

	if (pntr->refcnt == 0) delete pntr;

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
	stream << t.functor();
	if (t. nrsubtrees())
	{
		stream << "(";
		for (unsigned int i = 0; i < t.nrsubtrees() ; ++i )
		{
			if( i ) std::cout << ", ";
			stream << t[i];
		}
	stream << ')';
	}

	return stream;
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
        pntr = new trnode(pntr->f, pntr->subtrees, 1);
	}
}

const std::vector< tree > & tree::subtrees() const
{
	return pntr->subtrees;
}


tree subst( const tree& t, const std::string& var, const tree& val )
{
	tree tnew = t;

	// with only t. nrsubtrees() == 0 statement it changes only leafs
	if( (t. functor() == var) && (t. nrsubtrees() == 0)) tnew = val;
	else
		for (unsigned int i = 0; i < tnew. nrsubtrees(); ++i)
	       tnew [i] = subst( tnew [i], var, val );

	return tnew;
}
