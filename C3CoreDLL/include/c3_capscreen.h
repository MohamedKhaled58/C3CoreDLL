#ifndef _c3_capscreen_h_
#define _c3_capscreen_h_

#include "c3_common.h"
#include "c3_main.h"
#include "ijl.h"

C3_CORE_DLL_API
void CapScreen ( char *lpName );

/* �� 24 λͼ����벢����Ϊ JPG �ļ� */

BOOL JPGEncode ( char *lpJpegName,
				 DWORD dwWidth,
				 DWORD dwHeight, 
				 unsigned char *lpBuffer,
				 IJL_COLOR mode = IJL_RGB,	// IJL_BGR
				 DWORD dwQuality = 100 );

#endif