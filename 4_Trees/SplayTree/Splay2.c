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
static Position Root = NULL;


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



static SplayTree
Splay( ElementType Item, Position G )
{
	Position P, X = G;
	
	if ( G->Left != NULL )
	{
		P = G->Left;
		if ( P->Left != NULL && 
			 P->Left->Element == Item )
		{
			//zig-zig
			X = P->Left;

			G->Left = P->Right;
			P->Left = X->Right;
			P->Right = G;
			X->Right = P;
		}
		else
		if ( P->Right != NULL &&
			 P->Right->Element == Item )
		{
			//zig-zag
			X = P->Right;
			
			P->Right = X->Left;
			G->Left = X->Right;
			X->Left = P;
			X->Right = G;
		}

		if ( G == Root && G->Left != NULL && 
				G->Left->Element == Item )
		{
			//zig
			P = G;
			X = P->Left;

			P->Left = X->Right;
			X->Right = P;
		}
	}

	if ( G->Right != NULL )
	{
		P = G->Right;
		if ( P->Right != NULL && 
			 P->Right->Element == Item )
		{
			//zag-zag
			X = P->Right;

			G->Right = P->Left;
			P->Right = X->Left;
			P->Left = G;
			X->Left = P;
		}
		else
		if ( P->Left != NULL &&
			 P->Left->Element == Item )
		{
			//zag-zig
			X = P->Left;

			G->Right = X->Left;
			P->Left = X->Right;
			X->Left = G;
			X->Right = P;
		}

		if ( G == Root && G->Right != NULL && 
				G->Right->Element == Item )
		{
			//zag
			P = G;
			X = P->Right;
			
			P->Right = X->Left;
			X->Left = P;
		}
	}

	return X;
}


SplayTree
Find( ElementType X, SplayTree T )
{
	Position Tmp = NULL;

	if ( T == NULL )
		return NULL;
	else if ( T->Element < X )
	{
		Tmp = Find( X, T->Right );
		if ( Tmp != NULL )
		{
			if ( T != Root )
				T->Right = Splay( X, T->Right );
			else
			{
				//There are some problems here.
				T = Splay( X, T );
				Root = T;
			}
		}
	}
	else
	if ( T->Element > X )
	{
		Tmp = Find( X, T->Left );
		if ( Tmp != NULL )
		{
			if ( T != Root )
				T->Left = Splay( X, T->Left );
			else
			{
				T = Splay( X, T );
				Root = T;
			}
		}
	}
	else
		return T;
	
	return Tmp;
}


static SplayTree
InsertRec( ElementType X, SplayTree T )
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
		T->Left = InsertRec( X, T->Left );
		if ( T != Root )
			T->Left = Splay( X, T->Left );
		else
		{
			T = Splay( X, T );
			Root = T;
		}
	}
	else
	if ( X > T->Element )
	{
		T->Right = InsertRec( X, T->Right );
		if ( T != Root )
			T->Right = Splay( X, T->Right );
		else
		{
			T = Splay( X, T );
			Root = T;
		}
	}

	return T;
}

SplayTree
Insert( ElementType X, SplayTree T )
{
	T = InsertRec( X, T );
	Root = T;

	return T;
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

