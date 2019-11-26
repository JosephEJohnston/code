#include "HeadFile.h"

int main( void )
{
	Polynomial Poly = NULL;
	int P = 2;
	int X[][ 2 ] = { { 6, 7 }, { 8, 10 }, { 7, 9 }, { 11, 3 } };

	Poly = ZeroPolynomial( Poly );
	OrderInsertNodes( X, 4, Poly );
	PrintPolynomial( Poly );
	Poly = PowerPolynomial( Poly, P );
	PrintPolynomial( Poly );
}
