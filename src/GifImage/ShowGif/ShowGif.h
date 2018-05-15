// ShowGif.h : main header file for the SHOWGIF application
//

#if !defined(AFX_SHOWGIF_H__9EB65266_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_)
#define AFX_SHOWGIF_H__9EB65266_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowGifApp:
// See ShowGif.cpp for the implementation of this class
//

class CShowGifApp : public CWinApp
{
public:
	CShowGifApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowGifApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShowGifApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWGIF_H__9EB65266_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_)
