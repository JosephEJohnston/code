#ifndef _List_H
#include <stdio.h>
#include <stdlib.h>
#include "DecInt.h"

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( ElementType X, List L );
void Delete( ElementType X, List L );
Position FindPrevious( ElementType X, List L );
void Insert( ElementType X, List L, Position P );
void DeleteList( List L );
Position Header( List L );
Position First( List L );
Position Advance( Position P );
ElementType Retrieve( Position P );

void InsertList( ElementType X[], int n, List L );
void PrintList( List L );

void SwapPrecede( ElementType X, List L );
void SwapSucceed( ElementType X, List L );

#endif

