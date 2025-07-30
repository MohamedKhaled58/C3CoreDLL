#ifndef _c3_phy_h_
#define _c3_phy_h_

#ifdef	C3_CORE_DLL_EXPORTS
#define C3_CORE_DLL_API __declspec ( dllexport )
#else
#define C3_CORE_DLL_API __declspec ( dllimport )
#endif

#include "c3_common.h"
#include "c3_texture.h"
#include "c3_key.h"

/* �������嶥�㶨�� */
#define PHY_OUT_VERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
struct PhyOutVertex
{
	float							x, y, z;
	//float							nx, ny, nz;
	DWORD							color;
	float							u, v;
};

#define		_BONE_MAX_				2
#define		_MORPH_MAX_				4
struct PhyVertex
{
	D3DXVECTOR3						pos[_MORPH_MAX_];
	float							u, v;
	//float							nx, ny, nz;
	DWORD							color;
	DWORD							index[_BONE_MAX_];
	float							weight[_BONE_MAX_];
};

struct C3KeyFrame
{
	DWORD							pos;
	D3DXMATRIXA16					*matrix;
};
struct C3Motion
{
	DWORD							dwBoneCount;		// ������
	DWORD							dwFrames;			// ֡��

	DWORD							dwKeyFrames;
	C3KeyFrame						*lpKeyFrame;

	D3DXMATRIXA16					*matrix;

	DWORD							dwMorphCount;
	float							*lpMorph;
	int								nFrame;				// ��ǰ֡
};

C3_CORE_DLL_API 
void Motion_Clear ( C3Motion *lpMotion );
C3_CORE_DLL_API
BOOL Motion_Load ( C3Motion **lpMotion, FILE *file );
C3_CORE_DLL_API
BOOL Motion_LoadPack ( C3Motion **lpMotion, HANDLE f );
C3_CORE_DLL_API
BOOL Motion_Save ( char *lpName, C3Motion *lpMotion, BOOL bNew );
C3_CORE_DLL_API
void Motion_Unload ( C3Motion **lpMotion );
C3_CORE_DLL_API
void Motion_GetMatrix ( C3Motion *lpMotion, DWORD dwBone, D3DXMATRIXA16 *lpMatrix );

struct C3Phy
{
	char							*lpName;			// ����

	DWORD							dwBlendCount;		// ÿ�������ܵ����ٸ�����Ӱ��
	
	DWORD							dwNVecCount;		// ������(��ͨ����)
	DWORD							dwAVecCount;		// ������(͸������)
	PhyVertex						*lpVB;				// �����(��ͨ����/͸������)
	LPDIRECT3DVERTEXBUFFER8			vb;

	DWORD							dwNTriCount;		// �������(��ͨ�����)
	DWORD							dwATriCount;		// �������(͸�������)
	WORD							*lpIB;				// ������(��ͨ�����/͸�������)
	LPDIRECT3DINDEXBUFFER8			ib;
	
	char							*lpTexName;			// [ be used by plugin ]
	int								nTex;
	int								nTex2;
	D3DXVECTOR3						bboxMin, bboxMax;

	C3Motion						*lpMotion;

	float							fA, fR, fG, fB;

	C3Key							Key;
	BOOL							bDraw;

	DWORD							dwTexRow;

	D3DXMATRIXA16					InitMatrix;

	// 12-20-2002 : "STEP"
	D3DXVECTOR2						uvstep;
};

C3_CORE_DLL_API
void Phy_Clear ( C3Phy *lpPhy );
C3_CORE_DLL_API
BOOL Phy_Load ( C3Phy **lpPhy, FILE *file, BOOL bTex = false );
C3_CORE_DLL_API
BOOL Phy_LoadPack ( C3Phy **lpPhy, HANDLE f, BOOL bTex = false );
C3_CORE_DLL_API
BOOL Phy_Save ( char *lpName, C3Phy *lpPhy, BOOL bNew );
C3_CORE_DLL_API
void Phy_Unload ( C3Phy **lpPhy );
C3_CORE_DLL_API
void Phy_Prepare ( void );
C3_CORE_DLL_API
BOOL Phy_Calculate ( C3Phy *lpPhy );
C3_CORE_DLL_API
BOOL Phy_DrawNormal ( C3Phy *lpPhy );
C3_CORE_DLL_API
BOOL Phy_DrawAlpha ( C3Phy *lpPhy, BOOL bZ = false, int nAsb=5, int nAdb=6);
C3_CORE_DLL_API
void Phy_NextFrame ( C3Phy *lpPhy, int nStep );
C3_CORE_DLL_API
void Phy_SetFrame ( C3Phy *lpPhy, DWORD dwFrame );

C3_CORE_DLL_API
void Phy_Muliply ( C3Phy *lpPhy, int nBoneIndex, D3DXMATRIXA16 *matrix );

C3_CORE_DLL_API
void Phy_SetColor ( C3Phy *lpPhy,
					float alpha,
					float red,
					float green,
					float blue );

C3_CORE_DLL_API
void Phy_ClearMatrix ( C3Phy *lpPhy );

C3_CORE_DLL_API
void Phy_ChangeTexture ( C3Phy *lpPhy, int nTexID, int nTexID2=0 );
/*
C3_CORE_DLL_API
void Phy_LookAt ( C3Phy *lpPhy,
				  int nAxis,
				  D3DXMATRIX *lpRet );
*/
#endif
