#include "Cursor.h"

struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};


struct Node
{
	struct TreeNode Node;
	Position		Next;
};

struct Node CursorSpace[ SpaceSize ];

void
FatalError( char message[] )
{
	printf( "FatalError: %s\n", message );
}

void
Error( char message[] )
{
	printf( "Error: %s\n", message );
}

void 
InitializeCursorSpace( void )
{
	int i;

	for ( i = 0; i < SpaceSize-1; i++ )
		CursorSpace[ i ].Next = i + 1;
	CursorSpace[ i ].Next = 0;

}

static Position
CursorAlloc( void )
{
	Position P;

	P = CursorSpace[ 0 ].Next;
	CursorSpace[ 0 ].Next = CursorSpace[ P ].Next;

	return P;
}

static void
CursorFree( Position P )
{
	CursorSpace[ P ].Next = CursorSpace[ 0 ].Next;
	CursorSpace[ 0 ].Next = P;
}

/*
SearchTree
MakeEmpty( SearchTree T )
{
	if ( T )
	{
		MakeEmpty( CursorSpace[ T ].Left );
		MakeEmpty( CursorSpace[ T ].Right );
		CursorFree( T );
	}
	
	return 0;
}

*/

Position
Find( ElementType X, SearchTree T )
{
	if ( !T )
		return 0;
	if ( X < CursorSpace[ T ].Node.Element )
		return Find( X, CursorSpace[ T ].Node.Left );
	else
	if ( X > CursorSpace[ T ].Node.Element )
		return Find( X, CursorSpace[ T ].Node.Right );
	else
		return T;
}


Position
FindMin( SearchTree T )
{
	if ( T == 0 )
		return 0;
	else
	if ( CursorSpace[ T ].Node.Left == 0 )
		return T;
	else
		return FindMin( CursorSpace[ T ].Node.Left );
}

SearchTree
Insert( ElementType X, SearchTree T )
{
	if ( !T )
	{
		/* Create and return a one-node tree */
		T = CursorAlloc( );
		if ( !T )
			FatalError( "Out of space!!!" );
		else
		{
			CursorSpace[ T ].Node.Element = X;
			CursorSpace[ T ].Node.Left = CursorSpace[ T ].Node.Right = 0;
		}
	}
	else
	if ( X < CursorSpace[ T ].Node.Element )
		CursorSpace[ T ].Node.Left = Insert( X, CursorSpace[ T ].Node.Left );
	else
	if ( X > CursorSpace[ T ].Node.Element )
		CursorSpace[ T ].Node.Right = Insert( X, CursorSpace[ T ].Node.Right );
	/* Else X is in the tree already; we'll do nothing */

	return T; /* Do not forget this line!! */
}


SearchTree
Delete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if ( T == 0 )
		Error( "Element not found" );
	else
	if ( X < CursorSpace[ T ].Node.Element ) // Go left 
		CursorSpace[ T ].Node.Left = Delete( X, CursorSpace[ T ].Node.Left );
	else
	if ( X > CursorSpace[ T ].Node.Element ) // Go right 
		CursorSpace[ T ].Node.Right = Delete( X, CursorSpace[ T ].Node.Right );
	else
	if ( CursorSpace[ T ].Node.Left && CursorSpace[ T ].Node.Right ) // Two children 
	{
		// Replace with smallest in right sbtree 
		TmpCell = FindMin( CursorSpace[ T ].Node.Right );
		CursorSpace[ T ].Node.Element = CursorSpace[ TmpCell ].Node.Element;
		CursorSpace[ T ].Node.Right = 
			Delete( CursorSpace[ T ].Node.Element, CursorSpace[ T ].Node.Right );
	}
	else // One or zero children 
	{
		TmpCell = T;
		if ( CursorSpace[ T ].Node.Left == 0 ) // Also handles 0 children 
			T = CursorSpace[ T ].Node.Right;
		else if ( CursorSpace[ T ].Node.Right == 0 )
			T = CursorSpace[ T ].Node.Left;
		CursorFree( TmpCell );
	}
	
	return T;
}


ElementType
Retrieve( Position P )
{
	return CursorSpace[ P ].Node.Element;
}


void 
PrePrintTreeRec( SearchTree T, int N )
{
	if ( T != 0 )
	{
		int i;

		for ( i = 0; i < N; i++ )
			printf( "-" );

		printf( "%d\n", CursorSpace[ T ].Node.Element );
		PrePrintTreeRec( CursorSpace[ T ].Node.Left, N+1 );
		PrePrintTreeRec( CursorSpace[ T ].Node.Right, N+1 );
	}
}


void
PrePrintTree( SearchTree T )
{
	PrePrintTreeRec( T, 0 );
}

