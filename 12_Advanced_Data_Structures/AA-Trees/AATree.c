/* Returned for failures */
Position NullNode = NULL; /* Needs more initialization */

struct AANode
{
	ElementType	Element;
	AATree		Left;
	AATree		Right;
	int			Level;
};

AATree
Initialize( void )
{
	if ( NullNode == NULL )
	{
		NullNode = malloc( sizeof( struct AANode ) );
		if ( NullNode == NULL )
			FatalError( "Out of space!!!" );
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Level = 0;
	}
	return NullNode;
}

/* If T's left child is on the same level as T, */
/* perform a rotation */


AATree
Skew( AATree T )
{
	if ( T->Left->Level == T->Level )
		T = SingleRotateWithLeft( T );
	return T;
}

/* If T's rightmost grandchild is on the same level, */
/* rotate right child up */

AATree
Split( AATree T )
{
	if ( T->Right->Right->Level == T->Level )
	{
		T = SingleRotateWithRight( T );
		T->Level++;
	}
	return T;
}

AATree
Insert( ElementType Item, AATree T )
{
	if ( T == NullNode )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct AANode ) );
		if ( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = Item; T->Level = 1;
			T->Left = T->Right = NullNode;
		}
		return T;
	}
	else
	if ( Item < T->Element )
		T->Left = Insert( Item, T->Left );
	else
	if ( Item > T->Element )
		T->Right = Insert( Item, T->Right );

	/* Otherwise it's a duplicate; do nothing */

	T = Skew( T );
	T = Split( T );
	return T;
}

AATree
Remove( ElementType Item, AATree T )
{
	static Position DeletePtr, LastPtr;

	if ( T != NullNode )
	{
		/* Step 1: Search down tree */
		/*		   set LastPtr and DeletePtr */
		LastPtr = T;
		if ( Item < T->Element )
			T->Left = Remove( Item, T->Left );
		else
		{
			DeletePtr = T;
			T->Right = Remove( Item, T->Right );
		}

		/* Step 2: If at the bottom of the tree and */
		/*		   item is present, we remove it */
		if ( T == LastPtr )
		{
			if ( DeletePtr != NullNode &&
					Item == DeletePtr->Element )
			{
				DeletePtr->Element = T->Element;
				DeletePtr = NullNode;
				T = T->Right;
				free( LastPtr );

			}
		}
		else
		if ( T->Left->Level < T->Level - 1 ||
			 T->Right->Level < T->Level - 1 )
		{
			if ( T->Right->Level > --T->Level )
				T->Right->Level = T->Level;
			T = Skew( T );
			T->Right = Skew( T->Right );
			T->Right->Right = Skew( T->Right->Right );
			T = Split( T );
			T->Right = Split( T->Right );
		}
	}
	return T;
}
