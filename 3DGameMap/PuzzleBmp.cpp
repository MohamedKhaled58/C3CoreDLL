//------------------------------------------------
// PuzzleBmp.cpp
//------------------------------------------------
#include "PuzzleBmp.h"
#include "GameDataSet.h"
#include "3DGameMap.h"
#include "Physics.h"

int CPuzzleBmp::s_nRectAmount = 0;
CMyRect	CPuzzleBmp::s_setRect[_MAX_DIRTY_RECT]; 

//------------------------------------------------
CPuzzleBmp::CPuzzleBmp()
{
	m_usPuzzleIndex = NULL;
	m_nPuzzleAmount = 0;
	this->Destroy();
	strcpy(m_szAniFile, "");
	m_nZoomInNum = 1;
	m_nGrideSize = PUZZLE_GRIDE_SIZE;
	m_bTerrain = true;
	m_nRollSpeedX	= 0;
	m_nRollSpeedY	= 0;
	m_dwTimeBegin	= ::TimeGet();
	m_nMoveRateX	= 100;
	m_nMoveRateY	= 100;
	m_bRoll			= true;
	m_dwTimer		= ::TimeGet();
	m_dwColor		= 0xffffffff;
}
//------------------------------------------------
CPuzzleBmp::~CPuzzleBmp()
{
	this->Destroy();
}

//------------------------------------------------
void CPuzzleBmp::Destroy()
{
	if(m_usPuzzleIndex)
		delete[] m_usPuzzleIndex; 
	m_usPuzzleIndex = NULL;
	m_nPuzzleAmount = 0;
//	if(strlen(m_szAniFile) != NULL)
//		CAni::s_setAniFile.DelAniFile(m_szAniFile);
}
//------------------------------------------------
void CPuzzleBmp::SetSize(CMySize infoSize)
{
	this->Destroy();
	int nAmount = infoSize.iWidth * infoSize.iHeight;
	m_infoSize = infoSize;
	m_usPuzzleIndex = new unsigned short[nAmount];
	for(int i = 0; i < nAmount; i++)
	{
		unsigned short* pusIndex = m_usPuzzleIndex + i;
		*pusIndex = 65535;
	}
	m_nPuzzleAmount = nAmount;
}
//------------------------------------------------
void CPuzzleBmp::Show(int iPosX, int iPosY, BOOL bGrid, BOOL bPos)
{
//	bPos = bGrid = true;
	DWORD dwFrame = (::TimeGet()-m_dwTimer)/160;
	BOOL bRollBack = true;
	if((m_nRollSpeedX == 0) && 
		(m_nRollSpeedY == 0))
	{
		bRollBack = false;
	}
	if(!m_bRoll)
		bRollBack = false;

	CMySize sizeBmp;
	this->GetSize(sizeBmp);
	if(bRollBack)
	{
		CMyPos posOffset;
		DWORD dwTimeCurrent = ::TimeGet();
		posOffset.x = m_nRollSpeedX * m_nMoveRateX * (dwTimeCurrent - m_dwTimeBegin)/(1000 * 100);
		posOffset.y = m_nRollSpeedY * m_nMoveRateY * (dwTimeCurrent - m_dwTimeBegin)/(1000 * 100);

		iPosX += posOffset.x;
		iPosY += posOffset.y;
		iPosX = iPosX%(int)sizeBmp.iWidth;
		iPosY = iPosY%(int)sizeBmp.iHeight;
	}
	if(m_bTerrain)
		s_nRectAmount = 0;

	this->PreLoad(iPosX, iPosY);
	CMyPos posCell;
	posCell.x = -iPosX/m_nGrideSize;
	posCell.y = -iPosY/m_nGrideSize;
	if(iPosX>0)
		posCell.x --;
	if(iPosY>0)
		posCell.y --;

	CMySize infoSize;
	this->GetSizeByGride(infoSize);

	int nRealGridrSize = m_nGrideSize*g_objGameMap.GetScale()/_NORMAL_SCALE;
	
	int nAddPuzzleX = PUZZLE_SCRX/m_nGrideSize - PUZZLE_SCRX/nRealGridrSize;
	int nAddPuzzleY = PUZZLE_SCRY/m_nGrideSize - PUZZLE_SCRY/nRealGridrSize;

	int nAmountX = PUZZLE_SCRX/nRealGridrSize+3;
	int nAmountY = PUZZLE_SCRY/nRealGridrSize+3;
	CMyPos posView;
	posView.x  =  iPosX + posCell.x*m_nGrideSize;
	posView.y  =  iPosY + posCell.y*m_nGrideSize;
	if(nRealGridrSize > m_nGrideSize)
	{
		nAmountX += nAddPuzzleX;
		nAmountY += nAddPuzzleY;

		nAddPuzzleX = nAddPuzzleY = 0;
	}
	if(nRealGridrSize < m_nGrideSize)
	{
		nAmountX += nAddPuzzleX+1;
		nAmountY += nAddPuzzleY+1;

		nAddPuzzleX = nAddPuzzleY = -1;
	}
	
	for(int i = nAddPuzzleX; i < nAmountY; i++)
	{
		for(int j = nAddPuzzleY; j< nAmountX; j++)
		{
			CMyPos posCellShow;
			posCellShow.x = posCell.x + j;
			posCellShow.y = posCell.y + i;
			if(posCellShow.x < 0)
			{
				if(!bRollBack)
					continue;
				else
					posCellShow.x += infoSize.iWidth;
			}
			if(posCellShow.y < 0)
			{
				if(!bRollBack)
					continue;
				else
					posCellShow.y += infoSize.iHeight;
			}
			
			
			if(posCellShow.x >= infoSize.iWidth)
			{
				if(!bRollBack)
					continue;
				else
					posCellShow.x -= infoSize.iWidth;

			}
			if(posCellShow.y >= infoSize.iHeight)
			{
				if(!bRollBack)
					continue;
				else
					posCellShow.y -= infoSize.iHeight;
			}
			
			CMyPos posShow;
			posShow.x = posView.x + j*m_nGrideSize;
			posShow.y = posView.y + i*m_nGrideSize;
	
			g_objGameMap.MapScaleShowPos(posShow.x, posShow.y);
			int nIndex = this->GetGrid(posCellShow.x, posCellShow.y);
			
			if(nIndex == 65535)
			{
				// ͸��
				if(bGrid)
				{
					CMyBitmap::ShowRect(posShow.x, posShow.y, 
						posShow.x + m_nGrideSize, posShow.y + m_nGrideSize, 0xffffff00); 
				}
				if(bPos)
				{
					char szPos[64];
					sprintf(szPos, "��%d,%d��", posCellShow.x, posCellShow.y);
					CMySize sizeFont;
					CMyBitmap::GetFontSize(sizeFont);
					CMyBitmap::ShowString(posShow.x, posShow.y, 0xffffff, szPos);
				}
			}
			else
			{
				char szTitle[64];
				sprintf(szTitle, "Puzzle%d", nIndex);
				CAni* pAni = g_objGameDataSet.GetDataAni(m_szAniFile, szTitle, EXIGENCE_IMMEDIATE, g_objGameDataSet.m_dwPuzzleLife);
				if(pAni)
				{
					CMyBitmap* pBmp = pAni->GetFrame(0);
					if(pBmp)
					{
						DWORD dwARGB = m_dwColor;
						unsigned char ucA, ucR, ucG, ucB;
						ucA = dwARGB >> 24;
						ucR = (dwARGB & 0x00ff0000) >> 16;
						ucG = (dwARGB & 0x0000ff00) >> 8;
						ucB = dwARGB & 0x000000ff;
						pBmp->SetColor(ucA, ucR, ucG, ucB);
					}
					if(m_bTerrain)
					{
						CMyRect rect;
						rect.l = posShow.x;
						rect.t = posShow.y;
						rect.r = posShow.x + nRealGridrSize;
						rect.b = posShow.y + nRealGridrSize;
						this->TestRect(rect, true, pBmp->IsbTransparentFormat());
						
						pAni->ShowEx(dwFrame, posShow.x, posShow.y, NULL, nRealGridrSize, nRealGridrSize);
					}
					else
					{	
						CMyRect rect;
						rect.l = posShow.x;
						rect.t = posShow.y;
						rect.r = posShow.x + nRealGridrSize;
						rect.b = posShow.y + nRealGridrSize;
						if(this->TestRect(rect, false, pBmp->IsbTransparentFormat()))
							pAni->ShowEx(dwFrame, posShow.x, posShow.y, NULL, nRealGridrSize, nRealGridrSize);
						else
							int ll = 0;
					}

					if(bGrid)
					{
						CMyBitmap::ShowRect(posShow.x, posShow.y, 
									posShow.x + m_nGrideSize, posShow.y + nRealGridrSize, 0xffffff00); 
					}
					if(bPos)
					{
						char szPos[64];
						sprintf(szPos, "��%d,%d,%d��", posCellShow.x, posCellShow.y, nIndex);
						CMySize sizeFont;
						CMyBitmap::GetFontSize(sizeFont);
						CMyBitmap::ShowString(posShow.x, posShow.y, 0xffffff00, szPos);
					}
				}
				else
				{
					// ��ͼƬ��Դ
					CMyBitmap::ShowBlock(posShow.x, posShow.y, 
						posShow.x + m_nGrideSize, posShow.y + nRealGridrSize, 0xffffff00, 0xffffff00, 0xffffff00, 0xffffff00); 
					CMyBitmap::ShowRect(posShow.x, posShow.y, 
						posShow.x + m_nGrideSize, posShow.y + nRealGridrSize, 0xffffff00); 
				}
			}
			
		}
	}
	
}
//------------------------------------------------
void CPuzzleBmp::SetGrid(int iPosX, int iPosY, unsigned short usIndex)
{
	CMyPos posGrid;
	posGrid.x = -iPosX/m_nGrideSize;
	posGrid.y = -iPosY/m_nGrideSize;
	unsigned short* pusIndex = m_usPuzzleIndex + posGrid.y*m_infoSize.iWidth +posGrid.x;
	*pusIndex = usIndex;
}
//------------------------------------------------
unsigned short CPuzzleBmp::GetGrid(CMyPos posShow)
{
	CMyPos posGrid;
	posGrid.x = -posShow.x/m_nGrideSize;
	posGrid.y = -posShow.y/m_nGrideSize;
	return this->GetGrid(posGrid.x, posGrid.y);
}
//------------------------------------------------

BOOL CPuzzleBmp::Load(char* pszFile)
{
	if(!pszFile)
		return false;
	
	FILE* fp = fopen(pszFile, "rb");
	if(!fp)
		return false;
	// header..(8 bytes)
	char szHeader[8]="";
	fread(szHeader, 1, 8, fp);
	// check header ...
	m_dwVersion = 0;
	if(strcmp(szHeader, "PUZZLE") == 0)
		m_dwVersion = 1;
	else
	{
		if(strcmp(szHeader, "PUZZLE2") == 0)
			m_dwVersion = 2;
	}
	
	if(m_dwVersion == 0)
	{
		fclose(fp);
		return false;
	}
	// AniFile.. (256 bytes)
	char szAni[256];
	fread(szAni, 1, 256, fp);
	this->SetAniFile(szAni);
	// Size...
	CMySize infoSize;
	fread(&infoSize.iWidth, sizeof(UINT), 1, fp);
	fread(&infoSize.iHeight, sizeof(UINT), 1, fp);
	this->SetSize(infoSize);
	
	// Grid...
/*	int nAmount = infoSize.iWidth*infoSize.iHeight;
	m_setAniInfo.clear();
	for(int i = 0; i < nAmount; i++)
	{
		unsigned short usData;
		fread(&usData, sizeof(unsigned short), 1, fp);
		m_setAniInfo.push_back(usData);
	}*/
	fread(m_usPuzzleIndex, sizeof(unsigned short), m_nPuzzleAmount, fp);
	if(m_dwVersion == 2)
	{
		// �ƶ��ٶ�
		fread(&m_nRollSpeedX, sizeof(int), 1, fp);
		fread(&m_nRollSpeedY, sizeof(int), 1, fp);
	}
	else
	{
		m_nRollSpeedX = m_nRollSpeedY = 0;
	}
	fclose(fp);
	return true;
}
//------------------------------------------------
unsigned short CPuzzleBmp::GetGrid(int iPosX, int iPosY)
{
	unsigned short usIndex;
	if((iPosX < 0)||(iPosY < 0) || (iPosX >= m_infoSize.iWidth) || ((iPosY >= m_infoSize.iHeight)))
		return 65535;
	if((iPosY * m_infoSize.iWidth + iPosX) >= m_nPuzzleAmount)
		return 65535;
	unsigned short* pusIndex = m_usPuzzleIndex + iPosY * m_infoSize.iWidth + iPosX;	
	usIndex = *pusIndex;
	return  usIndex;
}
//------------------------------------------------
void CPuzzleBmp::GetSize(CMySize &infoSize)
{
	infoSize.iHeight = m_infoSize.iHeight * m_nGrideSize;
	infoSize.iWidth  = m_infoSize.iWidth  * m_nGrideSize;
}
//------------------------------------------------
void CPuzzleBmp::PreLoad(int iPosX, int iPosY)
{
	// do preload ...
	
	// ����Cell����
	CMyPos posCell;
	posCell.x = -iPosX/m_nGrideSize;
	posCell.y = -iPosY/m_nGrideSize;
	
	CMyPos posView;
	posView.x  =  iPosX + posCell.x*m_nGrideSize;
	posView.y  =  iPosY + posCell.y*m_nGrideSize;
	
	
	// ����ʾ��Χ
	int nAmountX = PUZZLE_SCRX/m_nGrideSize+2;
	int nAmountY = PUZZLE_SCRY/m_nGrideSize+2;
	
	int nPreLoadSize =  g_objGameDataSet.m_dwPuzzlePreloadSize;
	// ��ʼ��ʾ
	for(int i = 0-nPreLoadSize; i < nAmountY+nPreLoadSize; i++)
	{
		for(int j = 0-nPreLoadSize; j< nAmountX+nPreLoadSize; j++)
		{
			CMyPos posCellShow;
			
			// ��Ҫ���ص�Cell
			posCellShow.x = posCell.x + j;
			posCellShow.y = posCell.y + i;
			
			// �޳���Cell
			if(posCellShow.x < 0)
				continue;
			if(posCellShow.y < 0)
				continue;
			
			CMySize infoSize;
			this->GetSizeByGride(infoSize);
			
			if(posCellShow.x >= infoSize.iWidth)
				continue;
			if(posCellShow.y >= infoSize.iHeight)
				continue;
			
			// �޳��Ƿ�Cell						
			int nDequeIndex = posCellShow.y*m_infoSize.iWidth +posCellShow.x;
			
			if(nDequeIndex >= m_nPuzzleAmount)
				continue;
			if(nDequeIndex < 0)
				continue;
			
			unsigned short* pusIndex = m_usPuzzleIndex+nDequeIndex;

			int nIndex = (int)*pusIndex;
			
			if(nIndex == 65535)
			{
				// ͸��, ������
			}
			else
			{

				// PreLoad
				char szTitle[64];
				sprintf(szTitle, "Puzzle%d", nIndex);
				g_objGameDataSet.GetDataAni(m_szAniFile, szTitle, EXIGENCE_NORMAL, g_objGameDataSet.m_dwPuzzleLife);
			}
			
		}
	}
	
}
//------------------------------------------------
void CPuzzleBmp::SetZoomInNum(int nZoom)
{
	m_nZoomInNum = nZoom;
	m_nGrideSize = PUZZLE_GRIDE_SIZE/nZoom;
}
//------------------------------------------------
void CPuzzleBmp::Bmp2Grid(CMyPos posBmp, CMyPos& posGrid)
{
	posGrid.x = posBmp.x/m_nGrideSize;
	posGrid.y = posBmp.y/m_nGrideSize;
}
//------------------------------------------------
void CPuzzleBmp::Grid2Bmp(CMyPos posGrid, CMyPos& posBmp)
{
	posBmp.x = m_nGrideSize * posGrid.x + m_nGrideSize/2;
	posBmp.y = m_nGrideSize * posGrid.y + m_nGrideSize/2;
}
//------------------------------------------------
void CPuzzleBmp::Unit(CPuzzleBmp* pPuzzle, CMyPos posGrid)
{
        if(!pPuzzle)
                return;
        CMyPos posLayer = posGrid;
        CMySize sizeLayer;
        pPuzzle->GetSize(sizeLayer);

        CMySize sizeBmp;
        this->GetSizeByGride(sizeBmp);
        for(int i = 0; i < sizeLayer.iHeight; i++)
        {
                for(int j = 0; j < sizeLayer.iWidth; j++)
                {
                        CMyPos posLayerGrid;
                        posLayerGrid.x = posLayer.x + j;
                        posLayerGrid.y = posLayer.y + i;
                        if(posLayerGrid.x <0)
                                continue;
                        if(posLayerGrid.y <0)
                                continue;
                        if(posLayerGrid.x >= sizeBmp.iWidth)
                                continue;
                        if(posLayerGrid.y >= sizeBmp.iHeight)
                                continue;
                        if(pPuzzle->GetGrid(j,i) == 65535)
                                continue;

						unsigned short* pusIndex = m_usPuzzleIndex + posLayerGrid.y*m_infoSize.iWidth +posLayerGrid.x;
						*pusIndex = pPuzzle->GetGrid(j,i);
                }
        }
}
//------------------------------------------------
void CPuzzleBmp::Save(char* pszFile)
{
        if(!pszFile)
                return;
        FILE* fp = fopen(pszFile, "wb");
        if(!fp)
                return;
        // header..(8 bytes)
        char szHeader[8]="PUZZLE2";
        fwrite(szHeader, 1, 8, fp);

        // AniFile.. (256 bytes)
        char szAni[256];
        strcpy(szAni, this->GetAniFile());
        fwrite(szAni, 1, 256, fp);

        // Size
        CMySize infoSize;
        this->GetSizeByGride(infoSize);
        fwrite(&infoSize.iWidth, sizeof(UINT), 1, fp);
        fwrite(&infoSize.iHeight, sizeof(UINT), 1, fp);

        // Grids
/*        int nAmount = m_setAniInfo.size();
        for(int i = 0; i < nAmount; i++)
        {
                unsigned short usGrid = m_setAniInfo[i];
                fwrite(&usGrid, sizeof(unsigned short), 1, fp);
        }*/
		fwrite(m_usPuzzleIndex, sizeof(unsigned short), m_nPuzzleAmount, fp);
		fwrite(&m_nRollSpeedX, sizeof(int), 1, fp);
		fwrite(&m_nRollSpeedY, sizeof(int), 1, fp);
        fclose(fp);
        return;
}
//-------------------------------------------------------------------------------
BOOL CPuzzleBmp::TestRect(CMyRect rectInfo, BOOL bTerrain, BOOL bTransparent)
{
	// �ж��ǲ�������rectInfo���ζ������۹�
	// ����ǵķ���false
/*	if(!bTerrain)// �ر���Ƕ�Ҫ����
	{
		if(CPuzzleBmp::IsDirty(rectInfo))
			return false;
	}
*/	
	// ��rectInfo���������
	// �������ǵر�㣬���Ҳ�͸����Bufferû�����
	if(bTerrain && (!bTransparent) && (s_nRectAmount < _MAX_DIRTY_RECT))
	{
		s_setRect[s_nRectAmount] = rectInfo;
		s_nRectAmount++;
	}
	// ����true
	return true;
}
//-------------------------------------------------------------------------------
BOOL CPuzzleBmp::IsDirty(CMyRect rectInfo)
{
	// �����ֻ���˫�ر���
	// ��ֻҪ�ж�4������ ����ĸ����㶼�Ǳ����۹� return true
	// ����return false
	for(int i = 0; i < s_nRectAmount; i ++)
	{
		BOOL bCheck[4];
		CMyPos point;

		point.x = rectInfo.l;
		point.y	= rectInfo.t;
		bCheck[0] = CPhysics::IsPointInRect(point, s_setRect[i]);

		point.x = rectInfo.l;
		point.y	= rectInfo.b;
		bCheck[1] = CPhysics::IsPointInRect(point, s_setRect[i]);

		point.x = rectInfo.r;
		point.y	= rectInfo.t;
		bCheck[2] = CPhysics::IsPointInRect(point, s_setRect[i]);

		point.x = rectInfo.r;
		point.y	= rectInfo.b;
		bCheck[3] = CPhysics::IsPointInRect(point, s_setRect[i]);

		if(bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3])
			return true;
	}
	return false;
}
//-------------------------------------------------------------------------------
int  CPuzzleBmp::GetNormalGrideSize()
{
	return PUZZLE_GRIDE_SIZE;
}
//-------------------------------------------------------------------------------
void CPuzzleBmp::ReapetRateCount(DWORD& dwPicAmount, DWORD& dwGrideAmount)
{
	vector<unsigned short> m_setIndex;
	dwGrideAmount = m_infoSize.iHeight * m_infoSize.iWidth;
	for(int i = 0; i < m_infoSize.iWidth; i ++)
	{
		for(int j = 0; j < m_infoSize.iHeight; j ++)
		{
			unsigned short usIndex = this->GetGrid(i, j);
			int nAmount = m_setIndex.size();
			for(int k = 0; k < nAmount; k ++)
			{
				if(m_setIndex[k] == usIndex)
					break;
			}
			if(k == nAmount)
			{
				m_setIndex.push_back(usIndex);
			}
		}
	}
	dwPicAmount = m_setIndex.size();
}
//-------------------------------------------------------------------------------
void CPuzzleBmp::GenerateAni(const char* pszAniFile)
{
	if(!pszAniFile)
		return;
	FILE* fp = fopen(pszAniFile, "w");
	if(!fp)
		return;
	vector<unsigned short> m_setIndex;
	for(int i = 0; i < m_infoSize.iWidth; i ++)
	{
		for(int j = 0; j < m_infoSize.iHeight; j ++)
		{
			unsigned short usIndex = this->GetGrid(i, j);
			int nAmount = m_setIndex.size();
			for(int k = 0; k < nAmount; k ++)
			{
				if(m_setIndex[k] == usIndex)
					break;
			}
			if(k == nAmount)
			{
				m_setIndex.push_back(usIndex);
			}
		}
	}
	
	for(int l = 0; l < m_setIndex.size(); l ++)
	{
		char szTitle[64];
		sprintf(szTitle, "Puzzle%d", m_setIndex[l]);
		
	}
	fclose(fp);
}
//-------------------------------------------------------------------------------
