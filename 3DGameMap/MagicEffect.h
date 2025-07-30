// MagicEffect.h: interface for the CMagicEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGICEFFECT_H__8388C5C4_FE86_474B_B1D2_279F857E69D1__INCLUDED_)
#define AFX_MAGICEFFECT_H__8388C5C4_FE86_474B_B1D2_279F857E69D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseFunc.h"

class C3DMapEffect;
enum
{
	MAGICEFFECT_NONE				= 0,		// �Ƿ�
	MAGICEFFECT_BODY_BODY			= 1,		// ��ʼ->���壭>Ŀ������->����
	MAGICEFFECT_BODY_TRACE_BODY		= 2,		// ��ʼ->���壭>�켣��>Ŀ������->����
	MAGICEFFECT_BODY_TERRAIN_BODY	= 3,		// ��ʼ->Ŀ���
	MAGICEFFECT_BODY_TRACE_POS		= 4,		// ��ʼ->���壭>�켣��>λ��->���� // ��Ч��ֻ����
	
	MAGICEFFECT_ARROW				= 98,		// ����������Ŀ��㣬������ // ʵ���ֻ����
	MAGICEFFECT_SOUL				= 99,		// �������� ���⴦��
};

typedef struct 
{
	OBJID	idRole;
	DWORD	dwData;
}MagicEffectRoleInfo;

typedef struct 
{
	C3DMapEffect* pEffect[1];
}MagicEffectSoulInfo;



#include <vector>
using namespace std;
typedef vector<MagicEffectRoleInfo* > VECTOR_MAGICEFFECTROLEINFO;

class CMagicEffect  
{
public:
	CMagicEffect();
	virtual ~CMagicEffect();

private:
	CMyPos	m_posTarget;
	CMyPos	m_posBegin;
	CMyPos	m_posEnd;
	DWORD	m_dwBegin;
	int		m_nType;
	OBJID	m_idSender;
	OBJID	m_idTarget;
	DWORD	m_dwMagicType;
	DWORD	m_dwLevel;
	BOOL	m_bBegin;
	BOOL	m_bDelayOk;
	void*	m_pData;
	DWORD	m_dwMoment;
	DWORD	m_dwData;

	//for magiceffect soul 
	DWORD   m_dwDelay;
	float   m_fSpeedA;

	CMy3DDir	m_dir3D;
	VECTOR_MAGICEFFECTROLEINFO m_setRoleInfo;

public:
	int		m_nDir;
	int		m_nIndex; //for soulex
	
private:
	void Destroy();

public:
	static CMagicEffect* CreateNew(OBJID idSender, OBJID idTarget, DWORD dwMagicType, DWORD dwLevel, int nType = MAGICEFFECT_NONE,int nIndex=0);
	static CMagicEffect* CreateNewArrow(OBJID idSender, OBJID idTarget, int nArrowType, DWORD dwDelay = 0);
	static CMagicEffect* CreateNewTerrain(OBJID idSender, CMyPos posTarget, DWORD dwMagicType, DWORD dwLevel);

	void   GetSoulDirectPos(int nIndex, int nDir, int &x, int &y);
	BOOL CreateArrow(OBJID idSender, OBJID idTarget, int nArrowType, DWORD dwDelay = 0);
	BOOL Create(OBJID idSender, OBJID idTarget, DWORD dwMagicType, DWORD dwLevel, int nType = MAGICEFFECT_NONE,int nIndex=0);
	BOOL CreateTerrain(OBJID idSender, CMyPos posTarget, DWORD dwMagicType, DWORD dwLevel);
	
	void AddRoleInfo(OBJID idRole, DWORD dwData);
	BOOL Process();
	BOOL ProcessBodyBody();
	BOOL ProcessBodyTraceBody();
	BOOL ProcessBodyTracePos();
	BOOL ProcessSoul();
	BOOL ProcessSoulEx();
	
	BOOL ProcessArrow();
	BOOL ProcessBodyTerrainBody();
	void BeginScreenEffect(DWORD dwScreenRepresent);
};

#endif // !defined(AFX_MAGICEFFECT_H__8388C5C4_FE86_474B_B1D2_279F857E69D1__INCLUDED_)
