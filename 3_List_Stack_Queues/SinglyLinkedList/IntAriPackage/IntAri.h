#ifdef __IntAri_H__
#define __IntAri_H__

//sqrt(Int_MAX) ~= 46340
//It can be obtain by sqrt( ( ( unsigned )( -1 ) ) >> 1 )
#define MaxCurNum 10000

struct Number;
typedef Number *BigInteger;

BigInteger NewNumber( int X );
BigInteger Intialize( void );
void Carry( BigInteger X );
BigInteger MakeBigNumber( char X[] );

BigInteger Multiplication( BigInteger X, BigInteger Y );
BigInteger Addition( BigInteger X, BigInteger Y );
BigInteger Power( BigInteger X, int P );


#ifndef
