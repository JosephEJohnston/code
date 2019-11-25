#ifndef __Poly_H__

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Polynomial;

Polynomial ZeroPolynomial( Polynomial Poly );
Polynomial AddPolynomial( Polynomial Poly1, Polynomial Poly2 );
Polynomial MultPolynomial( Polynomial Poly1, Polynomial Poly2 );

void OrderInsert( int Coefficient, int Exponent, Polynomial Poly );
void OrderInsertNodes( int X[][2], int n, Polynomial Poly );
void Insert( int Coefficient, int Exponent, Polynomial Poly, Polynomial Pos );
void PrintPolynomial( Polynomial Poly );


#endif
