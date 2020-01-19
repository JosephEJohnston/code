#ifndef _Random_H
#define _Random_H

#define A 48271L
#define M 2147483647L
#define Q ( M / A )
#define R ( M % A )

double Random( void );
void Initialize( unsigned long InitVal );
int RandomInteger( int X, int Y );
void MakeRandomSequence( int n, int X, int Y, int a[] );

#endif
