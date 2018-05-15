// ShowGifDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowGif.h"
#include "ShowGifDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Structure define
#include "math.h"

/////////////////////////////////////////////////////////////////////////////
// CShowGifDlg dialog

CShowGifDlg::CShowGifDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowGifDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowGifDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowGifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowGifDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowGifDlg, CDialog)
	//{{AFX_MSG_MAP(CShowGifDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowGifDlg message handlers

BOOL CShowGifDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowGifDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowGifDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CShowGifDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	char Path[256];
	GetCurrentDirectory(256,Path);
	strcat(Path,"\\*.Gif");
	CFileDialog dlg(TRUE,"*.gif",Path,NULL, "gif file(*.gif)|*.gif||");
	DWORD dw = GetLastError();
	CString szFilePath;
	if ( dlg.DoModal() == IDOK )
	{
		szFilePath = dlg.GetPathName();
		m_Gif.LoadGIF (szFilePath);	
		CDC * pDC = GetDC();
		
		HDC hMemDC = ::CreateCompatibleDC(pDC->m_hDC);
		HBITMAP hBmp = (HBITMAP)::CreateCompatibleBitmap(pDC->m_hDC ,800,600);
		HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hBmp);
		::BitBlt (hMemDC,0,0,800,600,pDC->m_hDC,0,0,SRCCOPY);

		HDC hMemDC1 = ::CreateCompatibleDC(pDC->m_hDC);
		HBITMAP hBmp1 = (HBITMAP)::CreateCompatibleBitmap(pDC->m_hDC ,800,600);
		HBITMAP hOldBmp1 = (HBITMAP)::SelectObject(hMemDC1,hBmp1);
		::BitBlt (hMemDC1,0,0,800,600,pDC->m_hDC,0,0,SRCCOPY);

		CPoint pt(30,30);
		int i = 0;
		int k = 0;
		MSG msg;
		CRect Rect;
		COLORREF tColor;
		while (1)
		{
			if (!m_Gif.ShowImage (hMemDC1,pt,i++))
			{
				i = 0;
				m_Gif.ShowImage (hMemDC1,pt,i++);
				k++;
				if (k > 10) break;
			}
			if (m_Gif.GetImageInfo (Rect,tColor,i-1))
			{
				::BitBlt (pDC->m_hDC ,0,0,Rect.Width ()+pt.x + 50,Rect.Height ()+pt.y + 50,hMemDC1,0,0,SRCCOPY);
				::BitBlt (hMemDC1,0,0,Rect.Width ()+pt.x + 50,Rect.Height ()+pt.y+50,hMemDC,0,0,SRCCOPY);
			}
			else
			{
				::BitBlt (pDC->m_hDC ,0,0,800,600,hMemDC1,0,0,SRCCOPY);
				::BitBlt (hMemDC1,0,0,800,600,hMemDC,0,0,SRCCOPY);
			}
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			Sleep(100);
			if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			
		}
		ReleaseDC(pDC);
		::SelectObject(hMemDC,hOldBmp);
		::DeleteObject(hBmp);
		::DeleteDC(hMemDC);
		::SelectObject(hMemDC1,hOldBmp1);
		::DeleteObject(hBmp1);
		::DeleteDC(hMemDC1);
	}

}
