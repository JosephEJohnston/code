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
InsertList( ElementType X[], int n, List L )
{
	Position P;
	int i;

	P = L;
	for (i = 0; i < n; i++)
	{
		Insert( X[i], L, P );
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
			FatalError( "Out of bound!!!" );
	}
	
}


void
SwapPrecede(  ElementType X, List L )
{
	Position P, Pre, BefPre;

	Pre = L;
	P = L->Next;
	/* We need to find preceding poiner, 
	 * so we can't use Find. */
	while ( P != NULL && P->Element != X )	
	{
		BefPre = Pre;
		Pre = P;
		P = P->Next;
	}

	if ( P == NULL || P == L->Next )
		return;
	else
	{
		Pre->Next = P->Next;
		P->Next = Pre;
		BefPre->Next = P;
	}

}

void
SwapSucceed( ElementType X, List L )
{
	Position P, Suc, BefP;

	BefP = L;
	P = L->Next;
	while ( P != NULL && P->Element != X )
	{
		BefP = P;
		P = P->Next;
	}

	if ( P == NULL || P->Next == NULL )
		return;
	else
	{
		Suc = P->Next;
		P->Next = Suc->Next;
		Suc->Next = P;
		BefP->Next = Suc;
	}

}



List
Intersection( List L, List P )
{
	List New = NULL;
	Position PtrL, PtrP, PtrNew;
	PtrL = L->Next;
	PtrP = P->Next;
	New = MakeEmpty( New );
	PtrNew = New;


	while ( PtrL != NULL && PtrP != NULL )
	{
		if ( PtrL->Element < PtrP->Element )
			PtrL = PtrL->Next;
		else if ( PtrL->Element > PtrP->Element )
			PtrP = PtrP->Next;
		else
		{
			Insert( PtrL->Element, New, PtrNew );
			PtrNew = PtrNew->Next;
			PtrL = PtrL->Next;
			PtrP = PtrP->Next;
		}
	}

	return New;
}

List
Union( List L, List P )
{
	List New = NULL;
	Position PtrL, PtrP, PtrNew;
	PtrL = L->Next;
	PtrP = P->Next;
	New = MakeEmpty( New );
	PtrNew = New;

	while ( PtrL != NULL && PtrP != NULL )
	{
		if ( PtrL->Element < PtrP->Element )
		{
			Insert( PtrL->Element, New, PtrNew );
			PtrL = PtrL->Next;
		}
		else if ( PtrL->Element > PtrP->Element )
		{
			Insert( PtrP->Element, New, PtrNew );
			PtrP = PtrP->Next;
		}
		else
		{
			Insert( PtrL->Element, New, PtrNew );
			PtrL = PtrL->Next;
			PtrP = PtrP->Next;
		}
		PtrNew = PtrNew->Next;
	}

	while ( PtrL )
	{
		Insert( PtrL->Element, New, PtrNew );
		PtrL = PtrL->Next;
		PtrNew = PtrNew->Next;
	}

	while ( PtrP )
	{
		Insert( PtrP->Element, New, PtrNew );
		PtrP = PtrP->Next;
		PtrNew = PtrNew->Next;
	}

	return New;
}


