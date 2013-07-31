
#ifndef TREE_INCLUDED
#define TREE_INCLUDED  1


#include <iostream>
#include <vector>
#include <string>


class tree;

// struct trnode should be invisible to the user of tree. This can be 
// obtained by making it a private number of tree. 
// In this exercise, we leave it like this, because it is simpler.
// In real code, trnode should be defined inside tree.


struct trnode 
{
   std::string f;
   std::vector< tree > subtrees;
   
   unsigned int refcnt;
      // The reference counter: Counts how often this trnode is referred to.

   trnode( const std::string& f, const std::vector< tree > & subtrees, 
           unsigned int refcnt )
      : f(f),
        subtrees( subtrees ),
        refcnt( refcnt )
   { }

   trnode( const std::string& f, const std::vector< tree > && subtrees,
           unsigned int refcnt )
      : f(f),
        subtrees( std::move( subtrees )), 
        refcnt( refcnt )
   { }
      // The double && is an R-value reference. This is a reference
      // to an object, that nobody cares about anymore, and that
      // is about to be destroyed. In this way, it can be avoided that 
      // elements in the vector are copied, when it is possible to simply
      // pass the link. See: 
      // http://thbecker.net/articles/rvalue_references/section_01.html
};


class tree
{
   trnode* pntr;

public: 
   tree( const std::string& f ) 
      : pntr( new trnode( f, { }, 1 ))
   { /*std::cout << "tree(" << pntr->f << "): " << pntr->refcnt << std::endl;*/ }

   tree( const std::string& f, const std::vector< tree > & subtrees )   
      : pntr( new trnode( f, subtrees, 1 ))
   { /*std::cout << "tree(" << pntr->f << "): " << pntr->refcnt << std::endl;*/ } 
 
   tree( const std::string& f, std::vector< tree > && subtrees )
      : pntr( new trnode( f, std::move( subtrees ), 1 ))
   { /*std::cout << "tree(" << pntr->f << "): " << pntr->refcnt << std::endl;*/ }

  
   tree( const tree& t );
   void operator = ( const tree& t );
 
   const std::string& functor( ) const;
   std::string& functor( );

   const unsigned int nrsubtrees() const;
   const std::vector< tree > & subtrees() const;

   const tree& operator [ ] ( unsigned int i ) const;
   tree& operator [ ] ( unsigned int i );

   ~tree( );

   tree subst(const std::string& var, const tree& val ) const;

private:
   // Delete public, when the thing is tested:

   void ensure_not_shared( ); 

};

tree subst( const tree& t, const std::string& var, const tree& val );

std::ostream& operator << ( std::ostream& stream, const tree& t );
   // Doesn't need to be friend, because it uses only functor( ) and
   // [ ].

#endif

