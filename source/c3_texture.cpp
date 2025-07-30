#pragma warning(disable:4786)
#include "..\include\c3_texture.h"
#include "..\include\c3_main.h"
#include "..\include\c3_datafile.h"
#include "..\include\DnFile.h"

C3_CORE_DLL_API DWORD		g_dwTexCount = 0;
C3_CORE_DLL_API C3Texture	*g_lpTex[TEX_MAX];

C3_CORE_DLL_API
void Texture_Clear ( C3Texture *lpTex )
{
	lpTex->nID = -1;
	lpTex->nDupCount = 0;
	lpTex->lpName = 0;
	lpTex->lpTex = 0;
	ZeroMemory ( &lpTex->Info, sizeof ( D3DXIMAGE_INFO ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load texture from a WFile file name
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
C3_CORE_DLL_API
int Texture_Load ( C3Texture **lpTex,
				   char *lpName,
				   DWORD dwMipLevels,
				   D3DPOOL pool,
				   BOOL bDuplicate,
				   D3DCOLOR colorkey )
{
	EnterCriticalSection ( &g_CriticalSection );

	if ( bDuplicate )
	{
		// �����Ѱ������ͬ����ͼ�Ѿ������ڴ��򴫵�ָ��
		DWORD add = 0;
		for ( int t = 0; t < TEX_MAX; t++ )
		{
			if ( 0 != g_lpTex[t] )
			{
				if ( stricmp ( g_lpTex[t]->lpName, lpName ) == 0 )
				{
					g_lpTex[t]->nDupCount++;
					*lpTex = g_lpTex[t];

					LeaveCriticalSection ( &g_CriticalSection );
					return t;
				}
				if ( ++add == g_dwTexCount )
					break;
			}
		}
	}
	
	// ���ļ�������ͼ
	*lpTex = new C3Texture;
	Texture_Clear ( *lpTex );
	g_objDnFile.BeforeUseDnFile();
	DWORD dwSize = 0;
	void* pBuf = g_objDnFile.GetMPtr(lpName, dwSize);

	if (pBuf)
	{
		if ( FAILED ( D3DXCreateTextureFromFileInMemoryEx ( g_D3DDevice,
															pBuf,
															dwSize,
															D3DX_DEFAULT,
															D3DX_DEFAULT,
															dwMipLevels,
															0,
															D3DFMT_UNKNOWN,
															pool,
															D3DX_FILTER_LINEAR,
															D3DX_FILTER_LINEAR,
															colorkey,
															&( *lpTex )->Info,
															NULL,
															&( *lpTex )->lpTex ) ) )
		{
			LeaveCriticalSection ( &g_CriticalSection );

			//free (pBuf);
			g_objDnFile.AfterUseDnFile();
			return -1;
		}
		g_objDnFile.AfterUseDnFile();
		D3DSURFACE_DESC desc;
		( *lpTex )->lpTex->GetLevelDesc ( 0, &desc );
		( *lpTex )->Info.Format = desc.Format;

		( *lpTex )->lpName = new char[strlen ( lpName ) + 1];
		strcpy ( ( *lpTex )->lpName, lpName );

		( *lpTex )->nDupCount = 1;

		for ( int t = 0; t < TEX_MAX; t++ )
		{
			if ( g_lpTex[t] == 0 )
			{
				g_lpTex[t] = *lpTex;
				g_lpTex[t]->nID = t;
				LeaveCriticalSection ( &g_CriticalSection );
				return t;
			}
		}
	}
	// end while the file name is the WFile name
	else
	// begin while the file name is the really file name
	{
		g_objDnFile.AfterUseDnFile();

		if ( FAILED ( D3DXCreateTextureFromFileEx ( g_D3DDevice,
													lpName,
													D3DX_DEFAULT,
													D3DX_DEFAULT,
													dwMipLevels,
													0,
													D3DFMT_UNKNOWN,
													pool,
													D3DX_FILTER_LINEAR,
													D3DX_FILTER_LINEAR,
													colorkey,
													&( *lpTex )->Info,
													NULL,
													&( *lpTex )->lpTex ) ) )
		{
			LeaveCriticalSection ( &g_CriticalSection );
			return -1;
		}

		D3DSURFACE_DESC desc;
		( *lpTex )->lpTex->GetLevelDesc ( 0, &desc );
		( *lpTex )->Info.Format = desc.Format;

		( *lpTex )->lpName = new char[strlen ( lpName ) + 1];
		strcpy ( ( *lpTex )->lpName, lpName );

		( *lpTex )->nDupCount = 1;

		for ( int t = 0; t < TEX_MAX; t++ )
		{
			if ( g_lpTex[t] == 0 )
			{
				g_lpTex[t] = *lpTex;
				g_lpTex[t]->nID = t;
				LeaveCriticalSection ( &g_CriticalSection );
				return t;
			}
		}
	}
	// end while the file name is the really file name
	LeaveCriticalSection ( &g_CriticalSection );
	return -1;
}

C3_CORE_DLL_API
void Texture_Unload ( C3Texture **lpTex )
{
	EnterCriticalSection ( &g_CriticalSection );	

	if ( --( *lpTex )->nDupCount <= 0 )
	{
		int id = ( *lpTex )->nID;

		SafeDeleteEx ( ( *lpTex )->lpName );
		SafeRelease ( ( *lpTex )->lpTex );
		SafeDelete ( *lpTex );

		g_lpTex[id] = 0;
	}

	LeaveCriticalSection ( &g_CriticalSection );
}
C3_CORE_DLL_API
BOOL Texture_Update ( C3Texture *lpSrcTex, C3Texture *lpDestTex )
{
	if ( FAILED ( g_D3DDevice->UpdateTexture ( lpSrcTex->lpTex, lpDestTex->lpTex ) ) )
		return false;
	return true;
}
C3_CORE_DLL_API
BOOL Texture_Create ( C3Texture **lpTex,
					  DWORD dwWidth,
					  DWORD dwHeight,
					  DWORD dwMipLevels,
					  D3DFORMAT format,
					  D3DPOOL pool )
{
	*lpTex = new C3Texture;
	Texture_Clear ( *lpTex );

	if ( FAILED ( D3DXCreateTexture ( g_D3DDevice,
									  dwWidth,
									  dwHeight,
									  dwMipLevels,
									  0,
									  format,
									  pool,
									  &( *lpTex )->lpTex ) ) )
		return false;

	( *lpTex )->Info.Width = dwWidth;
	( *lpTex )->Info.Height = dwHeight;
	( *lpTex )->Info.Format = format;

	return true;
}
