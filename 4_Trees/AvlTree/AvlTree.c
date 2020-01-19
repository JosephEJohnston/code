#include <stdio.h>
#include <stdlib.h>
#include "AvlTree.h"
#include "Stack.h"
#include "Error.h"

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int		Height;
};

static int
Max( int A, int B )
{
	if ( A > B )
		return A;
	else
		return B;
}

static int
Height( Position P )
{
	if ( P == NULL )
		return -1;
	else
		return P->Height;
}

static Position
SingleRotateWithLeft( Position K2 )
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max( Height( K2->Left ),
								 Height( K2->Right ) ) + 1;
	K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

	return K1; /* New root */
}

static Position
SingleRotateWithRight( Position K1 )
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = Max( Height( K1->Left ),
								 Height( K1->Right ) ) + 1;
	K2->Height = Max( Height( K2->Left ), K1->Height ) + 1;

	return K2;
}

/*
static Position
DoubleRotateWithLeft( Position K3 )
{
	// Rotate between K1 and K2 
	K3->Left = SingleRotateWithRight( K3->Left );

	// Rotate between K3 and K2 
	return SingleRotateWithLeft( K3 );
}
*/

static Position
DoubleRotateWithLeft( Position K3 )
{
	Position K1, K2;

	K1 = K3->Left;
	K2 = K1->Right;

	K1->Right = K2->Left;
	K3->Left = K2->Right;
	K2->Left = K1;
	K2->Right = K3;

	return K2;
}


/*
static Position
DoubleRotateWithRight( Position K1 )
{
	K1->Right = SingleRotateWithLeft( K1->Right );

	return SingleRotateWithRight( K1 );
}
*/

static Position
DoubleRotateWithRight( Position K1 )
{
	Position K2, K3;

	K3 = K1->Right;
	K2 = K3->Left;

	K1->Right = K2->Left;
	K3->Left = K2->Right;
	K2->Left = K1;
	K2->Right = K3;

	return K2;
}


/*
AvlTree
Insert( ElementType X, AvlTree T )
{
	if ( T == NULL )
	{
		// Create and return a one-node tree 
		T = malloc( sizeof( struct AvlNode ) );
		if ( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = X; T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else
	if ( X < T->Element ) 
	{
		T->Left = Insert( X, T->Left );
		if ( ( Height( T->Left ) - Height( T->Right ) ) == 2 )
		{
			if ( X < T->Left->Element )
				T = SingleRotateWithLeft( T );
			else
				T = DoubleRotateWithLeft( T );
		}
	}
	else
	if ( X > T->Element )
	{
		T->Right = Insert( X, T->Right );
		if ( Height( T->Right ) - Height( T->Left ) == 2 )
		{
			if ( X > T->Right->Element )
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateWithRight( T );
		}
	}
	// Else X is in the tree already; we'll do nothing 

	T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
	return T;
}
*/

Position
FindMin( AvlTree T )
{
	Position P = NULL;

	P = T;
	if ( P != NULL )
		while ( P->Left != NULL )
			P = P->Left;

	return P;
}


AvlTree
Insert( ElementType X, AvlTree T )
{
	Stack S = NULL;
	Position P = NULL;
	Position LastP = NULL, NextP = NULL;

	S = CreateStack( );
	P = T;

	// Find approapiate position to insert.
	while ( P != NULL )
	{
		Push( P, S );

		if ( X < P->Element )
			P = P->Left;
		else 
		if ( X > P->Element )
			P = P->Right;
		else
		{
			DisposeStack( S );
			Error( "X is already in the tree" );
		}
	}

	// Insert X into tree.
	P = malloc( sizeof( struct AvlNode ) );
	if ( P == NULL )
	{
		DisposeStack( S );
		FatalError( "Out of space!!!" );
	}
	else
	{
		P->Element = X; P->Height = 0;
		P->Left = NULL; P->Right = NULL;

		if ( !IsEmpty( S ) )
			if ( ( LastP = Top( S ) ) != NULL )
			{
				if ( P->Element < LastP->Element )
					LastP->Left = P;
				else
					LastP->Right = P;

				LastP->Height = Max( Height( LastP->Left ), 
									 Height( LastP->Right ) ) + 1;
			}
	}


	// Update heights.
	while ( !IsEmpty( S ) )
	{
		P = Top( S );
		Pop( S );

		if ( NextP != NULL )
		{
			if ( NextP->Element < P->Element )
				P->Left = NextP;
			else
				P->Right = NextP;
			NextP = NULL;
		}

		if ( Height( P->Left ) - Height( P->Right ) == 2 )
		{
			if ( X > P->Left->Element )
				P = SingleRotateWithLeft( P );
			else
				P = DoubleRotateWithLeft( P );
			NextP = P;
		}
		else if ( Height( P->Right ) - Height( P->Left ) == 2 )
		{
			if ( X > P->Right->Element )
				P = SingleRotateWithRight( P );
			else
				P = DoubleRotateWithRight( P );
			NextP = P;
		}


		P->Height = Max( Height( P->Left ), Height( P->Right ) ) + 1;
	}

	DisposeStack( S );

	return P;
}

AvlTree
Delete( ElementType X, AvlTree T )
{
	Position TmpCell;

	if ( T == NULL )
		Error( "Element not found" );
	else
	if ( X < T->Element )
	{
		T->Left = Delete( X, T->Left );
		if ( ( Height( T->Right ) - Height( T->Left ) ) == 2 )
		{
			if ( X > T->Right->Element )
				T = SingleRotateWithRight( T );
			else
				T = DoubleRotateWithRight( T );
		}
	}
	else
	if ( X > T->Element )
	{
		T->Right = Delete( X, T->Right );
		if ( Height( T->Left ) - Height( T->Right ) == 2 )
		{
			if ( X < T->Left->Element )
				T = SingleRotateWithLeft( T );
			else
				T = DoubleRotateWithLeft( T );
		}
	}
	else
	if ( T->Left && T->Right )
	{
		TmpCell = FindMin( T->Right );
		T->Element = TmpCell->Element;
		T->Right = Delete( T->Element, T->Right );

	}
	else
	{
		TmpCell = T;
		if ( T->Left == NULL )
			T = T->Right;
		else if ( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	if ( T != NULL )
		T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

	return T;
}


static void
PrintTreeRec( AvlTree T, int ident, int VecLeft[] )
{
	int i;

	if ( ident > 0 )
	{
		for ( i = 0; i < ident - 1; i++ )
			printf( VecLeft[ i ] ? "│  " : "   " ); 
		printf( VecLeft[ ident - 1 ] ? "├──" : "└──" );
	}


	if ( T == NULL )
		printf( "(null) (-1)\n" );
	else
	{
		printf( "%d (%d)\n", T->Element, Height( T ) );

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
PrintTree( AvlTree T )
{
	int VecLeft[ 100 ];
	
	PrintTreeRec( T, 0, VecLeft );
}

