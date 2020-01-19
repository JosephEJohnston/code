
Treap
Initialize( void )
{
	if ( NullNode == NULL )
	{
		NullNode = malloc( sizeof( struct TreapNode ) );
		if ( NullNode == NULL )
			FatalError( "Out of space!!!" );
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Priority = Infinity;
	}
	return NullNode;
}

Treap
Insert( ElementType Item, Treap T )
{
	if ( T == NullNode )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct TreapNode ) );
		if ( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = Item; T->Priority = Random( );
			T->Left = T->Right = NullNode;
		}
	}
	else
	if ( Item < T->Element )
	{
		T->Left = Insert( Item, T->Left );
		if ( T->Left->Priority < T->Priority )
			T = SingleRotateWithLeft( T );
	}
	else
	if ( Item > T->Element )
	{
		T->Right = Insert( Item, T->Right );
		if ( T->Right->Priority < T->Priority )
			T = SingleRotateWithRight( T );
	}

	/* Otherwise it's a duplicate; do nothing */
	return T;
}

Treap
Remove( ElementType Item, Treap T )
{
	if ( T != NullNode )
	{
		if ( Item < T->Element )
			T->Left = Remove( Item, T->Left );
		else
		if ( Item > T->Element )
			T->Right = Remove( Item, T->Right );
		else
		{
			/* Match found */
			if ( T->Left->Priority < T->Right->Priority )
				T = SingleRotateWithLeft( T );
			else
				T = SingleRotateWithRight( T );

			if ( T != NullNode )	/* Continue on down */
				T = Remove( Item, T );
			else
			{
				/* At a leaf */
				free( T->Left );
				T->Left = NullNode;
			}
		}
	}

	return T;
}
