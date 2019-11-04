#include "List.h"

struct Node
{
	ElementType Element;
	Position	Next;
};

void 
FatalError( char message[] )
{
	printf("%s\n", message);
}

void
PrintElement( void *P )
{
	printf("%d ", ((Position)P)->Element);
}
