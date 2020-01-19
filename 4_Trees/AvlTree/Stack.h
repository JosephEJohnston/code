#ifndef _Stack_H
#define _Stack_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef Position StackElementType;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void StackMakeEmpty( Stack S );
void Push( StackElementType X, Stack S );
StackElementType Top( Stack S );
void Pop( Stack S );

#endif
