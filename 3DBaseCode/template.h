
//		Template

#ifndef TEMPLATE_LIB
#define TEMPLATE_LIB


#define NULL				0

//typedef unsigned char		BYTE;
//typedef unsigned short		WORD;
//typedef unsigned int		DWORD;

//-----------------------------------------------------------------------------

template< class T, int nSize = 0 >
class STACK{										//Stack

private:
	T					* pStack;					//Data Pointer Array
	int					nPoint;						//Stack pointer
	int					nCount;						//Stack space

protected:
	void Init( int nC )
		{
			if( nC && ( pStack = new T[ nC ] ) != NULL )
				SetMaxCount( nC );
			else
				SetMaxCount( 0 );
		}
	void Release( void )
		{ if( GetMaxCount() ) delete []pStack, SetMaxCount( 0 ), Clear(); };
	void SetMaxCount( int nC )
		{ nCount = nC; };

public:
	STACK( void ) : nPoint( 0 ), nCount( 0 ) { Init( nSize ); };
	~STACK( void ){ Release(); };

	bool IsEmpty( void )							//Stack empty?
		{ return ( GetCount() <= 0 ); };
	bool IsFull( void )								//Stack full?
		{ return ( GetCount() >= GetMaxCount() ); };
	int GetCount( void )							//Return the number of stack data
		{ return nPoint; };
	void Push( T t )								//Into the stack
		{ if( !IsFull() ) pStack[ nPoint++ ] = t; }
	T Pop( void )									//A stack
		{ return ( ( !IsEmpty() )? pStack[ --nPoint ] : NULL ); }
	void UnsafePush( T t )							//Into the stack (non-safety check)
		{ pStack[ nPoint++ ] = t; };
	T UnsafePop( void )								//A stack (non-safety check)
		{ return pStack[ --nPoint ]; };
	void Clear( void )								//Empty stack
		{ nPoint = 0; };
	void Resize( int nC )							//Reset stack size
		{ Release(); Init( nC ); };
	int GetMaxCount( void )							//Stack size has been
		{ return nCount; };
};

//-----------------------------------------------------------------------------

template< class T, int nSize = 0 >
class FILOMEMORY{									//FILO (stack) memory allocation / release

private:
	T				* pMemory;						//Memory heap
	int				nCount;							//Amount
	int				nPoint;							//Have been allocated the number of

protected:
	void Init( int nC )
		{
			if( nC && ( pMemory = new T[ nC ] ) != NULL )
				SetMaxCount( nC );
			else SetMaxCount( 0 );
		}
	void Release( void )
		{ if( GetMaxCount() ) delete []pMemory, SetMaxCount( 0 ), Clear(); };
	void SetMaxCount( int nC )
		{ nCount = nC; };

public:
	FILOMEMORY( void ) : nPoint( 0 ), nCount( 0 ) { Init( nSize ); };
	~FILOMEMORY( void ){ Release(); };

	bool IsFull( void )								//Full?
		{ return ( GetCount() >= GetMaxCount() ); }
	int GetCount( void )							//Return the number of heap data
		{ return nPoint; }
	T * GetOne( void )								//Distribution of a
		{ return ( IsFull() )? NULL : &pMemory[ nPoint++ ]; };
	T * CGetOne( void )								//Distribution of a (Clear)
		{
			T			* pTemp;

			if( ( pTemp = GetOne() ) == NULL ) return NULL;
			memset( pTemp, 0, sizeof( T ) );
			return pTemp;
		}
	T * UnsafeGetOne( void )						//Distribution of a (non-safety check)
		{ return &pMemory[ nPoint++ ]; };
	T * CUnsafeGetOne( void )						//Distribution of a (non-safety inspections, Clear)
		{
			T			* pTemp;

			if( ( pTemp = UnsafeGetOne() ) == NULL ) return NULL;
			memset( pTemp, 0, sizeof( T ) );
			return pTemp;
		}
	void Clear( void )								//Empty reactor
		{ nPoint = 0; };
	void Free( T * pT )								//Release
		{ if( nPoint && pT == ( pMemory + nPoint - 1 ) ) nPoint--; };
	void Resize( int nC )							//Heap size reset
		{ Release(); Init( nC ); };
	int GetMaxCount( void )
		{ return nCount; };
};

//-----------------------------------------------------------------------------

template< class T, int nSize = 0 >
class FIXMEMORY{									//Heap array

private:
	T				* pMemory;						//Memory heap
	char			* pUse;							//The use of tags
	int				nCount;							//Amount
	int				nPoint;							//The current array of numbers

protected:
	void Init( int nC )
		{
			if( nC && ( pMemory = new T[ nC ] ) != NULL ) )
				if( ( pUse = new char[ nC ] ) != NULL ){
					SetMaxCount( nC );
					Clear();
				}
				else{
					delete []pMemory;
					SetMaxCount( 0 );
				}
			else
				SetMaxCount( 0 );
		}
	void Release( void )
		{
			if( GetMaxCount() )
				delete []pUse, delete []pMemory, SetMaxCount( 0 ), SetPoint( 0 );
		}
	void SetMaxCount( int nC )
		{ nCount = nC; };
	void SetPoint( int nC )
		{ nPoint = nC; }
	int GetPoint( void )
		{ return nPoint; }

public:
	FIXMEMORY( void ) : nCount( 0 ), nPoint( 0 ) { Init( nSize ); };
	~FIXMEMORY( void ){ Release(); };

	bool IsFull( void )								//Full?
		{
			for( int i = 0; i < GetMaxCount(); i++ )
				if( !pUse[ i ] )
					return false;
			return true;
		}
	int GetCount( void )							//Return the number of heap data
		{
			int i, j;

			for( i = j = 0; i < GetMaxCount(); i++ )
				if( pUse[ i ] ) j++;
			return j;
		}
	T * GetOne( void )								//Distribution of a
		{
			int i;

			for( i = GetPoint(); i < GetMaxCount(); i++ )
				if( !pUse[ i ] ){
					pUse[ i ] = 1;
					SetPoint( i++ );
					return ( t + i );
				}
			for( i = 0; i < GetPoint(); i++ )
				if( !pUse[ i ] ){
					pUse[ i ] = 1;
					SetPoint( i++ );
					return ( t + i );
				}
			return NULL;
		}
	T * CGetOne( void )								//Distribution of a (Clear)
		{	T			* pTemp;
			if( ( pTemp = GetOne() ) == NULL ) return NULL;
			memset( pTemp, 0, sizeof( T ) );
			return pTemp;
		};
	void Clear( void )								//Empty reactor
		{ memset( pUse, 0, GetMaxCount() ), SetPoint( 0 ); };
	void Free( T * )								//Release
		{
			int i;

			for( i = GetPoint() - 1; i >= 0; i-- )
				if( pUse[ i ] && ( pMemory + i ) == pT ){
					pUse[ i ] = 0;
					SetPoint( i );
					return;
				}
			for( i = GetMaxCount() - 1; i >= GetPoint(); i-- )
				if( pUse[ i ] && ( pMemory + i ) == pT ){
					pUse[ i ] = 0;
					SetPoint( i );
					return;
				}
			return;
		}
	void Resize( int nC )							//Heap size reset
		{ Release(); Init( nC ); };
	int GetMaxCount( void )
		{ return nCount; };
};

//-----------------------------------------------------------------------------

template< class T >
class CHAIN_S;

template< class T >
class CHAINNODE_S : public T{						//Structure point of

	friend CHAIN_S< T >;

private:
	CHAINNODE_S< T >	* pNext;

public:
	CHAINNODE_S( void ) : pNext( NULL ) {};
};

template< class T >
class CHAIN_S{										//Structure List

private:
	CHAINNODE_S< T >	* pFirst;

public:
	CHAIN_S( void ) : pFirst( NULL ) {};
	~CHAIN_S( void ){ Reset(); };

	void Reset( void )								//Clear List
		{
			CHAINNODE_S< T >	* pTemp;

			while( pFirst ){
				pTemp = pFirst->pNext;
				pFirst->pNext = NULL;
				pFirst = pTemp;
			}
		}
	bool InstertF( CHAINNODE_S< T > * pNode )		//Insert node (Tau)
		{
			if( pNode->pNext != NULL ) return false;
			if( pFirst == NULL ){
				pFirst = pNode;
				return true;
			}
			pNode->pNext = pFirst;
			pFirst = pNode;
			return true;
		};
	bool Delete( CHAINNODE_S< T > * pNode )			//Delete the specified node
		{
			CHAINNODE_S< T >		* pTemp = pFirst, * pT1 = NULL;

			if( pTemp == NULL ) return false;
			while( pTemp != pNode ){
				pT1 = pTemp;
				if( ( pTemp = pTemp->pNext ) == NULL )
					return false;
			}
			if( pTemp == pFirst )
				pFirst = pFirst->pNext;
			else
				pT1->pNext = pTemp->pNext;
			pNode->pNext = NULL;
			return true;
		};
	int GetAllNode( CHAINNODE_S< T > * pNode[], int nCount )	//By all nodes and the number of indicators
		{
			int					i;
			CHAINNODE< T >		* pTemp = pFirst;

			for( i = 0; pTemp != NULL && i < nCount; pTemp = pTemp->pNext )
				pNode[ i++ ] = pTemp;
			return i;
		};
	int GetCount( void )							//List the number of access nodes
		{
			int					i;
			CHAINNODE_S< T >	* pTemp = pFirst;

			for( i = 0; pTemp != NULL; i++, pTemp = pTemp->pNext );
			return i;
		};
};

//-----------------------------------------------------------------------------

template< class T >
class CHAIN;

template< class T >
class CHAINNODE{

	friend CHAIN< T >;

private:
	T			* pNode;
	CHAINNODE	* pNext;
};

template< class T >
class CHAIN{

private:
	CHAINNODE< T >	* pFirst;

public:
	CHAIN( void ) : pFirst( NULL ) {};

	void Reset( void )								//Clear List
		{
			CHAINNODE< T > * pT1 = pFirst, * pT2;
			while( pT1 ){ pT2 = pT1->pNext; delete pT1; pT1 = pT2; };
			pFirst = NULL;
		};
	bool InstertF( T * pNode )						//Insert node (Tau)
		{
			if( pFirst == NULL ){
				if( ( pFirst = new CHAINNODE< T > ) == NULL )
					return false;
				pFirst->pNext = NULL;
				pFirst->pNode = pNode;
				return true;
			}
			CHAINNODE< T > pTemp;
			if( ( pTemp = new CHAINNODE< T > ) == NULL )
				return false;
			pTemp->pNext = pFirst;
			pTemp->pNode = pNode;
			pFirst = pTemp;
			return true;
		};
	bool Delete( T * pNode )						//Delete the specified node
		{
			CHAINNODE< T >		* pTemp = pFirst, * pT1 = NULL;

			if( pTemp == NULL ) return false;
			while( pTemp->pNode != pNode ){
				pT1 = pTemp;
				if( ( pTemp = pTemp->pNext ) == NULL )
					return false;
			}
			if( pTemp == pFirst ){
				pTemp = pTemp->pNext; delete pFirst; pFirst = pTemp;
			}
			else{
				pT1->pNext = pTemp->pNext; delete pTemp;
			}
			return true;
		};
	int GetAllNode( T pNode[], int nCount )			//By all nodes and the number of indicators
		{
			int					i;
			CHAINNODE< T >		* pTemp = pFirst;

			for( i = 0; pTemp != NULL && i < nCount; pTemp = pTemp->pNext )
				pNode[ i++ ] = pTemp->pNode;
			return i;
		};
	int GetCount( void )							//List the number of access nodes
		{
			int					i;
			CHAINNODE< T >		* pTemp = pFirst;

			for( i = 0; pTemp != NULL; i++, pTemp = pTemp->pNext );
			return i;
		};
};

//-----------------------------------------------------------------------------

#endif