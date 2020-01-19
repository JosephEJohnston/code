#include "Tree.h"

struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

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

SearchTree
MakeEmpty( SearchTree T )
{
	if ( T != NULL )
	{
		MakeEmpty( T->Left );
		MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}

Position
Find( ElementType X, SearchTree T )
{
	if ( T == NULL )
		return NULL;
	if ( X < T->Element )
		return Find( X, T->Left );
	else
	if ( X > T->Element )
		return Find( X, T->Right );
	else
		return T;
}

Position
FindMin( SearchTree T )
{
	if ( T == NULL )
		return NULL;
	else
	if ( T->Left == NULL )
		return T;
	else
		return FindMin( T->Left );
}

Position
FindMax( SearchTree T )
{
	if ( T != NULL )
		while ( T->Right != NULL )
			T = T->Right;
	
	return T;
}

SearchTree
Insert( ElementType X, SearchTree T )
{
	if ( T == NULL )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct TreeNode ) );
		if ( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else
	if ( X < T->Element )
		T->Left = Insert( X, T->Left );
	else
	if ( X > T->Element )
		T->Right = Insert( X, T->Right );
	/* Else X is in the tree already; we'll do nothing */

	return T; /* Do not forget this line!! */
}
			
SearchTree
Delete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if ( T == NULL )
		Error( "Element not found" );
	else
	if ( X < T->Element ) /* Go left */
		T->Left = Delete( X, T->Left );
	else
	if ( X > T->Element ) /* Go right */
		T->Right = Delete( X, T->Right );
	else
	if ( T->Left && T->Right ) /* Two children */
	{
		/* Replace with smallest in right sbtree */
		TmpCell = FindMin( T->Right );
		T->Element = TmpCell->Element;
		T->Right = Delete( T->Element, T->Right );
	}
	else /* One or zero children */
	{
		TmpCell = T;
		if ( T->Left == NULL ) /* Also handles 0 children */
			T = T->Right;
		else if ( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}
	
	return T;
}

ElementType
Retrieve( Position P )
{
	return P->Element;
}

static int vecLeft[ 100 ];

/* Copy from other */
void
PrePrintTreeRec( SearchTree T,  int ident )
{
	int i;

	if ( ident > 0 )
	{
		for ( i = 0; i < ident-1; i++ )
			printf( vecLeft[ i ] ? "│  " : "   " );
		printf( vecLeft[ ident-1 ] ? "├──" : "└──" );
	}

	if ( T == NULL )
	{
		printf( "(null)\n" );
		return;
	}

	printf( "%d\n", T->Element );

	if ( !T->Left && !T->Right )
		return;

	vecLeft[ ident ] = 1;
	PrePrintTreeRec( T->Left, ident + 1 );
	vecLeft[ ident ] = 0;
	PrePrintTreeRec( T->Right, ident + 1 );
}

void
PrePrintTree( SearchTree T )
{
	PrePrintTreeRec( T, 0 );
}
