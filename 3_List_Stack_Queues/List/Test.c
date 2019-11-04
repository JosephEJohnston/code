#include "List.h"

int main(void)
{
	List L = NULL;
	List P = NULL;
	int Elements[] = { 0, 2, 10, 4, 8, 6, 7 };
	int n = 7;

	int Pos[] = { 1, 3, 5 };
	int pn = 3;

	L = MakeEmpty( L );
	P = MakeEmpty( P );
	InsertList( L, Elements, n );
	InsertList( P, Pos, pn );
	PrintList( L );
	printf("\n");
	PrintList( P );
	printf("\n");
	PrintLots( L, P );


	return 0;
}

