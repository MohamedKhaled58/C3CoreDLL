//--------------------------------------------------------------------------------------
// File Name: DataAniModule.cpp
// Create by: Huang Yuhang
// Create on: 2003/9/24 11:47
//--------------------------------------------------------------------------------------
#include "DataAniModule.h"
#include "AniFileManager.h"

//--------------------------------------------------------------------------------------
DATAANI_API IDai*	IDai::CreateNew()
{
	CAniFileManager* pObj = new CAniFileManager;
	return pObj;
}

//--------------------------------------------------------------------------------------
IFrameSet* IFrameSet::CreateNew()
{
	CFrameSet* pFrameSet = new CFrameSet;
	return pFrameSet;
}
//--------------------------------------------------------------------------------------
