//-------------------------------------------------------
// SurfaceLayer.cpp
//-------------------------------------------------------
#include "SurfaceLayer.h"
//-------------------------------------------------------
CSurfaceLayer::CSurfaceLayer()
{
	// TODO ...
}
//-------------------------------------------------------
CSurfaceLayer::~CSurfaceLayer()
{
	// TODO ...
}
//-------------------------------------------------------------
void CSurfaceLayer::Show(CMyPos posShow)
{
	// TODO ...
}
//-------------------------------------------------------------
void CSurfaceLayer::Process(void* pInfo)
{
	// TODO ...
}
//-------------------------------------------------------------
int  CSurfaceLayer::GetType()
{
	return LAYER_SURFACE;
}
//-------------------------------------------------------------
CSurfaceLayer* CSurfaceLayer::CreateNew()
{
	CSurfaceLayer* pLayer = new CSurfaceLayer;
	return pLayer;
}

