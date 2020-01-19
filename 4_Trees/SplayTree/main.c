#include <stdio.h>
#include "Splay.h"

typedef struct SplayNode *Position;

int
main( int argc, char *argv[] )
{
	SplayTree T = NULL;
	//extern Position Root;


	T = Insert( 1, T );
	T = Insert( 2, T );
	T = Insert( 3, T );
	T = Insert( 4, T );
	T = Insert( 5, T );
	T = Insert( 6, T );
	T = Insert( 7, T );

	PrintTree( T );

	return 0;
}
