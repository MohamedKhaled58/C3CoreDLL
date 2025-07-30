#ifndef _c3_camera_h_
#define _c3_camera_h_

#ifdef	C3_CORE_DLL_EXPORTS
#define C3_CORE_DLL_API __declspec ( dllexport )
#else
#define C3_CORE_DLL_API __declspec ( dllimport )
#endif

#include "c3_common.h"

/* ��Ӱ���ṹ */
typedef struct
{
	char				*lpName;		// ����
	D3DXVECTOR3			*lpFrom;		// λ��
	D3DXVECTOR3			*lpTo;			// Ŀ��
	float				fNear;			// ��ƽ��
	float				fFar;			// Զƽ��
	float				fFov;			// ����

	DWORD				dwFrameCount;
	int					nFrame;
} C3Camera;
C3_CORE_DLL_API
void Camera_Clear ( C3Camera *lpCamera );

C3_CORE_DLL_API
BOOL Camera_Load ( C3Camera **lpCamera,
				   char *lpName,
				   DWORD dwIndex );
C3_CORE_DLL_API
BOOL Camera_Save ( char *lpName, C3Camera *lpCamera, BOOL bNew );
C3_CORE_DLL_API
void Camera_Unload ( C3Camera **lpCamera );

C3_CORE_DLL_API
void Camera_NextFrame ( C3Camera *lpCamera, int nStep );

/* 
	�����Ӿ���
	----------
	����Ӱ����λ�û�Ŀ�ĸı����Ҫ���ô˺���
*/
C3_CORE_DLL_API
BOOL Camera_BuildView ( C3Camera *lpCamera, BOOL bSet = true );
/*
	����ͶӰ����
	------------
	����Ӱ����Զ��ƽ�������ı����Ҫ���ô˺���
*/
C3_CORE_DLL_API
BOOL Camera_BuildProject ( C3Camera *lpCamera, BOOL bSet = true );
/*
	����ƽ��ͶӰ����
	------------
	����Ӱ����Զ��ƽ�������ı����Ҫ���ô˺���
*/
C3_CORE_DLL_API
BOOL Camera_BuildOrtho ( C3Camera *lpCamera,
						 float fWidth,
						 float fHeight,
						 BOOL bSet = true );

C3_CORE_DLL_API
void Camera_Process1stRotate ( C3Camera *lpCamera,
							   float fHRadian,
							   float fVRadian );
C3_CORE_DLL_API
void Camera_Process1stTranslate ( C3Camera *lpCamera,
								  float fDirRandian,
								  float fStep );
C3_CORE_DLL_API
void Camera_ProcessXYTranslate ( C3Camera *lpCamera,
								 float fDirRandian,
								 float fStep );

#endif