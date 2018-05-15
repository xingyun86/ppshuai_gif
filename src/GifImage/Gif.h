// Gif.h: interface for the CGif class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIF_H__3F3EB142_198E_11D3_ABDA_0000E81A9AA8__INCLUDED_)
#define AFX_GIF_H__3F3EB142_198E_11D3_ABDA_0000E81A9AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//-----------start define
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

typedef unsigned char UCHAR;
typedef UCHAR *   LPUSTR;
typedef unsigned short USHORT;
class GIFINFO
{
public:
	USHORT FileType;//89a or 87a 
	USHORT ColorType;//1,2,4,8,16,32,64,128,256
	USHORT ColorMode;//1,2,3,4,5,6,7,8
	USHORT Width;
	USHORT Height;
	USHORT FrameCount;//�@���X�T��	//UINT           DataOffset[100];//�p��FrameCount���� ,�]�A�ɥR�Ϥμƾڰ�
	UCHAR  InitPixelBits;//���Y�ƾڰ_�l�ƾ�Bits���
};

class MYRGB
{
public:
	BYTE bRed;
	BYTE bGreen;
	BYTE bBlue;
};
class BMPIMAGE
{
public:
	BMPIMAGE();
	virtual ~BMPIMAGE();
	short tColor;
	USHORT DelayTime;
	USHORT Left;
	USHORT Top;
	USHORT Width;
	USHORT Height;
	RGBQUAD		   Palette[256];	
    LPUSTR         pImageData;
	BOOL   SaveMode;//1 = normal; 0 = ��e
};
//------------------------------------------------------				
class GIFHEADER//GIF ����Y
{
public:
	UCHAR Signature[6];//�Ϲ��榡�A����
	USHORT ScreenWidth;//�Ϲ��e��
	USHORT ScreenDepth;//�Ϲ�����
	UCHAR GlobalFlagByte;//�����аO a0 -- a7 ���t�N
	UCHAR BackGroundColor;//�I����
	UCHAR AspectRadio;//89a�������e��
};

class IMAGEDATAINFO//�Ϲ��ƾڰ��ѧO�H��
{
public:
	UCHAR ImageLabel;// default 0x2c
	USHORT ImageLeft; 
	USHORT  ImageTop;
	USHORT  ImageWidth;
	USHORT  ImageHeight;
	UCHAR  LocalFlagByte; 
};

class LZWTABLE
{
public:
	USHORT Header;
	USHORT Tail;
	USHORT Code; 
};


//below only for 89a
class GRAPHCTRL
{
public:
	UCHAR ExtIntr;// 0x21	
	UCHAR Label;//0xF9
	UCHAR BlockSize;//0x04
	UCHAR PackedField;
	USHORT          DelayTime;
	UCHAR TranColorIndex;
	UCHAR blockTerminator;//0x00
};
class NOTEHCTRL
{
public:
	UCHAR ExtIntr;// 0x21	
	UCHAR Label;//0xFE
	UCHAR Data[256];//�ܪ��̤j256
	UCHAR blockTerminator;//0x00
};
class TEXTCTRL
{
public:	
	UCHAR ExtIntr;// 0x21	
	UCHAR Label;//0x01
	UCHAR BlockSize;//0x0c
	USHORT          Left;
	USHORT          Top;
	USHORT          Width;
	USHORT          Height; 
	UCHAR ForeColorIndex;
	UCHAR BkColorIndex;
	char		  Data[256];//�ܪ��̤j256
	UCHAR blockTerminator;//0x00
};
class APPCTRL
{
public:
	UCHAR ExtIntr;// 0x21	
	UCHAR Label;//0xFF
	UCHAR BlockSize;//0x0b
	UCHAR Identifier[8];
	UCHAR Authentication[3];
	UCHAR Data[256];//�ܪ��̤j256
	UCHAR blockTerminator;//0x00
};
//-----------------------------

class CGIF  
{
public:
	BOOL GetImageInfo(RECT &Rect,COLORREF &tColor ,UINT ImageNo = 0);
	BOOL ShowImage(HDC hDC,POINT StartPos,UINT ImageNo = 0);
	BOOL LoadGIF(LPCTSTR GifFileName);
	CGIF();
	virtual ~CGIF();

private:
	BOOL ConvertToBmpImage(LPUSTR SrcData);
	BOOL SaveBmp(LPCTSTR BmpFileName,LPUSTR pData);
	UINT GetImage(LPUSTR pData);
	UINT GetNoteContent(LPUSTR pNote);
	UINT GetAppContent(LPUSTR pApp);
	UINT ShowText(LPUSTR pText);
	UINT GetGrphContent(LPUSTR pGrCtrl);
	UINT AnalizeFileHeader(LPUSTR pFileContent);
	//�q�r�Ŧꤤ���N�r�`���Y��Bits�}�l���Y�zbits,�ê�^���G
	USHORT GetOneCode(LPUSTR CodeStr ,UINT CodeStrLen, UINT OffsetChar , UINT OffsetBits, UINT Length);
	//��Y���w���V������Y�ƾګe��m��,���o��e�ƾڰϤ����Y�ƾکҦ��r�`��
	UINT GetCodeCountOnChar (LPUSTR CodeStr ,UINT &AllDataLen);
	//��Y���w���V������Y�ƾګe��m��,���o��e�ƾڰϤ����Y�ƾ�
	LPUSTR GetCodeDataOnChar (LPUSTR CodeStr);
	//�����Y�ƾڸѩ�USHORT * ��,
	LPUSTR GetCodeDataOnBits (LPUSTR CodeDataStr,UINT InitLen ,UINT &CodeDataLen);
	//�o�쳡���u��ƾ�
	void  GetPartImageDataFromTable(LPUSTR &pImage,LZWTABLE * Table,UINT TableLen);
	//API end

	
	GIFINFO m_GifInfo;
	LPUSTR   m_pDataArea;
	LZWTABLE LZWTable[5200];
	
	CPtrList m_ImageList;

	RGBQUAD m_CurRgbQuad[256];//Bitmap pal;
	short   m_CurTColorIndex;
	USHORT  m_CurDelayTime;
	BOOL    m_CurSaveMode;
	USHORT  m_CurX,m_CurY,m_CurWidth,m_CurHeight;
};


BOOL BitBltEx(
  HDC hdcDest, // handle to destination device context
  int nXDest,  // x-coordinate of destination rectangle's upper-left 
               // corner
  int nYDest,  // y-coordinate of destination rectangle's upper-left 
               // corner
  int nWidth,  // width of destination rectangle
  int nHeight, // height of destination rectangle
  HDC hdcSrc,  // handle to source device context
  int nXSrc,   // x-coordinate of source rectangle's upper-left 
               // corner
  int nYSrc,   // y-coordinate of source rectangle's upper-left 
  COLORREF cTransparentColor      // corner
   // raster operation code
);

#endif // !defined(AFX_GIF_H__3F3EB142_198E_11D3_ABDA_0000E81A9AA8__INCLUDED_)
