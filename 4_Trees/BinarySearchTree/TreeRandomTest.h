#ifndef _TreeRandomTest_H
#include "Random.h"
#include "Tree.h"
#define _TreeRandomTest_H


SearchTree RandomInserts( int n, int X, int Y, int a[], SearchTree T );
SearchTree RandomDeletes( int n, int X, int Y, int a[], SearchTree T,
		SearchTree ( * Delete )( ElementType, SearchTree ) );


#endif
