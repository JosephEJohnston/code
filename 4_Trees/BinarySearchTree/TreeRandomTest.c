#include "TreeRandomTest.h"

struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};
	

SearchTree
RandomInserts( int n, int X, int Y, int a[] ,SearchTree T )
{
	int i;

	
	MakeRandomSequence( n, X, Y, a );

	for ( i = 0; i < n; i++ )
		T = Insert( a[ i ], T );

	return T;
}

SearchTree
RandomDeletes( int n, int X, int Y, int a[], SearchTree T, 
		SearchTree ( * Delete )( ElementType, SearchTree ) )
{
	int i;

	MakeRandomSequence( n, X, Y, a );

	for ( i = 0; i < n; i++ )
		T = Delete( a[ i ], T );

	return T;
}
