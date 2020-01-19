#include "TreeRandomTest.h"
#include "Deletions.c"

int
Compute( int h )
{
	if ( h == 0 )
		return 1;
	else
	if ( h == 1 )
		return 2;
	
	return Compute( h - 1 ) + Compute( h - 2 ) + 1;
}

int 
main( void )
{
	//InitializeCursorSpace( );

	SearchTree T = NULL;
	//SearchTree T = 0;

	/*
	T = Insert( 3, T );
	T = Insert( 1, T );
	T = Insert( 4, T );
	T = Insert( 6, T );
	T = Insert( 9, T );
	T = Insert( 2, T );
	T = Insert( 5, T );
	T = Insert( 7, T );
	*/

	Initialize( 6 );	

	int n = 20;
	int a[ n ];
	int X = 1, Y = 50;
	
	T = RandomInserts( n, X, Y, a, T );
	PrePrintTree( T );

	T = RandomDeletes( n / 2, X, Y, a, T, ThirdDelete );
	PrePrintTree( T );

	//printf( "\n**%d**\n", Retrieve( Find( 9, T ) ) );
	

	/*
	int i;
	for ( i = 0; i < 100; i++ )
		printf( "%d\n", RandomInteger( 1, 20 ) );
	
	int a[21];
	int i;

	MakeRandomSequence( a, 20, 5, 25 );

	for ( i = 0; i < 21; i++ )
		printf( "%d ", a[ i ] );
	printf( "\n" );
	*/

	printf( "%d\n", Compute( 15 ) ); 

	return 0;
}
