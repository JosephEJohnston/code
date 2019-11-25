#ifndef _BinaryHeap_H

struct HeapStruct;
typedef struct HeapStruct	*PriorityQueue;
typedef PtrToNode			ElementType;


int IsFull( PriorityQueue H );
int IsEmpty( PriorityQueue H );
PriorityQueue HeapInitialize( int MaxElements, ElementType Original ); 
void HeapInsert( ElementType X, PriorityQueue H );
ElementType HeapDeleteMax( PriorityQueue H );
void DeleteHeap( PriorityQueue H );

#endif

/*
struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};
*/
