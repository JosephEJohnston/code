#ifndef _Cursor_H
#include <stdio.h>
#define _Cursor_H
#define SpaceSize	100

typedef int ElementType;

typedef int Position;
typedef int SearchTree;

void FatalError( char message[] );
void Error( char message[] );

void InitializeCursorSpace( void );

/*
SearchTree MakeEmpty( SearchTree T );
*/

Position Find( ElementType X, SearchTree T );

Position FindMin( SearchTree T );
//Position FindMax( SearchTree T );

SearchTree Insert( ElementType X, SearchTree T );
SearchTree Delete( ElementType X, SearchTree T );
ElementType Retrieve( Position P );

void PrePrintTree( SearchTree T );

#endif /* _Cursor_H */



