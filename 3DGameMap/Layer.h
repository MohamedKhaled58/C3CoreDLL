////////////////////////////////////////////
// Layer.h
///////////////////////////////////////////

#ifndef _LAYER_H
#define _LAYER_H

//-------------------------------------------------------------
// header files ...
#include "BaseFunc.h"
//-------------------------------------------------------------

//-------------------------------------------------------------
// ���ڵر����� layer �ĸ߶�Ϊ 0
//-------------------------------------------------------------
struct  LayerInfo
{
        unsigned short     usTerrain;      // ����
        unsigned short     usMask;         // �赲����
        short              sAltitude;      // �߶ȣ����ػ�����ڵر�ĸ߶�
        LayerInfo*         pLayer;         // ��һ��Layer
};
typedef struct
{
        unsigned short     usTerrain;      // ����
        unsigned short     usMask;         // �赲����
        short              sAltitude;      // �߶ȣ����ػ�����ڵر�ĸ߶�
}IndexLayerInfo;


class CLayer
{
public:
        unsigned short     usTerrain;       // ����
        unsigned short     usMask;         // �赲����
        short              sAltitude;      // �߶ȣ����ػ�����ڵر�ĸ߶�
	
public:
	CLayer();
	virtual ~CLayer();
	
public:
	static HANDLE	        s_hHeap;
	static UINT		s_uNumAllocsInHeap;
	static BOOL		IsValidPt(void* p);

public:
	void*  operator new	(size_t size);
	void   operator delete	(void* p);
};

typedef struct
{
        LayerInfo       m_infoLayer;
        bool            m_bSearched;
}CellInfo;

#include <deque>
#include <vector>
using namespace std;
typedef deque<CLayer* >  DEQUE_LAYER;
typedef vector<IndexLayerInfo> VECTOR_INDEXLAYER;
//-------------------------------------------------------------
#endif
