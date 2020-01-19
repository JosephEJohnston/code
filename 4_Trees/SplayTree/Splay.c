#include "Splay.h"
#include "Error.h"
#include <stdlib.h>
#include <stdio.h>

struct SplayNode
{
	ElementType Element;
	SplayTree	Left;
	SplayTree	Right;
	//SplayTree	Parent;
};

typedef struct SplayNode *Position;
static Position NullNode = NULL;


SplayTree
Initialize( void )
{
	if ( NullNode == NULL )
	{
		NullNode = malloc( sizeof( struct SplayNode ) );
		if ( NullNode == NULL )
			FatalError( "Out of space!!!" );
		NullNode->Left = NullNode->Right = NullNode;
	}
	return NullNode;
}

static Position
SingleRotateWithLeft( Position K2 )
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	return K1;
}

static Position
SingleRotateWithRight( Position K1 )
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	return K2;
}

static Position
DoubleRotateWithLeft( Position K3 )
{
	K3->Left = SingleRotateWithRight( K3->Left );
	
	return SingleRotateWithLeft( K3 );
}

static Position
DoubleRotateWithRight( Position K3 )
{
	K3->Right = SingleRotateWithLeft( K3->Right );
	
	return SingleRotateWithRight( K3 );
}

static SplayTree
SplayWithRoot( ElementType Item, Position T )
{
	if ( T != NULL && T->Element != Item )
	{
		if ( T->Left != NULL &&
				T->Left->Element == Item )
			//zig
			T = SingleRotateWithLeft( T );
		else
		if ( T->Right != NULL &&
				T->Right->Element == Item )
			//zag
			T = SingleRotateWithRight( T );
	}

	return T;
}


static SplayTree
SplayWithLeft( ElementType Item, Position T )
{
	if ( T->Left != NULL )
	{
		//zig-zag
		if ( T->Left->Right != NULL && 
				T->Left->Right->Element == Item )
			T = DoubleRotateWithLeft( T );
	}
	else
	if ( T->Left != NULL )
	{
		//zig-zig
		if ( T->Left->Left != NULL &&
				T->Left->Left->Element == Item )
		{
			T->Left = SingleRotateWithLeft( T->Left );
			T = SingleRotateWithLeft( T );
		}
	}

	return T;
}


static SplayTree
SplayWithRight( ElementType Item, Position T )
{
	if ( T->Right != NULL )
	{
		//zag-zig
		if ( T->Right->Left != NULL &&
				T->Right->Left->Element == Item )
			T = DoubleRotateWithRight( T );
	}
	else
	if ( T->Right != NULL )
	{
		//zag-zag
		if ( T->Right->Right != NULL &&
				T->Right->Right->Element == Item )
		{
			T->Right = SingleRotateWithRight( T->Left );
			T = SingleRotateWithRight( T );
		}
	}

	return T;
}

SplayTree
Find( ElementType X, SplayTree T )
{
	return NullNode;
}


SplayTree
Insert( ElementType X, SplayTree T )
{
	if ( T == NULL )
	{
		T = malloc( sizeof( struct SplayNode ) );

		if ( T == NULL )
			FatalError( "Out of space!!!" );

		T->Element = X;
		T->Left = NULL;
		T->Right = NULL;
	}
	else
	if ( X < T->Element )
	{
		T->Left = Insert( X, T->Left );
		T = SplayWithLeft( X, T );
	}
	else
	if ( X > T->Element )
	{
		T->Right = Insert( X, T->Right );
		T = SplayWithRight( X, T );
	}

	return SplayWithRoot( X, T );
}



static void
PrintTreeRec( SplayTree T, int ident, int VecLeft[] )
{
	int i;

	if ( ident > 0 )
	{
		for ( i = 0; i < ident - 1; i++ )
			printf( VecLeft[ i ] ? "│  " : "   " ); 
		printf( VecLeft[ ident - 1 ] ? "├──" : "└──" );
	}


	if ( T == NULL )
		printf( "(null)\n" );
	else
	{
		printf( "%d\n", T->Element );

		if ( T->Right || T->Left )
		{	
			VecLeft[ ident ] = 1;
			PrintTreeRec( T->Left, ident + 1, VecLeft );
			VecLeft[ ident ] = 0;
			PrintTreeRec( T->Right, ident + 1, VecLeft );
		}
	}
}

void
PrintTree( SplayTree T )
{
	int VecLeft[ 100 ];
	
	PrintTreeRec( T, 0, VecLeft );
}

