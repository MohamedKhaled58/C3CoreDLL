//----------------------------------------------------//
// MapLayer.cpp
//----------------------------------------------------//
#include "MapLayer.h"

//----------------------------------------------------//
void CMapLayer::Show(CMyPos posShow)
{
	::LogMsg("MapLayer.Show(), 纯虚函数调用");
}
//----------------------------------------------------//
void CMapLayer::Process(void* pInfo)
{
	::LogMsg("MapLayer.Process(), 纯虚函数调用");
}
//----------------------------------------------------//
int CMapLayer::GetType()
{
	::LogMsg("MapLayer.GetType(), 纯虚函数调用");
	return LAYER_NONE;
}
//----------------------------------------------------//
