// ShowGifDlg.h : header file
//

#if !defined(AFX_SHOWGIFDLG_H__9EB65268_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_)
#define AFX_SHOWGIFDLG_H__9EB65268_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShowGifDlg dialog
#include "..\GIFPIC.h"

class CShowGifDlg : public CDialog
{
// Construction
public:
	CShowGifDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShowGifDlg)
	enum { IDD = IDD_SHOWGIF_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowGifDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShowGifDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGifPic m_Gif;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWGIFDLG_H__9EB65268_12AC_11D3_ABD9_0000E81A9AA8__INCLUDED_)
