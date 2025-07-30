#ifndef _BASEFUNC_H
#define _BASEFUNC_H
//---------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include <windows.H>

#include "mouse.H"

#ifdef _ANALYSIS_ON
	extern DWORD g_dwIniGetAmount;
	extern DWORD g_dwIniSearchLineAmount;
	extern DWORD g_dwIniGetAmountFrame;
	extern DWORD g_dwIniSearchLineAmountFrame;
#endif

//#define _NOTUSETRY
#pragma warning(disable: 4786)
extern int _SCR_WIDTH, _SCR_HEIGHT;


const DWORD _SHOWWAY_NORMAL		 =0;
const DWORD _SHOWWAY_ADDITIVE	 =1;

const DWORD _LOADWAY_NORMAL	 =0;
const DWORD _LOADWAY_MASK	 =0xff000000;
const DWORD _LOADWAY_TRANS   =0xffff00ff;

enum {CRITICAL_FALSE=false, CRITICAL_TRUE=true};
//----------------------------------------------------------
int		Double2Int	(double dValue);

BOOL	IniStrGet	(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, char *pszStr, BOOL bCritical=false);
BOOL	IniDataGet	(const char *pszFileName, const char *pszTitle, const char *pszSubTitle, int &iData, BOOL bCritical=false);

BOOL	TxtStrGet	(const char *pszFileName, const char *pszTitle, char *pszStr, BOOL bCritical=false);
BOOL	TxtDataGet	(const char *pszFileName, const char *pszTitle, int &iData, BOOL bCritical=false);

DWORD	TimeGet		(void);
DWORD	SysTimeGet  (void);
int		RandGet		(int nMax, BOOL bRealRand=false);

void	ErrorMsg	(const char* fmt, ...);
void	ErrorOut	(const char* fmt, ...);
void	LogMsg		(const char* fmt, ...);
void	DebugMsg	(const char* fmt, ...);
BOOL	StringCheck	(char* pszString);

void	MouseInit		(void);
void	MouseSet		(int x, int y, int event);
void	MouseProcess	(void);
int		MouseCheck		(int& iMouseX, int& iMouseY);

void	KeyClearBuffer	(void);
int		KeyAppend		(void);
int		KeyGet			(void);
bool	KeyUnGet		(void);

void	RepairString	(char* pszString);
void	ReplaceString	(char* pszString, char cFind, char cReplace);
DWORD	GetDate			();
BOOL	IsDBCSLeadByte	(const char* pszString, int idx);


//----------------------------------------------------------
typedef DWORD OBJID;

typedef struct 
{
	int	x, y;
}CMyPos;

typedef struct
{
	int t, l, r, b;
}CMyRect;

typedef struct 
{
	float fHorizontal;
	float fVertical;
}CMy3DDir;

typedef struct 
{
	int	x, y, z;
}CMy3DPos;

typedef struct {
	float		fRadianX;			// The right axis direction, clockwise
	float		fRadianY;			// On-axis direction, clockwise
	float		fRadianZ;			// Axis in the direction, clockwise
}CMy3DPose;



typedef struct {
	int	iWidth, iHeight;
}CMySize;

//----------------------------------------------------------
const int _MAX_STRING		=256;
const int _MAX_NAMESIZE		=16;
const int _MAX_NAMESIZE_CLI	=32;
const int _MAX_TITLESIZE	=128;
const OBJID	ID_NONE	=0;


//----------------------------------------------------------
#ifndef SAFE_DELETE
	#ifdef _DEBUG
		#define SAFE_DELETE(p) { if(p) delete p; p=NULL; }
	#else
		#define SAFE_DELETE(p) { if(p){ try{ delete p; } catch(...){} p=NULL; }}
	#endif
#endif

//----------------------------------------------------------
#ifndef MYASSERT
	#ifdef _DEBUG
		#define	MYASSERT(x) assert(x)
	#else
		#define	MYASSERT(x)	{if(!(x)) LogMsg("¡ïASSERT(" #x ") in %d line of %s¡ï", __LINE__, __FILE__); }
	#endif
#endif

//----------------------------------------------------------
#ifndef IF_SUC
	#ifdef _DEBUG
		#define	IF_SUC(x)  if( ((x)) ? true : ( assert(!("IF_SUC: " #x)), false ) )
	#else
		#define	IF_SUC(x)  if( ((x)) ? true : ( LogMsg("¡ïIF_SUC(%s)¡ï failed in %s, %d", #x, __FILE__, __LINE__), false ) )
	#endif
#endif

#define IF_TRUE	IF_SUC
#define IF_YES	IF_SUC
#define IF_OK	IF_SUC

//----------------------------------------------------------
#ifndef IF_NOT
	#ifdef _DEBUG
		#define	IF_NOT(x)  if( (!(x)) ? ( assert(!("IF_NOT: " #x)),1 ) : 0 )
	#else
		#define	IF_NOT(x)  if( (!(x)) ? ( LogMsg("¡ïIF_NOT(%s)¡ï in %s, %d", #x, __FILE__, __LINE__),1 ) : 0 )
	#endif
#endif
//---------------------------------------------------------------------
inline unsigned int	ExchangeShortBits(unsigned long nData, int nBits)
{
	MYASSERT(nBits >= 0 && nBits < 16);
	nData	&= 0xFFFF;
	return ((nData>>nBits) | (nData<<(16-nBits))) & 0xFFFF;
}
inline unsigned int	ExchangeLongBits(unsigned long nData, int nBits)
{
	MYASSERT(nBits >= 0 && nBits < 32);
	return (nData>>nBits) | (nData<<(32-nBits));
}
//---------------------------------------------------------------------
// version define
const int _VERSION		=108;

// game status define
const unsigned int	_STATUS_NONE		=1000;
const unsigned int	_STATUS_ACCOUNT		=_STATUS_NONE+1;
const unsigned int	_STATUS_CONNECT		=_STATUS_NONE+2;
const unsigned int	_STATUS_LOGIN		=_STATUS_NONE+3;
const unsigned int	_STATUS_REGISTER	=_STATUS_NONE+4;
const unsigned int	_STATUS_MAINTAINROLE=_STATUS_NONE+5;

const unsigned int	_STATUS_WAITING		=_STATUS_NONE+8;
const unsigned int	_STATUS_FIGHTING	=_STATUS_NONE+9;
const unsigned int	_STATUS_NORMAL		=_STATUS_NONE+10;
const unsigned int	_STATUS_TASK		=_STATUS_NONE+11;
const unsigned int	_STATUS_GAMBLE		=_STATUS_NONE+12;

const unsigned int	_STATUS_EXIT		=_STATUS_NONE+100;
const unsigned int	_STATUS_DESTROY		=_STATUS_NONE+101;

//---------------------------------------------------------------------
// action define

const int _ACTION_DANCE1		=001;
const int _ACTION_DANCE2		=002;
const int _ACTION_DANCE3		=003;
const int _ACTION_DANCE4		=004;
const int _ACTION_DANCE5		=005;
const int _ACTION_DANCE6		=006;
const int _ACTION_DANCE7		=007;
const int _ACTION_DANCE8		=8;	

const int _ACTION_STANDBY		=100;
const int _ACTION_REST1			=101;
const int _ACTION_REST2			=102;
const int _ACTION_REST3			=103;
const int _ACTION_STANDBY_I		=105;

const int _ACTION_WALKL			=110;	
const int _ACTION_WALKR			=111;
const int _ACTION_WALKL_I		=115;
const int _ACTION_WALKR_I		=116;


const int _ACTION_RUNL			=120;
const int _ACTION_RUNR			=121;

const int _ACTION_TRANSFORM		=122;

const int _ACTION_RUNL_I		=125;
const int _ACTION_RUNR_I		=126;

const int _ACTION_JUMP	        =130;
const int _ACTION_JUMP_BACK	    =131;
const int _ACTION_JUMP_RUN	    =132;

const int _ACTION_JUMP_ATK		=140;
const int _ACTION_JUMP_ATKEND	=141;

const int _ACTION_LAUGH			=140;
const int _ACTION_GUFFAW		=151;
const int _ACTION_FURY          =160;
const int _ACTION_SAD	        =150;
const int _ACTION_EXCITEMENT	=180;
const int _ACTION_SAYHELLO		=190;
const int _ACTION_SALUTE		=160;
const int _ACTION_GENUFLECT     =170;
const int _ACTION_KNEEL			=220;
const int _ACTION_COOL			=230;
const int _ACTION_COOLPOSE		=231;
const int _ACTION_SWIM			=240;
const int _ACTION_SITDOWN       =250;
const int _ACTION_SITDOWN_STATIC=251;

const int _ACTION_ZAZEN			=260;
const int _ACTION_ZAZENCOOL		=261;
const int _ACTION_FAINT	        =190;
const int _ACTION_LIE	        =200;

const int _ACTION_PICKUP		=262;
const int _ACTION_MINE			=360;


const int _ACTION_ALERT			=340;
const int _ACTION_ALERT_I		=305;

const int _ACTION_DODGE0		=311;

const int _ACTION_BRUISE0		=321;
const int _ACTION_BRUISE1		=321;


const int _ACTION_DIE0			=330;
const int _ACTION_BODY0			=331;
const int _ACTION_DIE1			=332;
const int _ACTION_BODY1			=333;
const int _ACTION_DIE2			=334;
const int _ACTION_BODY2			=335;
const int _ACTION_DIE3			=336;
const int _ACTION_BODY3			=337;

const int _ACTION_DIEFLY		=340;
const int _ACTION_DIEFLYEND		=341;
const int _ACTION_WALKBACK      =342;

const int _ACTION_ATTACK0	    =350;
const int _ACTION_ATTACK1	    =351;
const int _ACTION_ATTACK2	    =352;

const int _ACTION_RELIVE		=400;

const int _ACTION_PUNCTURE	    =451;
const int _ACTION_AIRSTRIKE		=452;
const int _ACTION_TORNADO	    =453;

const int _ACTION_BODYSHIELD	=460;
const int _ACTION_GODBELIEVE	=465;
const int _ACTION_BUMP			=470;
const int _ACTION_POPOFF		=_ACTION_BRUISE0;

const int _ACTION_INTONE			=390;
const int _ACTION_INTONE_DURATION	=391;
const int _ACTION_INTONE_LAUNCH		=392;

const int _ACTION_FLY_STANDBY	=501;
const int _ACTION_FLY_ALERT		=502;
const int _ACTION_FLY_MOVE		=510;
const int _ACTION_FLY_ATTACK	=520;

const int _ACTION_FLY_DOWN		=530;
const int _ACTION_FLY_UP		=540;
const int _ACTION_FLY_DIE		=550;
const int _ACTION_FLY_WOUND		=560;
const int _ACTION_JUMPBACK_SHOOT=610;
const int _ACTION_FAST_SHOOT	=620;
const int _ACTION_CHARGEUP_BEGIN=630;
const int _ACTION_CHARGEUP_END	=631;

const int _ACTION_TM_FAST_SHOOT			=800;
const int _ACTION_TM_DISPERSION_SHOOT	=801;






//---------------------------------------------------------------------
// my win message define
#ifndef WM_MY_MESSAGE
#define WM_MY_MESSAGE (WM_USER+100)
	
	const int CMD_NORMAL			= 1000;
	const int CMD_OPENSHOP			= CMD_NORMAL + 1;	// Open shop
	const int CMD_CLOSESHOP			= CMD_NORMAL + 2;	// Closed shop

	const int CMD_FLASHITEM			= CMD_NORMAL + 3;	// Refresh column items
	const int CMD_FLASHMONEY		= CMD_NORMAL + 4;	// Refresh money 

	const int CMD_OPENTRADE			= CMD_NORMAL + 5;	// Open trading window
	const int CMD_TRADEOK			= CMD_NORMAL + 6;	// Transaction success / / prompt transaction / / close the trading window
	const int CMD_TRADEFALSE		= CMD_NORMAL + 7;	// Transaction cancellation / / prompt cancellation of the transaction / / close the trading window

	const int CMD_TRADPLAYERMONEY	= CMD_NORMAL + 8;	// Transaction interface refresh each other's money
	const int CMD_TRADHEROEMONEY	= CMD_NORMAL + 9;	// Refresh their money transaction interface

	const int CMD_TRADEPLAYERITEM	= CMD_NORMAL + 10;	// Transaction interface refresh each other's goods
	const int CMD_TRADEHEROITEM		= CMD_NORMAL + 12;	// Refresh their goods transaction interface

	const int CMD_TRADEPLAYERAGREE	= CMD_NORMAL + 13;	// The other party agreed to the transaction / / transaction ID to the other party unity
	const int CMD_TRADEPLAYERAPPLY	= CMD_NORMAL + 14;	// Other applications for the transaction / / is willing to pop the window and the other transactions

	const int CMD_FLASHPACKAGEITEM	= CMD_NORMAL + 15;	// Package set of items
	const int CMD_FLASHBANKMONEY	= CMD_NORMAL + 16;	// Refresh bank deposits

	const int CMD_TASKDIALOGOPEN	= CMD_NORMAL + 17;	// Open the task dialog box
	const int CMD_FLASHFRIENDLIST	= CMD_NORMAL + 18;	// Refresh buddy list

	const int CMD_FLASHEQUIPMENT	= CMD_NORMAL + 19;	// Equipment refresh box

	const int CMD_FLASHTEAM			= CMD_NORMAL + 20;	// Refresh Group interface
	const int CMD_TEAMINVITE		= CMD_NORMAL + 21;	// Team was invited to
	const int CMD_TEAMAPPLY			= CMD_NORMAL + 22;	// Application was made to team up
	
	const int CMD_FLASHWEAPONSKILL	= CMD_NORMAL + 23;	// Refresh weapon skills
	const int CMD_CHANGEPKMODE		= CMD_NORMAL + 24;	// PK model of change
	const int CMD_SETPKMODE			= CMD_NORMAL + 25;	// PK mode settings

	const int CMD_LEVELUP			= CMD_NORMAL + 26;	// People upgrade
	const int CMD_FLASHPK			= CMD_NORMAL + 27;	// Refresh PK values

	const int CMD_FLASHCHATLOGFILELIST			= CMD_NORMAL + 28;	// Refresh the list of chat log files
	const int CMD_FLASHCURRENTCHATLOGLINELIST	= CMD_NORMAL + 29;	// Refresh line to open the list of chats

	const int CMD_FLASH_MAGIC					= CMD_NORMAL + 30;  // Magic refresh list
	const int CMD_FLASH_MAGIC_EXP				= CMD_NORMAL + 31;  // Refresh magic experience

	const int CMD_SYNDICATE_APPLY				= CMD_NORMAL + 32;  // It was a request to you to join gangs
	const int CMD_SYNDICATE_INVITE				= CMD_NORMAL + 33;  // Some people invite you to join the gang
	const int CMD_FLASH_SYNDICATE				= CMD_NORMAL + 34;  // Refresh the protagonist of the gang (including gang name, title)

	const int CMD_START_MAGIC_BUSY				= CMD_NORMAL + 35;	// Delay the beginning of Magic
	const int CMD_END_MAGIC_BUSY				= CMD_NORMAL + 36;	// Magic end delay

	const int CMD_XPFULL						= CMD_NORMAL + 37;	// XP full
	const int CMD_XPEMPTY						= CMD_NORMAL + 38;	// Empty XP
	const int CMD_XPCHANGE						= CMD_NORMAL + 39;	// XP change

	const int CMD_QUERYFRIEND_OK				= CMD_NORMAL + 40;	// Friend successful query
	const int CMD_QUERYFRIEND_TIMEOUT			= CMD_NORMAL + 41;	// Inquiries Friends overtime

	const int CMD_FLASH_TEAM_FACE				= CMD_NORMAL + 42;	// Refresh team head
	const int CMD_FLASH_HERO_FACE				= CMD_NORMAL + 43;	// Refresh the protagonist's Head
	
	const int CMD_FLASH_SYNDICATE_WORD			= CMD_NORMAL + 44;	// Refresh gang message

	const int CMD_DIE							= CMD_NORMAL + 50;	// The death of the protagonist
	const int CMD_REBORN						= CMD_NORMAL + 51;	// Leading the revival of

	const int CMD_FRIEND_APPLY					= CMD_NORMAL + 52;	// It was suggested that Canada Friends

	const int CMD_GHOST_BEGIN					= CMD_NORMAL + 53;	// The beginning of the ghost state
	const int CMD_GHOST_END						= CMD_NORMAL + 54;	// Revocation of the ghost state

	const int CMD_PPCHANGE						= CMD_NORMAL + 55;	// Changes in physical points
	const int CMD_MAXPPCHANGE					= CMD_NORMAL + 56;	// The largest physical point

	const int CMD_FLASH_LEAVE_WORD				= CMD_NORMAL + 57;	// Refresh Message
	const int CMD_NEW_LEAVE_WORD				= CMD_NORMAL + 58;	// New Message

	const int CMD_FLASH_SYN_WAR_REPORT			= CMD_NORMAL + 59;	// Refresh gang war

	const int CMD_CHANGE_MAP					= CMD_NORMAL + 60;	// Cut screen

	const int CMD_FLASH_BOOTH_ITEM				= CMD_NORMAL + 62;	// Other items to refresh stalls					
	const int CMD_FLASH_BOOTHMANAGER_ITEM		= CMD_NORMAL + 63;	// Refresh their goods stalls	
	
	const int CMD_FLASH_BULLETIN_LIST			= CMD_NORMAL + 64;	// Notice the list of refresh	
	const int CMD_FLASH_BULLETIN_NOTE			= CMD_NORMAL + 65;	// Notice refresh content	

	const int CMD_OPEN_PLACE_STATUARY_DIALOG	= CMD_NORMAL + 66;	// Open interface to place the statue
	const int CMD_COURT							= CMD_NORMAL + 67;	// Proposal
	const int CMD_BECOURT						= CMD_NORMAL + 68;	// By marriage

	const int CMD_OPEN_PLACE_NPC_INFO_DIALOG	= CMD_NORMAL + 69;	// Npc placement tips open interface
	const int CMD_OPEN_PLACE_NPC_MODIFY_DIALOG	= CMD_NORMAL + 70;	// Open interface to adjust npc
	
	const int CMD_OPEN_FLASH_SYN_MEMBER			= CMD_NORMAL + 71;	// Refresh the list of gang members 
	const int CMD_OPEN_FLASH_SYN_MEMBER_INFO	= CMD_NORMAL + 72;	// Information on gang members to refresh 

	const int CMD_FLASH_MAGIC_STATUS			= CMD_NORMAL + 73;	// Magic refresh state 
	const int CMD_FLASH_OTHERPLAYER_EQUIPMENT	= CMD_NORMAL + 74;	// Refresh to see other people and equipment interface

	const int CMD_OPEN_ABORT_TRANSFORM_DLG		= CMD_NORMAL + 75;	// Cancel turned to open interface 
	const int CMD_CLOSE_ABORT_TRANSFORM_DLG		= CMD_NORMAL + 76;	// Cancel turned to close the interface 
	
	const int CMD_DICE_JOIN						= CMD_NORMAL + 77;	// Join the game
	const int CMD_DICE_QUIT						= CMD_NORMAL + 78;	// To leave the game
	const int CMD_DICE_FLASH_PLAYERLIST			= CMD_NORMAL + 79;	// Brush the list of game players
	const int CMD_DICE_FLASH_ANTES				= CMD_NORMAL + 80;	// Brush stakes gamble list

	const int CMD_FLASHENEMYLIST				= CMD_NORMAL + 81;	// Refresh list enemy
	const int CMD_QUERYENEMY_OK					= CMD_NORMAL + 82;	// Enemy of the success of inquiry
	const int CMD_QUERYENEMY_TIMEOUT			= CMD_NORMAL + 83;	// Query time-out enemy

	const int CMD_RESET							= CMD_NORMAL + 84;	// Reset

	const int CMD_RESOURCE_LOSE					= CMD_NORMAL + 85;  // The issue of the second set of resources
	const int CMD_ACTION_MESSAGEBOX				= CMD_NORMAL + 86;  // Message box
	const int CMD_ACTION_IDENTBOX				= CMD_NORMAL + 87;  // Identification of the box
	const int CMD_FRIEND_ACCEPT					= CMD_NORMAL + 88;  // Friends make the success of
	
	const int CMD_ACTION_SELECTEMBLEM			= CMD_NORMAL + 89;  // Select basket gang insignia
	const int CMD_ACTION_OPENDIALOG				= CMD_NORMAL + 90;  // Open dialogue basket

	const int CMD_ACTION_TEACHAPPLY				= CMD_NORMAL + 91;  // It was to you, the apprentice
	const int CMD_ACTION_STUDENTAPPLY			= CMD_NORMAL + 92;  // Some people you do want to apprentice
	const int CMD_FLASH_SCHOOLINFO				= CMD_NORMAL + 93;  // Master list refresh
	
	const int CMD_FLASH_PLAYERTASKLIST			= CMD_NORMAL + 94;	// Refresh task list players
	const int CMD_FLASH_PLAYERTASKDETIAL		= CMD_NORMAL + 95;	// Players set the task for more information
	
	const int CMD_ACTION_ACCEPTEDTASKLIST			= CMD_NORMAL + 96;  // Open the task list mercenaries - not completed
	const int CMD_ACTION_UNACCEPTEDTASKLIST			= CMD_NORMAL + 97;  // Open the task list mercenaries - not completed
	const int CMD_ACTION_COMPLETEDTASKLIST			= CMD_NORMAL + 98;  // Open the task list mercenaries - not completed
	const int CMD_ACTION_MYTASKLIST					= CMD_NORMAL + 99;  // Open the task list mercenaries - not completed
	const int CMD_ACTION_PLAYERTASKUP				= CMD_NORMAL + 100; // Bounty task orders to open interface
	const int CMD_ACTION_OPENSHOP					= CMD_NORMAL + 101; // Open store interface
	const int CMD_ACTION_OPENEMBED					= CMD_NORMAL + 103; // Upgrade equipment interface
	const int CMD_ACTION_OPENDEPOT					= CMD_NORMAL + 104;	// Storage interface

	const int CMD_ACTION_OPENUPANNOUNCE					= CMD_NORMAL + 105;		//New trade unions announced
	const int CMD_ACTION_OPENANNOUNCELIST				= CMD_NORMAL + 106;     //Notice the list of new trade union
	const int CMD_ACTION_OPENMYANNOUNCE					= CMD_NORMAL + 107;		//Notice my new union
	
	const int CMD_FLASH_ANNOUNCEINFO					= CMD_NORMAL + 108;		//Refresh Notice Information
	const int CMD_FLASH_ANNOUNCELIST					= CMD_NORMAL + 109;		//Notice the list of refresh

	const int CMD_ACTION_OPENMONSTERHATCH				= CMD_NORMAL + 110;		//Magic spoil the open hatch
	const int CMD_ACTION_OPENMONSTERALIVE				= CMD_NORMAL + 111;		//Open the revival of magic pet
	const int CMD_ACTION_OPENMONSTERIMPROVE				= CMD_NORMAL + 112;		//Open magic pet strengthen
	const int CMD_ACTION_OPENMONSTERDEPOT				= CMD_NORMAL + 113;		//Open magic pet warehouse
	const int CMD_FLASH_SECSCHOOLLIST					= CMD_NORMAL + 114;		//Refresh the list of disciples 2

	const int CMD_ACTION_OPENNPCFACE					= CMD_NORMAL + 115;		//Open NPC FACE DIALOG
	const int CMD_ACTION_OPENBOOTH						= CMD_NORMAL + 116;		//Set up a stall to open interface
	const int CMD_ACTION_OPENBOOTHFLAG					= CMD_NORMAL + 117;		//Determine the interface to open stall
	const int CMD_ACTION_OPENDICECFM					= CMD_NORMAL + 118;		//Open interface tables to determine

	const int CMD_ACTION_OPENADDAUCTION					= CMD_NORMAL + 119;		//Add auction to open interface
	const int CMD_ACTION_OPENAUCTIONBID					= CMD_NORMAL + 120;		//Open auction bidding interface
	const int CMD_ACTION_FLASHAUCTION					= CMD_NORMAL + 121;		//Auction bidding interface refresh
	const int CMD_ACTION_NEWAUCTION						= CMD_NORMAL + 122;		//Start a new auction
	const int CMD_ACTION_OVERAUCTION					= CMD_NORMAL + 123;		//The end of the current auction
		
	const int CMD_ACTION_OPENIMPROVE					= CMD_NORMAL + 124;	// Equipment to upgrade the quality of the interface
	const int CMD_ACTION_OPENIMPROVESOUL				= CMD_NORMAL + 125;	// upgrade equipment interface
	const int CMD_ACTION_OPENIMPROVELEVEL				= CMD_NORMAL + 126;	// Equipment to upgrade the interface level
	const int CMD_ACTION_OPENIMPROVEGEM					= CMD_NORMAL + 127;	// Mosaic interface equipment, precious stones
		
	const int CMD_ACTION_CLOSEBOOTH						= CMD_NORMAL + 128; // The closure of open stalls

	const int CMD_ACTION_OPENAUCPACKAGE					= CMD_NORMAL + 129; // Open player auction warehouse
	
	const int CMD_FLASH_MYPETINFO						= CMD_NORMAL + 130; // Used to update the value of the experience of imaginary animals and HP values
	const int CMD_FLASH_PETSTATUS						= CMD_NORMAL + 131; // Imaginary animals refresh information - call syncytial

	const int CMD_FLASH_SYNDOC							= CMD_NORMAL + 150; // Refresh the list of Corps documents
	const int CMD_FLASH_SYNALLY							= CMD_NORMAL + 151; // Legionella friend list refresh

	const int CMD_EVOMONSTER_SUC						= CMD_NORMAL + 152;	// Evolutionary success of imaginary animals

	const int CMD_ACTION_EVOMONSTERG						= CMD_NORMAL + 153; // Imaginary animals an evolutionary interface - Sacred
	const int CMD_ACTION_EVOMONSTERS						= CMD_NORMAL + 154;	// Imaginary animals an evolutionary interface - Warcraft

	const int CMD_ACTION_EVOMONSTER1						= CMD_NORMAL + 155; // Imaginary animals evolved secondary interface - the god of life
	const int CMD_ACTION_EVOMONSTER2						= CMD_NORMAL + 156;	// Imaginary animals evolved secondary interface - Chaos Death
	const int CMD_ACTION_EVOMONSTER3						= CMD_NORMAL + 157; // Imaginary animals evolved secondary interface - the god of justice
	const int CMD_ACTION_EVOMONSTER4						= CMD_NORMAL + 158;	// Imaginary animals evolved secondary interface - the god of conspiracy 
	const int CMD_ACTION_EVOMONSTER5						= CMD_NORMAL + 159; //  Imaginary animals evolved secondary interface - the god of wisdom 
	const int CMD_ACTION_EVOMONSTER6						= CMD_NORMAL + 160; // Imaginary animals evolved secondary interface - the god of war
	const int CMD_ACTION_EVOMONSTER7						= CMD_NORMAL + 161; // Imaginary animals evolved secondary interface - the god of corruption
	const int CMD_ACTION_EVOMONSTER8						= CMD_NORMAL + 162; // Imaginary animals evolved secondary interface - the god of forging  
	
	const int CMD_OPEN_FLASH_SYNINFO						= CMD_NORMAL + 163;	// Query to return to gang information
	const int CMD_ACTION_ADDALLY							= CMD_NORMAL + 164; // Association received the invitation
    const int CMD_CALL_PET_OUT                              = CMD_NORMAL + 165; // Players enter the map to set off all the imaginary animals
	const int CMD_PET_DIE                                   = CMD_NORMAL + 166;
	const int CMD_PET_ALIVE                                 = CMD_NORMAL + 167;
	void PostCmd(DWORD dwCommand, int nData= 0);
#endif

extern HWND g_hGameWnd;
extern BOOL g_bLocalVersion;
//---------------------------------------------------------------------
#endif