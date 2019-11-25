#include "HeadFile.h"


struct Node
{
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};


int
CountItems( Polynomial Poly )
{
	Polynomial P = NULL;
	int count = 0;

	P = Poly->Next;

	while ( P != NULL )
	{
		count++;
		P = P->Next;
	}

	return count;
}

void 
Union( Polynomial Result, Polynomial Poly )
{
	Polynomial PR = NULL, P = NULL;
	Polynomial PrePR = NULL;
	
	PR = Result->Next;
	P = Poly->Next;
	PrePR = Result;
	
	while ( PR != NULL && P != NULL )
	{
		if ( PR->Exponent > P->Exponent )
		{
			PrePR = PR;
			PR = PR->Next;			
		}
		else if ( PR->Exponent < P->Exponent )
		{
			//Change node owner
			Poly->Next = P->Next;
			P->Next = PR;
			PrePR->Next = P;

			//Reset P
			P = Poly->Next;
		}
		else
		{
			//Combine and delete
			PR->Coefficient += P->Coefficient;
			Poly->Next = P->Next;
			
			//Remember to do this
			P->Next = NULL;

			free( P );
			P = Poly->Next;
		}
	}

	PrePR->Next = Poly->Next;
	Poly->Next = NULL;
}


PtrToNode
MakeMultNode( PtrToNode M, PtrToNode N )
{
	int NewCoefficient = 
		M->Coefficient * N->Coefficient;
	int NewExponent =
		M->Exponent + N->Exponent;

	PtrToNode TmpCell = NULL;

	TmpCell = malloc( sizeof( struct Node ) );

	if ( TmpCell == NULL )
	{
		Error( "Out of space!!!" );
		return NULL;
	}

	TmpCell->Coefficient = NewCoefficient;
	TmpCell->Exponent = NewExponent;

	return TmpCell;
}


PtrToNode
MakeNode( int Coefficient, int Exponent )
{
	PtrToNode TmpCell = NULL;

	TmpCell = malloc( sizeof( struct Node ) );

	if ( TmpCell == NULL )
	{
		Error( "Out of space!!!" );
		return NULL;
	}

	TmpCell->Coefficient = Coefficient;
	TmpCell->Exponent = Exponent;

	return TmpCell;
}


Polynomial
MultPolynomialFirst( Polynomial Poly1, Polynomial Poly2 )
{
	Polynomial PolyProd = NULL; 
	Polynomial P1 = NULL, P2 = NULL; 
	P1 = Poly1->Next;
	P2 = Poly2->Next;

	PolyProd = ZeroPolynomial( PolyProd );

	while ( P1 != NULL )
	{
		while ( P2 != NULL )
		{
			OrderInsert( P1->Coefficient*P2->Coefficient, P1->Exponent+P2->Exponent, PolyProd );
			P2 = P2->Next;
		}
		P2 = Poly2->Next;
		P1 = P1->Next;
	}

	return PolyProd;
}


Polynomial
MultPolynomialSecond( Polynomial Poly1, Polynomial Poly2 )
{
	Polynomial PolyProd = NULL, TmpProd = NULL; 
	Polynomial P1 = NULL, P2 = NULL; 
	Polynomial T1 = NULL, T2 = NULL;
	Polynomial TmpTP = NULL;

	T1 = Poly1;
	T2 = Poly2;
	
	if ( CountItems( Poly1 ) > CountItems( Poly2 ) )
	{
		T1 = Poly2;
		T2 = Poly1;
	}
	P1 = T1->Next;
	P2 = T2->Next;


	PolyProd = ZeroPolynomial( PolyProd );
	TmpProd = ZeroPolynomial( TmpProd );
	TmpTP = TmpProd;

	while ( P1 != NULL )
	{
		while ( P2 != NULL )
		{
			Insert( P1->Coefficient*P2->Coefficient, 
					P1->Exponent+P2->Exponent, TmpProd, TmpTP );


			TmpTP = TmpTP->Next;	
			P2 = P2->Next;
		}
		Union( PolyProd, TmpProd );

		P2 = T2->Next;
		TmpTP = TmpProd;
		P1 = P1->Next;
	}

	TmpProd->Next = NULL;
	free( TmpProd );
	TmpProd = NULL;

	return PolyProd;
}


Polynomial
MultPolynomialThird( Polynomial Poly1, Polynomial Poly2 )
{
	Polynomial PolyProd = NULL, TmpProd = NULL; 
	Polynomial TmpCell = NULL;
	Polynomial P1 = NULL, P2 = NULL; 
	PriorityQueue Heap = NULL;
	int M, N;

	P1 = Poly1->Next;
	P2 = Poly2->Next;
	M = CountItems( Poly1 );
	N = CountItems( Poly2 );
	PolyProd = ZeroPolynomial( PolyProd );
	TmpProd = PolyProd;

	if ( ( M * N < M ) || ( M * N < N ) )
	{
		printf( "ERROR: Int over flow\n" );
		return NULL;
	}
	else
	{
		if ( M != 0 && N != 0 )
			Heap = HeapInitialize( M * N + 1, 
					MakeNode( 0, P1->Exponent + P2->Exponent + 1 ) );
		else
		{
			Error( "Input poly is NULL!!!" );
			return NULL;
		}
	}

	while ( P1 != NULL )
	{
		while ( P2 != NULL )
		{
			HeapInsert( MakeMultNode( P1, P2 ), Heap );
			P2 = P2->Next;
		}
		P2 = Poly2->Next;
		P1 = P1->Next;
	}

	/* Sort the poly list then. */
	while ( !IsEmpty( Heap ) )
	{
		TmpCell = HeapDeleteMax( Heap );	
		//printf( "%d ", TmpCell->Exponent );
		if ( TmpProd->Exponent == TmpCell->Exponent )
			TmpProd->Coefficient += TmpCell->Coefficient;
		else
		{
			Insert( TmpCell->Coefficient, TmpCell->Exponent, 
					PolyProd, TmpProd );
			TmpProd = TmpProd->Next;
		}
	}
	
	DeleteHeap( Heap );

	return PolyProd;
}
