#include "List.h"

struct Node
{
	ElementType Element;
	Position	Next;
};


List
MakeEmpty( List L )
{
	return ( List )malloc( sizeof( struct Node ) );
}

int
IsEmpty( List L )
{
	return L->Next == NULL;
}

int 
IsLast( Position P, List L )
{
	return P->Next == NULL;
}

Position
Find( ElementType X, List L )
{
	Position P;

	P = L->Next;
	while ( P != NULL && P->Element != X)
		P = P->Next;

	return P;
}

void
Delete( ElementType X, List L )
{
	Position P, TmpCell;

	P = FindPrevious( X, L );

	if ( !IsLast(P, L) )
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free( TmpCell );
	}
}

Position 
FindPrevious( ElementType X, List L )
{
	Position P;

	P = L;
	while ( P->Next != NULL && P->Next->Element != X )
		P = P->Next;

	return P;
}

void
Insert( ElementType X, List L, Position P )
{
	Position TmpCell;

	TmpCell = malloc( sizeof( struct Node ) );
	if ( TmpCell == NULL )
		FatalError( "Out of space!!!" );

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}


void
DeleteList( List L )
{
	Position P, Tmp;

	P = L->Next;
	L->Next = NULL;
	while ( P != NULL )
	{
		Tmp = P->Next;
		free( P );
		P = Tmp;
	}
}

Position
Header( List L )
{
	return L;
}

Position
First( List L )
{
	/* Not check whether L is NULL here */
	return L->Next;
}

Position
Advance( Position P )
{
	return P->Next;
}


ElementType
Retrieve( Position P )
{
	return P->Element;
}

void
InsertList( List L, ElementType Elements[], int n )
{
	Position P;
	int i;

	P = L;
	for (i = 0; i < n; i++)
	{
		Insert( Elements[i], L, P );
		P = P->Next;
	}

}

void
PrintList( List L )
{
	Position P;

	P = L;
	while ( P->Next != NULL )
	{
		P = P->Next;
		PrintElement( P );
	}

}

void
PrintLots( List L, List P )
{
	Position CurL, CurP;
	int i = 0, j;

	CurL = L;
	CurP = P;

	while ( CurP->Next != NULL )
	{
		CurP = CurP->Next;
		j = CurP->Element;

		for ( ; (i<j) && CurL->Next != NULL; i++)
			CurL = CurL->Next;

		if ( CurL->Next != NULL )
			PrintElement( CurL );
		else
			FatalError("Out of bound!!!");
	}
	
}


