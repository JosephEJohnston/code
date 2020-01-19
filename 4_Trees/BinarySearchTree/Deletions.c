struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

static int count = 0;

SearchTree
FirstDelete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if ( T == NULL )
		Error( "Element not found" );
	else
	if ( X < T->Element )
		T->Left = FirstDelete( X, T->Left );
	else
	if ( X > T->Element )
		T->Right = FirstDelete( X, T->Right );
	else
	if ( T->Left && T->Right )
	{
		TmpCell = FindMin( T->Right );
		T->Element = TmpCell->Element;
		T->Right = FirstDelete( T->Element, T->Right );
	}
	else
	{
		TmpCell = T;
		if ( T->Left == NULL )
			T = T->Right;
		else
		if ( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	return T;
}

SearchTree
SecondDelete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if ( T == NULL )
		Error( "Element not found" );
	else
	if ( X < T->Element )
		T->Left = SecondDelete( X, T->Left );
	else
	if ( X > T->Element )
		T->Right = SecondDelete( X, T->Right );
	else
	if ( T->Left && T->Right )
	{
		int r = rand();

		 if ( r % 2 == 1 )  
		 {
			TmpCell = FindMax( T->Left );
			T->Element = TmpCell->Element;
			T->Left = SecondDelete( T->Element, T->Left );
		 }
		 else
		 {
			TmpCell = FindMin( T->Right );
			T->Element = TmpCell->Element;
			T->Right = SecondDelete( T->Element, T->Right );
		 }

	}
	else
	{
		TmpCell = T;
		if ( T->Left == NULL )
			T = T->Right;
		else
		if ( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	return T;
}


SearchTree
ThirdDelete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if ( T == NULL )
		Error( "Element not found" );
	else
	if ( X < T->Element )
		T->Left = ThirdDelete( X, T->Left );
	else
	if ( X > T->Element )
		T->Right = ThirdDelete( X, T->Right );
	else
	if ( T->Left && T->Right )
	{
		 if ( count++ % 2 == 1 )  
		 {
			TmpCell = FindMax( T->Left );
			T->Element = TmpCell->Element;
			T->Left = SecondDelete( T->Element, T->Left );
		 }
		 else
		 {
			TmpCell = FindMin( T->Right );
			T->Element = TmpCell->Element;
			T->Right = SecondDelete( T->Element, T->Right );
		 }

	}
	else
	{
		TmpCell = T;
		if ( T->Left == NULL )
			T = T->Right;
		else
		if ( T->Right == NULL )
			T = T->Left;
		free( TmpCell );
	}

	return T;
}

