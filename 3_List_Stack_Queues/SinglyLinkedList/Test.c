#include "List.h"

int main(void)
{
	List L = NULL;
	List P = NULL;
	List New = NULL;
	int Elements[] = { 0, 2, 4, 8 };
	int n = 4;

	int Pos[] = { 1, 3, 4, 5, 8 };
	int pn = 5;

	L = MakeEmpty( L );
	P = MakeEmpty( P );
	InsertList( Elements, n, L );
	InsertList( Pos, pn, P );
	PrintList( L );
	printf("\n");
	//PrintList( P );
	//printf("\n");
	New = Union( L, P );
	PrintList( New );

	return 0;
}

