#include <stdio.h>
#include "AvlTree.h"
#include "Stack.h"

int main( void )
{
	AvlTree T = NULL;

	T = Insert( 1, T );
	T = Insert( 2, T );
	T = Insert( 3, T );
	T = Insert( 4, T );
	//T = Insert( 5, T );
	//T = Insert( 6, T );
	//T = Insert( 7, T );
	//T = Insert( 8, T );
	//T = Insert( 9, T );

	/*
	T = Insert( 10, T );
	T = Insert( 11, T );
	T = Insert( 12, T );
	T = Insert( 13, T );
	*/


	/*
	T = Delete( 4, T );
	T = Delete( 5, T );
	T = Delete( 9, T );
	*/

	PrintTree( T );

	//printf( "000\n" );

	return 0;
}

