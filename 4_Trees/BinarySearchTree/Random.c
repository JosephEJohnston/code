#include "Random.h"

static unsigned long Seed = 1;


double
Random( void )
{
	long TmpSeed;

	TmpSeed = A * ( Seed % Q ) - R * ( Seed / Q );
	if ( TmpSeed >= 0 )
		Seed = TmpSeed;
	else
		Seed = TmpSeed + M;

	return ( double ) Seed / M;
}

void
Initialize( unsigned long InitVal )
{
	Seed = InitVal;
}

int
RandomInteger( int X, int Y )
{
	int tmp;
	
	do 
		tmp = ( int )( ( Y + 1 ) * Random() );
	while ( tmp < X );

	return tmp;
}

/*
void
Count( int X, int Y )
{
	int i;
	int C[ Y + 1 ];
	for ( i = 0; i <= Y; i++ )
		C[i] = 0;

	for ( i = 0; i < 1000000; i++ )
		C[ RandomInteger( X, Y ) ]++;

	for ( i = 1; i <= Y; i++ )
		printf( "%d ", C[ i ] );
	printf( "\n" );
}
*/

void 
Swap( int *a, int *b )
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void
MakeRandomSequence( int n, int X, int Y, int a[] )
{
	int i;

	a[ 0 ] = X++;
	for ( i = 1 ; i < n ; i++ )
	{
		a[ i ] = X++;
		Swap( &a[ i ], &a[ RandomInteger( 0, i ) ] );
	}

}


