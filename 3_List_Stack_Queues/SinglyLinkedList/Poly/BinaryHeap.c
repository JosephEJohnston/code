#include "HeadFile.h"

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

struct Node
{
	int Coefficient;
	int Exponent;
	PtrToNode Next;
};

void Error( char message[] )
{
	printf( "Error: %s\n", message );
}

void FatalError( char message[] )
{
	printf( "FatlaError: %s\n", message );
}

int
IsFull( PriorityQueue H )
{
	return H->Capacity == H->Size;
}

int
IsEmpty( PriorityQueue H )
{
	return H->Size == 0;
}

PriorityQueue
HeapInitialize( int MaxElements, ElementType Original )
{
	PriorityQueue H;

	H = malloc( sizeof( struct HeapStruct ) );
	if ( H == NULL )
		FatalError( "Out of space!!!" );

	H->Elements = malloc( ( MaxElements + 1 )
						    * sizeof( ElementType ) );
	
	if ( H->Elements == NULL )
		FatalError( "Out of space!!!" );

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[ 0 ] = Original;

	return H;
}

void 
HeapInsert( ElementType X, PriorityQueue H )
{
	int i;

	if ( IsFull( H ) )
	{
		Error( "Priority queue is full" );
		return;
	}
	
	for ( i = ++H->Size; ( H->Elements[ i / 2 ] )->Exponent
			< X->Exponent; i /= 2 )
				H->Elements[ i ] = H->Elements[ i / 2 ];
	H->Elements[ i ] = X;
}

ElementType
HeapDeleteMax( PriorityQueue H )
{
	int i, Child;
	ElementType MaxElement, LastElement;

	if ( IsEmpty( H ) )
	{
		Error( "Priority queue is empty" );
		return H->Elements[ 0 ];
	}
	MaxElement = H->Elements[ 1 ];
	LastElement = H->Elements[ H->Size-- ];
	//printf( "++%d++ ", LastElement->Exponent );

	for ( i = 1; i * 2 <= H->Size; i = Child )
	{
		Child = i * 2;
		if ( Child != H->Size && ( H->Elements[ Child + 1 ]->Exponent
							   > H->Elements[ Child ]->Exponent ) )
			Child++;
		
		if ( LastElement->Exponent < ( H->Elements[ Child ] )->Exponent )
			H->Elements[ i ] = H->Elements[ Child ];
		else
			break;
	}
	H->Elements[ i ] = LastElement;

	return MaxElement;
}

void
DeleteHeap( PriorityQueue H )
{
	free( H->Elements );
	H->Elements = NULL;
	free( H );
	H = NULL;
}

