//--------------------------------------------------------------------------------------
// File Name: DataAniModule.h
// Create by: Huang Yuhang
// Create on: 2003/9/24 11:02
//--------------------------------------------------------------------------------------
#ifndef _DATAANIMODULE_H
#define _DATAANIMODULE_H

#define DATAANI_API __declspec(dllexport)
#pragma warning(disable:4786)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.H>
#include <VECTOR>

using namespace std;

const int MAX_ANIFRAMEAMOUNT = 255;

class DATAANI_API IFrameSet
{
public:
	IFrameSet(void){}
	virtual ~IFrameSet(void){this->Clear();}
public:
	virtual void InsertFrame(const char* pszFrame){;}
	virtual void Clear(){;}
	virtual unsigned long	GetFrameAmount(){return 0;}
	virtual char*			GetFrameByIndex(int nIndex){return NULL;}
public:
	static IFrameSet* CreateNew();
};
class DATAANI_API IDai
{
public:
	enum
	{
			SUCCESS						=	0,  // �ɹ�
			CODE_UNDEFINED_ERROR		=	1,	// δ�������
			CODE_INTERIOR_ERROR			=	2,	// �ڲ�����
			CODE_EXTERIOR_ERROR			=	3,	// �ⲿ����
			CODE_UNKNOW_FEXT			=	4,	// δ֪�ļ���չ��
			CODE_OPENFILE_FALSE			=	5,	// ���ļ�ʧ��
			CODE_TITLEFORMAT_ERROE		=	6,	// [Title]��ʽ����
			CODE_FRAMEAMOUNT_ERROR		=	7,	// ֡������
			CODE_FRAMEAMOUNT_OVERFLOW	=	8,	// ֡�����
			CODE_FRAMEINFO_ERROR		=	9,	// ֡��Ϣ����
			CODE_UNKNOW_FILEHEAD		=	10,	// δ֪�ļ�ͷ
			CODE_UNKNOW_VERSION			=	11, // δ֪�ļ��汾
			CODE_ANIINDEX_OVERFLOW		=	12, // �������
			CODE_DIRINDEX_OVERFLOW		=	13,	// ·�����
			CODE_EXTINDEX_OVERFLOW		=	14,	// ��չ�����
			CODE_STRINDEX_OVERFLOW		=	15,	// �����
			CODE_STRINGBUFFER_OVERFLOW	=	16, // ���ռ����
			CODE_INFO_NOTFOUND			=	17, // δ�ҵ���Ϣ
	};
public:
	IDai(void){}
	virtual ~IDai(void){}
public:
	virtual unsigned long	Load(const char* pszFileName, BOOL bFroceBin){return 0;}
	virtual void			UnLoad(const char* pszFileName){}
	virtual void			Clear(){}
	virtual unsigned long	Locate(const char* pszFileName, const char* pszindex, IFrameSet* pInfoFrame){return 0;}
	virtual void			ClearBuffer(IFrameSet* pInfoFrame){;}
	
public:
	static IDai*	CreateNew();
// for editor
#ifdef _DAI_EDITOR
public:
	virtual unsigned long	Ani2Dai(const char* pszAniFileName, const char* pszDaiFileName, unsigned long& uLastErrorLine){return 0;}
	virtual unsigned long	Dai2Ani(const char* pszDaiFileName, const char* pszAniFileName, unsigned long& uLastErrorLine){return 0;}
#endif
};


#endif