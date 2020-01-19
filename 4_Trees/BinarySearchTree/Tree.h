#ifndef _Tree_H
#define _Tree_H
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

void FatalError( char message[] );
void Error( char message[] );

SearchTree MakeEmpty( SearchTree T );
Position Find( ElementType X, SearchTree T );
Position FindMin( SearchTree T );
Position FindMax( SearchTree T );
SearchTree Insert( ElementType X, SearchTree T );
SearchTree Delete( ElementType X, SearchTree T );
ElementType Retrieve( Position P );

void PrePrintTree( SearchTree T );

#endif 


