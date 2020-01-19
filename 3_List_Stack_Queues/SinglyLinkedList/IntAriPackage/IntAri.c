#include "IntAri.h"

struct Number
{
	int CurNum;
	BigInteger Next;
};

BigInteger
NewNumber( int X )
{
	BigInteger NewNum = NULL;

	NewNum = malloc( sizeof( struct Number ) );

	if ( NewNum == NULL )
	{
		printf( "FatalError: Out of Space!!!\n" );
		return NULL;
	}

	NewNum->Next = NULL;
	NewNum->CurNum = X;
	return NewNum;
}

BigInteger
Intialize( void )
{
	return NewNumber( 0 );
}

void
Carry( BigInteger X )
{
	BigInteger NewNum = NULL;

	if ( X->CurNum > MaxCurNum )
	{
		NewNum = NewNumber( ( X->CurNum - MaxCurNum ) / MaxCurNum );
		X->CurNum -= MaxCurNum;

		if ( NewNum != NULL )
		{
			X->Next = NewNum;
			NewNum->Next = NULL;

		}

		printf( "FatalError: Out of Space!!!\n" );
	}

	printf( "Error: Don't need to carry!!!\n" );

}

BigInteger
MakeBigNumber( char X[] )
{
	BigInteger NewNum = NULL;
	BigInteger TmpNum = NULL;
	int CurNum = 0, Sum = 0;
	int i;

	NewNum = Intialize();
	TmpNum = NewNum->Next;
	TmpNum->Next = Intialize();
	TmpNum = TmpNum->Next;

	for ( i = 0; X[ i ] != '\0'; i++ ) 
	{
		Sum = X[ i ] + Sum * 10;		
		
		if ( Sum > MaxCurNum )
		{
			TmpNum->CurNum = Sum;
			Carry( TmpNum );

		}
	}

}
