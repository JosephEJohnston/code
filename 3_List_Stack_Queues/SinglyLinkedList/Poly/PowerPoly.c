#include "HeadFile.h"

Polynomial
PowerPoly( Polynomial Poly, int P )
{
	Polynomial PowPoly = NULL;
	Polynomial TmpPoly = NULL;
	Polynomial DeletePoly = NULL;
	int TmpP = P;

	PowPoly = CopyPoly( Poly );
	TmpPoly = PowerZeroPoly( );

	while ( TmpP > 1 )
	{
		if ( TmpP % 2 == 0 )
		{
			DeletePoly = PowPoly;
			PowPoly = MultPolynomial( PowPoly, PowPoly );

			TmpP /= 2;
		}
		else
		{
			DeletePoly = TmpPoly;
			TmpPoly = MultPolynomial( PowPoly, TmpPoly );

			TmpP -= 1;
		}

		DeletePolynomial( DeletePoly );
		DeletePoly = NULL;
	}

	DeletePoly = PowPoly;
	PowPoly = MultPolynomial( PowPoly, TmpPoly );
	DeletePolynomial( DeletePoly );
	DeletePoly = NULL;

	return PowPoly;
}

Polynomial
PowerZeroPoly( void )
{
	Polynomial PowerPoly = NULL;

	PowerPoly = ZeroPolynomial( PowerPoly );
	Insert( 1, 0, PowerPoly, PowerPoly );


	return PowerPoly;
}

Polynomial
CopyPoly( Polynomial Poly )
{
	Polynomial CopyPoly = NULL;
	Polynomial TmpPoly = NULL, TmpCopyPoly = NULL;	

	CopyPoly = ZeroPolynomial( CopyPoly );
	TmpPoly = Advance( Poly );
	TmpCopyPoly = CopyPoly;

	while ( TmpPoly )
	{
		Insert( Coefficient( TmpPoly ), Exponent( TmpPoly ),
				CopyPoly, TmpCopyPoly );
		TmpCopyPoly = Advance( TmpCopyPoly );
		TmpPoly = Advance( TmpPoly );
	}

	return CopyPoly;
}
