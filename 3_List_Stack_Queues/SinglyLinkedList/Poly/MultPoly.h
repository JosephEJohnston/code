#ifndef __MultPoly_H__

int CountItems( Polynomial Poly );
void Union( Polynomial Result, Polynomial Poly );
PtrToNode MakeMultNode( PtrToNode M, PtrToNode N );
PtrToNode MakeNode( int Coefficient, int Exponent );

Polynomial MultPolynomialFirst( Polynomial Poly1, Polynomial Poly2 );
Polynomial MultPolynomialSecond( Polynomial Poly1, Polynomial Poly2 );
Polynomial MultPolynomialThird( Polynomial Poly1, Polynomial Poly2 );


#endif
