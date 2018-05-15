// GifPic.cpp: implementation of the CGifPic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GifPic.h"
#include "gif.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGifPic::CGifPic()
{
	pGif = NULL;
}

CGifPic::~CGifPic()
{
	if (pGif) delete pGif;
}

BOOL CGifPic::LoadGIF(LPCTSTR FileName)
{
	if (pGif) delete pGif;
	pGif = new CGIF;
	if (pGif->LoadGIF (FileName)) return 1;
	delete pGif;
	pGif = NULL;
	return 0;
}

BOOL CGifPic::GetImageInfo(RECT &Rect, COLORREF &tColor, UINT ImageNo)
{
	if (pGif)
	{
		if (pGif->GetImageInfo (Rect,tColor,ImageNo)) return 1;
	}
	return 0;
}

BOOL CGifPic::ShowImage(HDC hDC,POINT StartPos,UINT ImageNo )
{
	if (pGif)
	{
		if (pGif->ShowImage (hDC,StartPos,ImageNo)) return 1;
	}
	return 0;
}
