#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

void
Error( char Message[] )
{
	fprintf( stderr, "Error: %s\n", Message );
	exit( 0 );
}

void
FatalError( char Message[] )
{
	fprintf( stderr, "FatalError: %s\n", Message );
	exit( 0 );
}
