// GifPic.h: interface for the CGifPic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFPIC_H__E2B19650_1D98_11D3_ABDA_0000E81A9AA8__INCLUDED_)
#define AFX_GIFPIC_H__E2B19650_1D98_11D3_ABDA_0000E81A9AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGIF;

class AFX_EXT_CLASS CGifPic  
{
public:
	BOOL ShowImage(HDC hDC,POINT StartPos,UINT ImageNo = 0);
	BOOL GetImageInfo(RECT &Rect,COLORREF &tColor,UINT ImageNo);
	BOOL LoadGIF(LPCTSTR FileName);
	CGifPic();
	virtual ~CGifPic();
private:
	CGIF * pGif;
};

#endif // !defined(AFX_GIFPIC_H__E2B19650_1D98_11D3_ABDA_0000E81A9AA8__INCLUDED_)
