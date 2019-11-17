#include "List.h"

struct Node
{
	ElementType Element;
	Position	Precede;
	Position	Succeed;
};

void 
FatalError( char message[] )
{
	printf( "%s\n", message );
}

void
PrintElement( void *P )
{
	printf( "%d ", ( ( Position )P )->Element );
}
