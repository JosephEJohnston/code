#ifndef __Poly_H__
#define __Poly_H__

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Polynomial;

Polynomial ZeroPolynomial( Polynomial Poly );
Polynomial AddPolynomial( Polynomial Poly1, Polynomial Poly2 );
Polynomial MultPolynomial( Polynomial Poly1, Polynomial Poly2 );
Polynomial PowerPolynomial( Polynomial Poly, int P );

void OrderInsert( int Coefficient, int Exponent, Polynomial Poly );
void OrderInsertNodes( int X[][2], int n, Polynomial Poly );
void Insert( int Coefficient, int Exponent, Polynomial Poly, Polynomial Pos );
void DeletePolynomial( Polynomial Poly );
void PrintPolynomial( Polynomial Poly );
PtrToNode Advance( PtrToNode Pos );
int Coefficient( PtrToNode Pos );
int Exponent( PtrToNode Pos );


#endif
