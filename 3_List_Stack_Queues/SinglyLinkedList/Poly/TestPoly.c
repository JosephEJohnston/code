#include "HeadFile.h"

int main(void)
{
	Polynomial L = NULL, G = NULL;
	Polynomial PS = NULL;


	if (0) 
	{
		int n1 = 2000, n2 = 5000;
		int i;
		int X1[n1][ 2 ]; 
		int X2[n2][ 2 ]; 
		for ( i = 0; i < n1; i++ )
		{
			X1[i][0] = i;
			X1[i][1] = i + 1;
		}
		for ( i = 0; i < n2; i++ )
		{
			X2[i][0] = i;
			X2[i][1] = i + 1;
		}

		L = ZeroPolynomial( L );
		G = ZeroPolynomial( G );
		OrderInsertNodes( X1, n1, L );
		OrderInsertNodes( X2, n2, G );
		PS = MultPolynomial( L, G );
		//PrintPolynomial( PS );
	}
	else
	{
		int n1 = 7, n2 = 4;
		int X1[][ 2 ] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 7, 8 }, { 9, 10 }, { 11, 13 }, { 14, 19 } };
		int X2[][ 2 ] = { { 6, 7 }, { 8, 10 }, { 7, 9 }, { 11, 3 } };

		L = ZeroPolynomial( L );
		G = ZeroPolynomial( G );
		OrderInsertNodes( X1, n1, L );
		OrderInsertNodes( X2, n2, G );
		PrintPolynomial( L );
		PrintPolynomial( G );
		PS = MultPolynomial( L, G );
		PrintPolynomial( PS );
	}


	return 0;
}


