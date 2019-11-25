#include "HeadFile.h"

struct Node
{
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};

Polynomial
ZeroPolynomial( Polynomial Poly )
{
	return ( Polynomial )malloc( sizeof ( struct Node ) );
}

Polynomial
AddPolynomial( Polynomial Poly1, Polynomial Poly2 )
{
	Polynomial PolySum = NULL, P = NULL;
	Polynomial P1 = NULL, P2 = NULL, EndP = NULL;
	P1 = Poly1->Next;
	P2 = Poly2->Next;

	PolySum = ZeroPolynomial( PolySum );
	P = PolySum;

	while ( P1 != NULL && P2 != NULL )
	{
		if ( P1->Exponent == P2->Exponent )
		{
			Insert( P1->Coefficient+P2->Coefficient, P1->Exponent, PolySum, P );
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if ( P1->Exponent > P2->Exponent )
		{
			Insert( P1->Coefficient, P1->Exponent, PolySum, P );
			P1 = P1->Next;
		}
		else
		{
			Insert( P2->Coefficient, P2->Exponent, PolySum, P );
			P2 = P2->Next;
		}
		
		P = P->Next;	
	}

	EndP = ( P1 == NULL ) ? P2 : P1;
	
	while ( EndP != NULL )
	{
		Insert( EndP->Coefficient, EndP->Exponent, PolySum, P );
		P = P->Next;
		EndP = EndP->Next;
	}

	return PolySum;
}

Polynomial
MultPolynomial( Polynomial Poly1, Polynomial Poly2 )
{
	Polynomial PolyProd = NULL;
	//PolyProd = MultPolynomialFirst( Poly1, Poly2 );
	//PolyProd = MultPolynomialSecond( Poly1, Poly2 );
	PolyProd = MultPolynomialThird( Poly1, Poly2 );

	return PolyProd;
}

void 
OrderInsert( int Coefficient, int Exponent, Polynomial Poly )
{
	Polynomial P, PreP;
	Polynomial TmpCell;
	P = Poly;

	while ( P->Next != NULL )
	{
		PreP = P;
		P = P->Next;
		if ( P->Exponent <= Exponent )
			break;
	}

	if ( P != Poly && P->Exponent == Exponent )
		P->Coefficient += Coefficient;
	else
	{
		TmpCell = ( Polynomial )malloc( sizeof( struct Node ) );

		if ( TmpCell == NULL )
			printf( "ERROR: Out of space!!!\n" );
		else
		{
			TmpCell->Coefficient = Coefficient;
			TmpCell->Exponent = Exponent;

			//It is important here!!!
			TmpCell->Next = NULL;
			
			if ( P == Poly || P->Exponent > Exponent )
				P->Next = TmpCell;
			else
			{
				PreP->Next = TmpCell;
				TmpCell->Next = P;
			}
		}
	}
}

void
OrderInsertNodes( int X[][2], int n, Polynomial Poly )
{
	int i;

	for ( i = 0; i < n; i++ )
		OrderInsert( X[i][0], X[i][1], Poly );
}

void 
Insert( int Coefficient, int Exponent, Polynomial Poly, Polynomial Pos )
{
	Polynomial TmpCell;

	TmpCell = ( Polynomial )malloc( sizeof ( struct Node ) );
	
	if ( TmpCell == NULL )
		printf( "ERROR: Out of space!!!\n");
	else
	{
		TmpCell->Coefficient = Coefficient;
		TmpCell->Exponent = Exponent;

		TmpCell->Next = Pos->Next;
		Pos->Next = TmpCell;
	}

}


void
PrintPolynomial( Polynomial Poly )
{
	Polynomial P = NULL;
	P = Poly->Next;

	while ( P != NULL )
	{
		printf( "--%d %d-- ", P->Coefficient, P->Exponent );
		P = P->Next;
	}
	printf( "\n" );

}

