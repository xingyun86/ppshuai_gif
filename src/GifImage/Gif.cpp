// Gif.cpp: implementation of the CGif class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GIF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BMPIMAGE::BMPIMAGE()
{
	pImageData = NULL;
}

BMPIMAGE::~BMPIMAGE()
{
	if (pImageData) GlobalFree(pImageData);
}




//

CGIF::CGIF()
{

}

CGIF::~CGIF()
{
	BMPIMAGE * pBmpImage;
	while (!m_ImageList.IsEmpty ())
	{
		pBmpImage = (BMPIMAGE *) m_ImageList.GetTail ();
		m_ImageList.RemoveTail ();
		delete pBmpImage;
	}
}

BOOL CGIF::LoadGIF(LPCTSTR GifFileName)
{
	//將文件內容考到內存中,pFileContent;
	CFile file;
	if (!file.Open (GifFileName,CFile::modeRead | CFile::typeBinary )) return 0;
	LPUSTR pFileContent = (LPUSTR)GlobalAlloc(GPTR,file.GetLength() + 1);
	file.Read (pFileContent,file.GetLength ());
	file.Close ();
	
	//Clear 
	BMPIMAGE * pBmpImage;
	while (!m_ImageList.IsEmpty ())
	{
		pBmpImage = (BMPIMAGE *) m_ImageList.GetTail ();
		m_ImageList.RemoveTail ();
		delete pBmpImage;
	}
	//
	//得到有用信息	
	UINT HeaderSize = AnalizeFileHeader(pFileContent);
	/*
	if (m_GifInfo.ColorMode == 1)
	{
		GlobalFree(pFileContent);
		return 0;
	}
	*/
	m_pDataArea = pFileContent + HeaderSize;

	//
	m_CurTColorIndex = -1;
	m_CurDelayTime = 0;
	
	LPUSTR p = m_pDataArea;
	UINT  Offset;
	while (1)
	{
		if (p[0] == 0x21 && p[1] == 0xf9 && p[2] == 0x04)
		{//圖形補充區
			Offset = GetGrphContent(p);
			p += Offset;
		}
		else if (p[0] == 0x21 && p[1] == 0x01 && p[2] == 0x0c)
		{//文字補充區
			Offset = ShowText(p);
			p += Offset;
		}
		else if (p[0] == 0x21 && p[1] == 0xff && p[2] == 0x0b)
		{//應用塊
			Offset = GetAppContent(p);
			p += Offset;
		}
		else if (p[0] == 0x21 && p[1] == 0xfe)
		{//註解區
		   Offset = GetNoteContent(p);
		   p += Offset;	
		}
		else if (p[0] == 0x2c)
		{//數據塊
		   Offset = GetImage(p);
		   p += Offset;	
		}
		else break;
	}
	GlobalFree(pFileContent);

	return 1;
}

UINT  CGIF::AnalizeFileHeader(LPUSTR pFileContent)
{

	// GIF File Header
	GIFHEADER gifHeader;//文件頭
	memcpy(&gifHeader,pFileContent,sizeof(GIFHEADER));
	m_GifInfo.Width = gifHeader.ScreenWidth ;
	m_GifInfo.Height = gifHeader.ScreenDepth ;
	//Analize Header
	//char radio = (gifHeader.AspectRadio +15)/64;//保留
	
	//得到調色板大小
	m_GifInfo.ColorMode  = (gifHeader.GlobalFlagByte & 0x07) + 1;//顏色模式 1,2,3,4,5,6,7,8
	//單個壓縮數據初始位數
	m_GifInfo.InitPixelBits = m_GifInfo.ColorMode + 1;
	m_GifInfo.ColorType = 1;
	switch (m_GifInfo.ColorMode)
	{
		case 1:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 1;
			break;
		case 2:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 2;
			break;
		case 3:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 3;
			break;
		case 4:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 4;
			break;
		case 5:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 5;
			break;
		case 6:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 6;
			break;
		case 7:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 7;
			break;
		case 8:
			m_GifInfo.ColorType = m_GifInfo.ColorType << 8;
			break;
	}
	//end

	if (gifHeader.GlobalFlagByte & 0x80) //AfxMessageBox("有通用調色板數據!");
	{ 
		
		//read pal data and save it to BitMap pal
		LPUSTR p = pFileContent + sizeof(GIFHEADER);	
		MYRGB * pRGB = (MYRGB *)p;
		for (UINT j = 0; j < m_GifInfo.ColorType ; j ++)
		{
			m_CurRgbQuad[j].rgbRed       = pRGB->bRed;
			m_CurRgbQuad[j].rgbGreen     = pRGB->bGreen;
			m_CurRgbQuad[j].rgbBlue      = pRGB->bBlue;
			m_CurRgbQuad[j].rgbReserved  = 0;
			pRGB++;
		}
		p += 3 * m_GifInfo.ColorType;//pass pal
		return  sizeof(GIFHEADER)+ 3 * m_GifInfo.ColorType;
	}
	
	return sizeof(GIFHEADER);
}
//處理圖形控制補充區
UINT CGIF::GetGrphContent(LPUSTR pGrCtrl)
{
	GRAPHCTRL GraphCtrl;
	memcpy(&GraphCtrl,pGrCtrl,sizeof(GRAPHCTRL));
	USHORT Flag = GraphCtrl.PackedField;
	//保留 Flag = (Flag & 0x1c)>>2;//get 2,3,4 bits
	m_CurTColorIndex = -1;
	m_CurDelayTime = 0;
	
	if (Flag & 1)
	{
		m_CurTColorIndex = GraphCtrl.TranColorIndex ;
	}
	if (Flag & 2)
	{
		m_CurDelayTime = GraphCtrl.DelayTime ;
	}
	return sizeof(GRAPHCTRL);
}
//處理文字補充區
UINT CGIF::ShowText(LPUSTR pText)
{
	TEXTCTRL TextCtrl;
	memcpy(&TextCtrl,pText,sizeof(TEXTCTRL));
	return sizeof(TEXTCTRL)+TextCtrl.Data [0] - 256 + 1;
}
//處理應用補充區
UINT CGIF::GetAppContent(LPUSTR pApp)
{
	APPCTRL AppCtrl;
	memcpy(&AppCtrl,pApp,sizeof(APPCTRL));
	return sizeof(APPCTRL)+AppCtrl.Data [0] - 256 + 1;
}
//處理附註補充區
UINT CGIF::GetNoteContent(LPUSTR pNote)
{
	NOTEHCTRL NoteCtrl;
	memcpy(&NoteCtrl,pNote,sizeof(NOTEHCTRL));
	return sizeof(NOTEHCTRL)+NoteCtrl.Data[0] - 256 + 1;
}

UINT CGIF::GetImage(LPUSTR pData)
{
	IMAGEDATAINFO ImageData;
	memcpy(&ImageData,pData,sizeof(IMAGEDATAINFO));
	LPUSTR p = pData + sizeof(IMAGEDATAINFO);
	UINT PalSize = 0;
	m_CurSaveMode = 0;
	m_CurX = ImageData.ImageLeft;
	m_CurY = ImageData.ImageTop ;
	m_CurWidth = ImageData.ImageWidth ;
	m_CurHeight = ImageData.ImageHeight;
	if (ImageData.LocalFlagByte  & 0x80) //AfxMessageBox("有局部調色板數據!");
	{ 
		MYRGB * pRGB = (MYRGB *)p;
		for (UINT j = 0; j < m_GifInfo.ColorType ; j ++)
		{
			m_CurRgbQuad[j].rgbRed       = pRGB->bRed;
			m_CurRgbQuad[j].rgbGreen     = pRGB->bGreen;
			m_CurRgbQuad[j].rgbBlue      = pRGB->bBlue;
			m_CurRgbQuad[j].rgbReserved  = 0;
			pRGB++;
		}
		p += 3 * m_GifInfo.ColorType;//pass pal
		PalSize = 3 * m_GifInfo.ColorType;
	}	
	else if (ImageData.LocalFlagByte  & 0x40)
	{
		m_CurSaveMode = 1;
	}
	UINT InitBits = *p++;//跳過第一字節，進入真正的段落 ;
	
	UINT offset;
	UINT dataCount = GetCodeCountOnChar(p,offset);//得到當前區數據總數
	LPUSTR pCodeData = GetCodeDataOnChar(p);//得到當前區數據內容
	//提取真實數據,所有數據存為字符大小
	LPUSTR pTrueCodeData = GetCodeDataOnBits (pCodeData,m_GifInfo.InitPixelBits,dataCount);	
	ConvertToBmpImage(pTrueCodeData);
	GlobalFree(pCodeData);
	GlobalFree(pTrueCodeData);
	return sizeof(IMAGEDATAINFO) + offset + PalSize;
}

USHORT CGIF::GetOneCode(LPUSTR CodeStr ,UINT CodeStrLen, UINT OffsetChar , UINT OffsetBits, UINT Length)
{
	ASSERT (Length <= 12);
	
	
	UCHAR *pValue,*lp = (UCHAR*)CodeStr;
	
	UINT value = 0;
	pValue = (UCHAR *)&value;
	pValue[0] = lp[OffsetChar+0];
	if (OffsetChar + 1 < CodeStrLen)
		pValue[1] = lp[OffsetChar+1];
	if (OffsetChar + 2 < CodeStrLen)
		pValue[2] = lp[OffsetChar+2];
	if (OffsetChar + 3 < CodeStrLen)
		pValue[3] = lp[OffsetChar+3];

	value = value >> OffsetBits;
	value = value << (32 - Length);
	value = value >> (32 - Length);
	return (USHORT)value;
}
UINT CGIF::GetCodeCountOnChar (LPUSTR CodeDataStr,UINT &AllDataLen)
{
	UINT dataCount = 0;
	UCHAR dataLen;
	LPUSTR p1 = CodeDataStr;
	AllDataLen = 0;
	while (1)
	{
		dataLen = *p1 ++;
		p1 += dataLen;
		dataCount += dataLen;
		AllDataLen += (dataLen + 1);
		if (dataLen == 0x00) break;
	}
	AllDataLen ++;
	return dataCount;
}

LPUSTR CGIF::GetCodeDataOnChar (LPUSTR CodeDataStr)
{
	UINT offset;
	UINT dataCount = GetCodeCountOnChar(CodeDataStr,offset);
	LPUSTR pData,p2;
	pData = (LPUSTR)GlobalAlloc (GPTR,dataCount+1);
	p2 = pData;
	UCHAR dataLen;
	LPUSTR p1 = CodeDataStr;
	while (1)
	{
		dataLen = *p1 ++;
		if (dataLen == 0x00) 
			break;
		memcpy(p2,p1,dataLen);
		p1 += dataLen;
		p2 += dataLen;
		dataCount += dataLen;
	}
	return pData;
}

LPUSTR  CGIF::GetCodeDataOnBits (LPUSTR CodeDataStr ,UINT InitLen ,UINT &CodeDataLen)
{
	LPUSTR p = CodeDataStr;
	LPUSTR pData = (LPUSTR ) GlobalAlloc (GPTR ,m_CurWidth*m_CurHeight*2);
	LPUSTR pTrueData = pData;
	
	int i = 0;
	UINT BitsCount = 0;
	USHORT TCode,s = m_GifInfo.ColorType + 2;//起始的代碼值
	UINT TableLen,iLen = InitLen;
	UINT Pos,index,j = 0;
	UINT SrcCodeLEN = CodeDataLen;
	while (1)
	{
		TCode = GetOneCode(p ,CodeDataLen,BitsCount / 8, BitsCount % 8, iLen);		
		BitsCount += iLen;

		if (TCode < m_GifInfo.ColorType)
		{
			LZWTable[j].Header = TCode;
			LZWTable[j].Code   = s ++;
			if (j != 0)
			{
				LZWTable[j - 1].Tail = TCode;
			}
			j++;
		}
		else if (TCode > m_GifInfo.ColorType + 1)//為代碼
		{
			if (j == 0) continue;
			LZWTable[j].Header = TCode;
			LZWTable[j].Code   = s ++;
			ASSERT( LZWTable[j].Header < LZWTable[j].Code);
			index = j - 1;
			Pos = j;
		//	TRACE("BitsCount = %d\n",BitsCount);
	//		afxDump<<"BitsCount = %d"<<BitsCount;
			while (1)
			{
				Pos = LZWTable[Pos].Header - (m_GifInfo.ColorType + 2) ;
				if (LZWTable[Pos].Header < m_GifInfo.ColorType) 
					break;
			}
			LZWTable[index].Tail  = LZWTable[Pos].Header;
			j++;	
		}
		else if (TCode == m_GifInfo.ColorType)//清除碼
		{
			iLen = InitLen;
			TableLen = j;
			j = 0;
			GetPartImageDataFromTable(pData,LZWTable,TableLen);
			//pData+=TableLen;
			s = m_GifInfo.ColorType + 2 ;
		}
		else if (TCode == m_GifInfo.ColorType + 1) //結束碼
		{
			//end build table
			iLen = InitLen;
			TableLen = j;
			GetPartImageDataFromTable(pData,LZWTable,TableLen);
			//pData+=TableLen;
			s = m_GifInfo.ColorType + 2;
			break;
		}
		if (s == 3)
			iLen = 2;
		else if (s == 5)
			iLen = 3;
		else if (s == 9)
			iLen = 4;
		else if (s == 17)
			iLen = 5;
		else if (s == 33)
			iLen = 6;
		else if (s == 65)
			iLen = 7;
		else if (s == 129)
			iLen  = 8;
		else if (s == 257)
			iLen  = 9;
		else if ( s == 513 ) 
			iLen = 10;
		else if (s == 1025 ) 
			iLen = 11;
		else if (s == 2049 ) 
			iLen = 12;
		
		if (BitsCount / 8 > SrcCodeLEN)
		{
			iLen = InitLen;
			TableLen = j;
			GetPartImageDataFromTable(pData,LZWTable,TableLen);
			//pData+=TableLen;
			s = m_GifInfo.ColorType + 2;
			break;
		}
		
	}
	CodeDataLen = BitsCount / 8;
	
	return pTrueData;
}

void  CGIF::GetPartImageDataFromTable(LPUSTR &pImage,LZWTABLE * Table,UINT TableLen)
{
	UINT i;
	LPUSTR p = pImage;
	USHORT *TailStack = new USHORT[5200];
	int j;
	int sp;
	for (i = 0 ; i < TableLen; i++)
	{
		if (Table[i].Header < m_GifInfo.ColorType)
		{
			*p++ = (UCHAR)Table[i].Header ;
		}
		else
		{
			sp = 0;
			j = Table[i].Header - (m_GifInfo.ColorType + 2);
			while (Table[j].Header > m_GifInfo.ColorType + 1)
			{
				TailStack[sp++] = Table[j].Tail ;
				j = Table[j].Header;
				j -= (m_GifInfo.ColorType + 2);
				ASSERT(sp < 5200);
			}
			*p++ = (UCHAR)Table[j].Header;
			*p++ = (UCHAR)Table[j].Tail;
			sp --;
			while (sp >= 0)
			{
				*p++ = (UCHAR)TailStack[sp--];
			}
			
		}
	
	}
	int len = p - pImage;
	pImage = p;
	
	delete []TailStack;
}


BOOL CGIF::SaveBmp(LPCTSTR BmpFileName,LPUSTR pData)
{
	BITMAPINFOHEADER BmpInfoHeader;
	BITMAPFILEHEADER BmpFileHeader;
	BmpFileHeader.bfType = 0x4d42;
	BmpFileHeader.bfSize = m_GifInfo.Width*m_GifInfo.Height ;
	BmpFileHeader.bfReserved1 = 0;
	BmpFileHeader.bfReserved2 = 0;
	BmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 4 * m_GifInfo.ColorType;

	BmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	BmpInfoHeader.biWidth = m_CurWidth;
	BmpInfoHeader.biHeight = m_CurHeight ;
	BmpInfoHeader.biPlanes = 1;
	BmpInfoHeader.biBitCount = 8;
	BmpInfoHeader.biCompression = BI_RGB;
	BmpInfoHeader.biSizeImage = 0;
	BmpInfoHeader.biXPelsPerMeter = 0;
	BmpInfoHeader.biYPelsPerMeter = 0;
	BmpInfoHeader.biClrUsed = 0;
	BmpInfoHeader.biClrImportant = 0;


	CFile newFile("1.bmp",CFile::typeBinary|CFile::modeWrite|CFile::modeCreate);
	newFile.Write(&BmpFileHeader,sizeof(BITMAPFILEHEADER));
	newFile.Write(&BmpInfoHeader,sizeof(BITMAPINFOHEADER));
	newFile.Write(&m_CurRgbQuad,sizeof(RGBQUAD)*256);
	USHORT TrueWidth = WIDTHBYTES(m_CurWidth * 8);
	newFile.Write(pData,TrueWidth*m_CurHeight);
	newFile.Close ();
	return 1;
}

BOOL CGIF::ConvertToBmpImage(LPUSTR SrcData)
{
	
	LPUSTR pSrcData = SrcData;
	
	UINT i,j,k,Step;
	if (m_CurSaveMode )//交叉存處
	{
		LPUSTR p2 = (LPUSTR)GlobalAlloc(GPTR,m_CurWidth*m_CurHeight);
		LPUSTR pTmp = p2;
		
		k = 0; Step = 8;
		for (j = 0; j < m_CurHeight  ; j ++)
		{
			memcpy(pTmp+k*m_CurWidth,pSrcData+j*m_CurWidth,m_CurWidth);
			k += Step;
			if (k >= m_CurHeight) break;
		}
		j++;//每行中存了一個越界值
		k = 4; Step = 8;
		for (; j < m_CurHeight  ; j ++)
		{
			memcpy(pTmp+k*m_CurWidth,pSrcData+j*m_CurWidth,m_CurWidth);
			k += Step;
			if (k >= m_CurHeight) break;
		}
		j++;
		k = 2; Step = 4;
		for (; j < m_CurHeight  ; j ++)
		{
			memcpy(pTmp+k*m_CurWidth,pSrcData+j*m_CurWidth,m_CurWidth);
			k += Step;
			if (k >= m_CurHeight) break;
		}
		j++;
		k = 1; Step = 2;
		for (; j < m_CurHeight  ; j ++)
		{
			memcpy(pTmp+k*m_CurWidth,pSrcData+j*m_CurWidth,m_GifInfo.Width);
			k += Step;
			if (k >= m_CurHeight) break;
		}
		
		pSrcData = p2;
	}
	BMPIMAGE * pBmpImage = new BMPIMAGE;
	pBmpImage->tColor = m_CurTColorIndex;
	pBmpImage->DelayTime = m_CurDelayTime;
	pBmpImage->Left = m_CurX;
	pBmpImage->Top = m_CurY;
	pBmpImage->Width = m_CurWidth ;
	pBmpImage->Height = m_CurHeight ;
	pBmpImage->SaveMode = m_CurSaveMode;

	

	memcpy(&pBmpImage->Palette ,&m_CurRgbQuad,sizeof(RGBQUAD)*256);

	USHORT TrueWidth = WIDTHBYTES(m_CurWidth * 8);//全轉成256顯示圖片
	pBmpImage->pImageData = (LPUSTR)GlobalAlloc(GPTR,TrueWidth*m_CurHeight );

	LPUSTR p0,p1;
	p0 = pSrcData;
    p1 = pBmpImage->pImageData;

	for (j = 0; j < m_CurHeight  ; j ++)//圖形翻轉
	{
		k = (m_CurHeight - j - 1);
		for (i = 0 ; i < m_CurWidth ;i ++)
		{
			p1[ k * TrueWidth + i] = p0[j*m_CurWidth+i];
		}
	}
	
	if (m_CurSaveMode) //交叉存
	{
		GlobalFree(pSrcData);
	}
	m_ImageList.AddTail (pBmpImage);
	//SaveBmp("1.bmp",pBmpImage->pImageData);
	return 1;
}

BOOL CGIF::ShowImage(HDC hDC, POINT StartPos, UINT ImageNo)
{
	//CDC *pDC = CDC::FromHandle (hDC);
	BITMAPINFOHEADER  BmpInfoHeader;
	BmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	
	BmpInfoHeader.biPlanes = 1;
	BmpInfoHeader.biBitCount = 8;
	BmpInfoHeader.biCompression = BI_RGB;
	BmpInfoHeader.biSizeImage = 0;
	BmpInfoHeader.biXPelsPerMeter = 0;
	BmpInfoHeader.biYPelsPerMeter = 0;
	BmpInfoHeader.biClrUsed = 0;
	BmpInfoHeader.biClrImportant = 0;
	
	POSITION Pos;
	Pos = m_ImageList.FindIndex(ImageNo);
	if (Pos)
	{
		BMPIMAGE * pBmpImage = (BMPIMAGE *)m_ImageList.GetAt(Pos );
		BmpInfoHeader.biWidth = pBmpImage->Width;
		BmpInfoHeader.biHeight = pBmpImage->Height;	

		BITMAPINFO  *pBmInfo = (BITMAPINFO  *)GlobalAlloc(GPTR,sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
		memcpy(&pBmInfo->bmiHeader ,&BmpInfoHeader,sizeof(BITMAPINFOHEADER));
		memcpy(pBmInfo->bmiColors ,pBmpImage->Palette ,sizeof(RGBQUAD)*256);
		
		if (pBmpImage->tColor >= 0)
		{
			HDC hMemDC = ::CreateCompatibleDC(hDC);
			HBITMAP hBmp = (HBITMAP)::CreateCompatibleBitmap(hDC,pBmpImage->Width,pBmpImage->Height);
			HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hBmp);

			::StretchDIBits(hMemDC,0 ,0,pBmpImage->Width,pBmpImage->Height,
							0,0,pBmpImage->Width,pBmpImage->Height ,pBmpImage->pImageData,pBmInfo,
							DIB_RGB_COLORS,SRCCOPY);


			COLORREF cRgb = RGB(pBmpImage->Palette [pBmpImage->tColor].rgbRed,
								pBmpImage->Palette [pBmpImage->tColor].rgbGreen,
								pBmpImage->Palette [pBmpImage->tColor].rgbBlue );

			BitBltEx(hDC,pBmpImage->Left+StartPos.x ,pBmpImage->Top+StartPos.y ,pBmpImage->Width,pBmpImage->Height,hMemDC,0,0 ,cRgb);
			::SelectObject(hMemDC,hOldBmp);
			::DeleteObject(hBmp);
			::DeleteDC(hMemDC);
		}
		else ::StretchDIBits(hDC,pBmpImage->Left+StartPos.x ,pBmpImage->Top+StartPos.y ,pBmpImage->Width,pBmpImage->Height,
							0,0,pBmpImage->Width,pBmpImage->Height ,pBmpImage->pImageData,pBmInfo,
							DIB_RGB_COLORS,SRCCOPY);
 
		GlobalFree(pBmInfo);
		//SaveBmp("1.bmp",pBmpImage->pImageData);
	}
	else return 0;
	return 1;
}


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
)
{

	HDC hDC1,hDC2;
	hDC1 = CreateCompatibleDC( hdcSrc );
	hDC2 = CreateCompatibleDC( hdcSrc );
	

	HBITMAP bmp1Old, bmp1 = CreateBitmap(nWidth, nHeight, 1, 1, NULL);
	bmp1Old = (HBITMAP)SelectObject(hDC1, bmp1);
	COLORREF cColor = SetBkColor(hdcSrc, cTransparentColor); 
	::BitBlt(hDC1,0,0,nWidth,nHeight,hdcSrc,nXSrc,nYSrc,SRCCOPY);
	
	

	HBITMAP bmp2Old, bmp2 = CreateBitmap(nWidth, nHeight, 1, 1, NULL);
	bmp2Old = (HBITMAP)SelectObject(hDC2, bmp2);
	
	::BitBlt(hDC2,0,0,nWidth,nHeight,hDC1,0,0,NOTSRCCOPY);
	
	HDC hDC3;
	hDC3 = CreateCompatibleDC( hdcSrc );
	HBITMAP bmp3Old, bmp3 = CreateCompatibleBitmap(hdcSrc, nWidth, nHeight);
	bmp3Old = (HBITMAP)SelectObject(hDC3, bmp3);
	::BitBlt(hDC3,0,0,nWidth,nHeight,hdcSrc,nXSrc,nYSrc,SRCCOPY);
	::BitBlt(hDC3,0,0,nWidth,nHeight,hDC2,0,0,SRCAND);
	SelectObject(hDC2, bmp2Old);
	DeleteObject(bmp2);
	DeleteDC(hDC2);
	
	HDC hDC4;
	hDC4 = CreateCompatibleDC( hdcSrc );
	HBITMAP bmp4Old, bmp4 = CreateCompatibleBitmap(hdcSrc, nWidth, nHeight);
	bmp4Old = (HBITMAP)SelectObject(hDC4, bmp4);
	::BitBlt(hDC4,0,0,nWidth,nHeight,hdcDest,nXDest,nYDest,SRCCOPY);
	::BitBlt(hDC4,0,0,nWidth,nHeight,hDC1,0,0,SRCAND);
	SelectObject(hDC1, bmp1Old);
	DeleteObject(bmp1);
	DeleteDC(hDC1);
	
	
	HDC hDC5;
	hDC5 = CreateCompatibleDC( hdcSrc );
	HBITMAP bmp5Old, bmp5 = CreateCompatibleBitmap(hdcSrc, nWidth, nHeight);
	bmp5Old = (HBITMAP)SelectObject(hDC5, bmp5);
	::BitBlt(hDC5,0,0,nWidth,nHeight,hDC3,0,0,SRCCOPY);
	::BitBlt(hDC5,0,0,nWidth,nHeight,hDC4,0,0,SRCPAINT);
	
	SelectObject(hDC3, bmp3Old);
	DeleteObject(bmp3);
	DeleteDC(hDC3);
	SelectObject(hDC4, bmp4Old);
	DeleteObject(bmp4);
	DeleteDC(hDC4);

	::BitBlt(hdcDest,nXDest,nYDest,nWidth,nHeight,hDC5,0,0,SRCCOPY);
	
	SelectObject(hDC5, bmp5Old);
	DeleteObject(bmp5);
	DeleteDC(hDC5);
	return 1;
}

BOOL CGIF::GetImageInfo(RECT &Rect,COLORREF &tColor ,UINT ImageNo)
{
	POSITION Pos;
	Pos = m_ImageList.FindIndex(ImageNo);
	if (Pos)
	{
		BMPIMAGE * pBmpImage = (BMPIMAGE *)m_ImageList.GetAt(Pos );
		Rect.left = pBmpImage->Left ;
		Rect.top =  pBmpImage->Top ;
		Rect.right = pBmpImage->Left + pBmpImage->Width ;
		Rect.bottom = pBmpImage->Top + pBmpImage->Height ;
		tColor = pBmpImage->tColor ;
		return 1;
	}
	else return 0;
}
