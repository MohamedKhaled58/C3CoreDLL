//----------------------------------------------------
//3DMapObj.cpp
//----------------------------------------------------
#include "3DMapObj.h"
#include "BaseFunc.h"
#include "3DGameMap.h"
//----------------------------------------------------

C3DMapObj::C3DMapObj()
{
}
//----------------------------------------------------
C3DMapObj::~C3DMapObj()
{
}
//----------------------------------------------------
void C3DMapObj::GetWorldPos(CMyPos& posWorld)
{
	g_objGameMap.Cell2World(m_posCell.x, m_posCell.y, posWorld.x, posWorld.y);
}
//----------------------------------------------------
void C3DMapObj::GetPos(CMyPos& posCell)
{
	posCell = m_posCell;
}
//----------------------------------------------------
void C3DMapObj::SetPos(CMyPos posCell)
{
	m_posCell = posCell;
}
//----------------------------------------------------
