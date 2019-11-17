#include "List.h"

int main(void)
{
	List L = NULL;
	int Num[] = { 1, 2, 3, 4, 5 };
	int n = 5;

	L = MakeEmpty( L );
	InsertList( Num, n, L );
	SwapSucceed( 3, L );
	PrintList( L );
	

	return 0;
}

