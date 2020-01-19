#include <stdlib.h>
#include "Stack.h"
#include "AvlTree.h"
#include "Error.h"

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int		Height;
};

struct Node
{
	StackElementType	Element;
	PtrToNode			Next;
};

int
IsEmpty( Stack S )
{
	return S->Next == NULL;
}

Stack
CreateStack( void )
{
	Stack S;

	S = malloc( sizeof( struct Node ) );
	if ( S == NULL )
		FatalError( "Out of space!!!" );
	StackMakeEmpty( S );
	return S;
}

void
DisposeStack( Stack S )
{
	StackMakeEmpty( S );
	free( S );
	S = NULL;
}

void
StackMakeEmpty( Stack S )
{
	if ( S == NULL )
		Error( "Must use CreateStack first" );
	else
		while ( !IsEmpty( S ) )
			Pop( S );
}

void
Push( StackElementType X, Stack S )
{
	PtrToNode TmpCell;

	TmpCell = malloc( sizeof( struct Node ) );
	if ( TmpCell == NULL )
		FatalError( "Out of space!!!" );
	else
	{
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}

StackElementType
Top( Stack S )
{
	if ( !IsEmpty( S ) )
		return S->Next->Element;
	Error( "Empty stack" );
	return NULL;
}


void
Pop( Stack S )
{
	PtrToNode FirstCell;

	if ( IsEmpty( S ) )
		Error( "Empty stack" );
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free( FirstCell );
	}
	
}

