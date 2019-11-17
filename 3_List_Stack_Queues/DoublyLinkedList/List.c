#include "List.h"

struct Node
{
	ElementType Element;
	Position	Precede;
	Position	Succeed;
};


List
MakeEmpty( List L )
{
	return ( List )malloc( sizeof( struct Node ) );
}

Position
Find( ElementType X, List L )
{
	Position P;
	
	P = L->Succeed;
	while ( P != NULL && P->Element != X )
		P = P->Succeed;
	
	return P;
}

void
Insert( ElementType X, List L, Position P )
{
	Position TmpCell;

	TmpCell = ( Position )malloc( sizeof ( struct Node ) );
	if ( TmpCell == NULL )
		FatalError( "Out of space!!!" );

	TmpCell->Element = X;
	TmpCell->Precede = P;
	TmpCell->Succeed = P->Succeed;
	P->Succeed = TmpCell;

}

void
InsertList( ElementType X[], int n, List L )
{
	Position P;
	int i;

	P = L;
	for ( i = 0; i < n; i++ )
	{
		Insert( X[i], L, P );
		P = P->Succeed;
	}
}

void
PrintList( List L )
{
	Position P;
	P = L->Succeed;

	while ( P != NULL )
	{
		PrintElement( P );
		P = P->Succeed;
	}

}

void
SwapPrecede( ElementType X, List L )
{
	Position P, PtrPre;
	P = Find( X, L );

	if ( P == NULL || L->Succeed == P )
		return;
	else
	{
		PtrPre = P->Precede;

		PtrPre->Succeed = P->Succeed;
		P->Succeed = PtrPre;
		P->Precede = PtrPre->Precede;
		(PtrPre->Precede)->Succeed = P;
		PtrPre->Precede = P;
	}
}

void 
SwapSucceed( ElementType X, List L )
{
	Position P, PtrSuc;
	P = Find( X, L );

	if ( P == NULL || P->Succeed == NULL )
		return;
	else
	{
		PtrSuc = P->Succeed;

		P->Succeed = PtrSuc->Succeed;
		PtrSuc->Succeed = P;
		PtrSuc->Precede = P->Precede;
		(PtrSuc->Precede)->Succeed = PtrSuc;
		P->Precede = PtrSuc;
	}
}



