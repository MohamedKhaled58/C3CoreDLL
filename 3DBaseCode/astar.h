#ifndef PROGRAM_ASTAR
#define PROGRAM_ASTAR


#include "template.h"


//-----------------------------------------------------------------------------

const int MAXSEARCHSTEP		= 400;				//Step up to the number of routing

enum BODYSIZE{
	BODILY0					= 0,					//Does not account for lattice
	BODILY1					= 1,					//Accounted for a lattice
	BODILY4					= 4,					//Accounted for four lattice
};

class STEPDATA{										//Road data

private:
	int					nStepCount;							//Record step
	char				cStepWay[ MAXSEARCHSTEP * 2 + 3 ];	//The direction of the array
	BODYSIZE			eBodySize;							//Size

public:
	STEPDATA( void ) : nStepCount( 0 ) {};
	STEPDATA( BODYSIZE bs ) : nStepCount( 0 ), eBodySize( bs ) {};

	int RemainSteps( void )							//The remaining steps
		{ return nStepCount; }
	void ClearStep( void )							//Clear
		{ nStepCount = 0; }
	void AddStep( int nC )							//Additional steps
		{ nStepCount += nC; };
	void SetStep( int nC )							//Set step
		{ nStepCount = nC; };
	char GetNextStep( void )						//Take the next step
		{ return cStepWay[ --nStepCount ]; }
	char * GetStepArray( void )						//Get step-by-step buffer
		{ return cStepWay; }
	char * GetStepArrayTail( void )					//Get step-by-step at the end of the address buffer
		{ return cStepWay + nStepCount; }
	void SetBodySize( BODYSIZE eSize )				//Set size size
		{ eBodySize = eSize; }
	BODYSIZE GetBodySize( void )					//Body size has been
		{ return eBodySize; }
};

//-----------------------------------------------------------------------------

#define ASTAR_UNSTAY		( ASTAR_NODE * )0xffffffffL	//Can not stay
#define ASTAR_INSTAY		( ASTAR_NODE * )NULL		//Can stay

const int ASTACKBUFFSIZE	= MAXSEARCHSTEP * 8 * 8 + 10;	//A * Stack number
const int ASTARBUFFSIZE		= MAXSEARCHSTEP * 8 + 10;		//A * number of node buffer
const unsigned int ASTAR_HASMAN		= 0x00000001L;			//People to stay marked

const char INSTAY			= 0;				//Can stay
const char UNSTAY			= 1;				//Can not stay

const char INOPEN			= 1;					//In the OPEN list
const char INCLOSE			= 2;					//List of the CLOSE
const char OTHERWISE		= 0;					//Not in the list

struct ASTAR_NODE{
	int				nG, nH, nF;					//Valuation Value
	int				nX, nY;						//Coordinates
	int				nNumber;					//Array code
	ASTAR_NODE		* pParent;					//Parent node pointer
	ASTAR_NODE		* pChild[8];				//Sub-node pointer
	ASTAR_NODE		* pNextNode;				//Pointer list
	char			cWhere, cDirect;			//Location, direction
};

class ASTAR_8WAY{

private:
	class ASTAR_IDX{
	private:
		ASTAR_NODE			* pAN;					//Node pointer
		unsigned int		unCount;				//Counters, markers
	public:

		void SetUnstay( void )						//Settings can not go
			{ pAN = ASTAR_UNSTAY; };
		void SetStay( void )						//Set to go
			{ pAN = ASTAR_INSTAY; };
		void SetStay( char cS )						//Set to go
			{ pAN = ( cS == UNSTAY )? ASTAR_UNSTAY : ASTAR_INSTAY; };
		void SetHasman( void )						//Set was
			{ unCount |= ASTAR_HASMAN; };
		void SetNoman( void )						//No one set
			{ unCount = unCount & ( ~ASTAR_HASMAN ); };
		void SetCount( unsigned int unC )			//Set up counter
			{ unCount = ( unCount & 0xf ) | unC; };
		bool IsAvail( unsigned int unC )			//Counter effective?
			{ return ( unCount >= unC ); };
		bool IsUnstay( void )						//Test can not stay, do not consider the people?
			{ return ( pAN == ASTAR_UNSTAY ); };
		bool IsUnstayCM( void )						//Test can not stop to consider who?
			{ return ( ( pAN == ASTAR_UNSTAY ) || ( unCount & ASTAR_HASMAN ) ); };
		void SetNode( ASTAR_NODE * pN )				//Set node pointer
			{ pAN = pN; };
		ASTAR_NODE * GetNode( void )				//Node pointer to be
			{ return pAN; };
		char GetStay( void )						//Remain to be marked
			{ return ( pAN == ASTAR_UNSTAY ); };
	};

	class CHAINASN_C{								//CLOSE list
	protected:
		ASTAR_NODE			* pNode;

	public:
		CHAINASN_C( void ) : pNode( NULL ) {};

		bool IsEmpty( void )						//Check for empty
			{ return ( pNode == NULL ); };
		ASTAR_NODE * Get( void )					//Out
			{
				if( pNode == NULL ) return NULL;
				ASTAR_NODE * pTemp = pNode;
				pNode = pNode->pNextNode;
				return pTemp;
			}
		void Insert( ASTAR_NODE * pN )				//Insert
			{ pN->pNextNode = pNode; pNode = pN; pNode->cWhere = INCLOSE; };
		void Clear( void )							//Clear
			{ pNode = NULL; };
	};

	class CHAINASN_O : public CHAINASN_C{			//OPEN List
	public:
		void Insert( ASTAR_NODE * );				//Insert
	};


	int						nMapWidth;				//Map width
	int						nMapHeight;				//Map high -
	ASTAR_IDX *				pAStarIdx;				//Map the size of walk marked
	unsigned int			unPathCount;			//Counter Wayfinding

	int						MAN_BODILY_OFFSET[ BODILY4 ];		//
	int						MAN_BODILY_AROUND[ 8 ];				//Around the center point of the relative offset
	int						LINEOFF[ 8 ];						//

	STACK< ASTAR_NODE *, ASTACKBUFFSIZE >		AstarStack;		//A * stack
	FILOMEMORY< ASTAR_NODE, ASTARBUFFSIZE >		AstarNode;		//A * heap node

	CHAINASN_O				OpenChain;			//OPEN List
	CHAINASN_C				CloseChain;			//CLOSE list

	int					nEndX, nEndY;			//End coordinates
	ASTAR_IDX			* pEndASI;				//Destination address
	STEPDATA			* pStepPtr;				//Were described walking pointer
	BODYSIZE			BSize;					//Running object type

protected:
	ASTAR_NODE * ReturnBestNode( void );				//To be the next node
	int GenerateSuccessorsNoMan( ASTAR_NODE * );		//Were not obstacles
	int GenerateSuccessorsHasMan( ASTAR_NODE * );		//Were considered obstacles to
	void FreeNodes( void );									//Routing node clearance
	void PropagateDown( ASTAR_NODE * );

	inline void ClearAstarIdx( void );
	int CheckContinue( int, int, int &, int & );		//
	int CheckFront( int, int, int, int, int );			//
	char CalculateWay( ASTAR_NODE *, ASTAR_NODE * );
	char CalculateMirrWay( ASTAR_NODE *, ASTAR_NODE * );
	int Calculate( int nSX, int nSY, int nTX, int nTY )		//Estimated function
		{ return ( ( nTX - nSX ) * ( nTX - nSX ) + ( nTY - nSY ) * ( nTY - nSY ) ) << 2; }

	bool TestStayHasMan( ASTAR_IDX *, BODYSIZE );			//Test stop taking people
	bool TestStayNoMan( ASTAR_IDX *, BODYSIZE );			//Testing to stay, regardless of who

public:
	ASTAR_8WAY( void );
	~ASTAR_8WAY( void ){ Release(); }

	int InitAStar( int, int );								//Initialization map size
	void SetSafelyZone( void );								//Set of seat belts
	void Release( void );									//Release

	void SetAStarAtr( int nX, int nY, char cArt )			//Attribute set to walk
		{ SetAStarAtr( nMapWidth * nY + nX, cArt ); }
	void SetAStarAtr( int nCount, char cArt )				//Attribute set to walk
		{ pAStarIdx[ nCount ].SetStay( cArt ); };
	char GetAStarAtr( int nX, int nY )						//Check stop marking
		{ return GetAStarAtr( nMapWidth * nY + nX ); }
	char GetAStarAtr( int nC )								//Check stop marking
		{ return pAStarIdx[ nC ].GetStay(); };
	void SetManInAStarAtr( int nX, int nY, BODYSIZE cType )	//Set up the occupation of
		{ SetManInAStarAtr( nMapWidth * nY + nX, cType ); }
	void SetManInAStarAtr( int, BODYSIZE );					//Set up the occupation of
	void ClrManInAStarAtr( int nX, int nY, BODYSIZE cType )	//Removal of the occupation
		{ ClrManInAStarAtr( nMapWidth * nY + nX, cType ); }
	void ClrManInAStarAtr( int, BODYSIZE );					//Removal of the occupation

	int FindPath( int, int, int, int, STEPDATA *, int );	//Wayfinding
};


//-------------------------Parameters------------------------------------------------

const int NO_MAN			= 0;				//People do not consider
const int HAS_MAN			= 1;				//Consider people

const int E_TO_S			= 0;				//Reverse Search
const int S_TO_E			= 0x10;				//Forward Search

const int NOCHECKFRONT		= 0x1000;			//Starting point does not check
const int CONTINUESEARCH	= 0x2000;			//The current path of local search

//-----------------------Return value------------------------------------------------

const int NOFOUND			= 1;				//Not find the target
const int NOPATH			= 2;				//No way
const int HAVEPATH			= 4;				//Find
const int ATTARGET			= 8;				//Standing goal

const int TARGETHASMAN		= 0x10;				//Others target points
const int TARGETNOPATH		= 0x20;				//Target points can not stop (for example, by other building coverage)
const int TARGETCLOSE		= 0x40;				//Target closed
const int SOURCECLOSE		= 0x80;				//Closed source
const int UNWALKABLE		= TARGETHASMAN | TARGETNOPATH | TARGETCLOSE | SOURCECLOSE;

const int NOENOUGHSTEP		= 0x200;			//The remaining step is not enough local search can not be

const int RECORDPATH		= 0x1000;			//Record of the path
//        CONTINUESEARCH	0x2000				//The current path of local search
const int SHARELAST			= 0x4000;			//The use of the path before
const int MAXSTEP			= 0x8000;			//The largest search

#endif
