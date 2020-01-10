// RotateAnimation.cpp : 实现文件
//

#include "RotateAnimation.h"


// CRotateAnimation

CRotateAnimation::CRotateAnimation()
{
	m_nWidth=0;
	m_nHeight=0;
	m_ColorBack=0xFFFFFF;
	m_pColorArray=NULL;
	m_pAnimationArray=NULL;
	m_AnimationCount=0;
	m_AnimationIndex=0;
	m_hCacheDC=NULL;
	m_hCacheBitmap=NULL;
	m_hCacheOldBitmap=NULL;
	m_AnimationType=0;
	m_MarginAngle=0;
	m_ItemSize=0;
}

CRotateAnimation::~CRotateAnimation()
{
    this->Release();
}

void CRotateAnimation::InitAnimation()
{
	this->Release();
	if(m_hWnd==NULL || !::IsWindow(m_hWnd))
	{
		return;
	}
	//--------------------------------------------------------
	RECT rc;
	GetClientRect (&rc);
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;
	m_Rect.Width = m_nWidth > m_nHeight?m_nHeight - 2:m_nWidth - 2;
	m_Rect.Height = m_Rect.Width;
	m_Rect.X = (m_nWidth - m_Rect.Width) / 2;
	m_Rect.Y = (m_nHeight - m_Rect.Height) / 2;
	m_ItemSize = m_Rect.Width/8;
	if(m_ItemSize<5)
		m_ItemSize=5;
	m_MarginAngle = 0;
	m_ColorBack = GetSysColor(COLOR_BTNFACE);
	m_AnimationCount = 12;
	m_AnimationIndex = 0;
	m_AnimationType = 0;
	//--------------------------------------------------------
	m_pColorArray = new AnimationItem[m_AnimationCount];
	m_pAnimationArray = new AnimationItem[m_AnimationCount];

	m_ColorBasic.clrOut=RGB(128,128,128);
	m_ColorBasic.clrIn=RGB(192,192,192);

	m_pColorArray[0].clrOut = RGB(251,244,31);
	m_pColorArray[1].clrOut = RGB(140,249,7);
	m_pColorArray[2].clrOut = RGB(4,168,145);
	m_pColorArray[3].clrOut = RGB(2,147,204);
	m_pColorArray[4].clrOut = RGB(1,88,175);
	m_pColorArray[5].clrOut = RGB(107,66,156);
	m_pColorArray[6].clrOut = RGB(167,68,151);
	m_pColorArray[7].clrOut = RGB(228,65,152);
	m_pColorArray[8].clrOut = RGB(238,27,36);
	m_pColorArray[9].clrOut = RGB(245,114,36);
	m_pColorArray[10].clrOut = RGB(244,144,33);
	m_pColorArray[11].clrOut = RGB(255,194,18);

	m_pColorArray[0].clrIn = RGB(255,245,52);
	m_pColorArray[1].clrIn = RGB(163,253,60);
	m_pColorArray[2].clrIn = RGB(51,184,165);
	m_pColorArray[3].clrIn = RGB(51,167,216);
	m_pColorArray[4].clrIn = RGB(54,118,182);
	m_pColorArray[5].clrIn = RGB(136,105,173);
	m_pColorArray[6].clrIn = RGB(185,104,173);
	m_pColorArray[7].clrIn = RGB(233,102,172);
	m_pColorArray[8].clrIn = RGB(239,74,81);
	m_pColorArray[9].clrIn = RGB(245,141,78);
	m_pColorArray[10].clrIn = RGB(250,165,75);
	m_pColorArray[11].clrIn = RGB(254,206,62);

	//--------------------------------------------------------
	for(int i=0;i<m_AnimationCount;i++)
	{
		m_pAnimationArray[i] = m_ColorBasic;
	}
	//--------------------------------------------------------
	HDC hSrcDC = ::GetDC(m_hWnd);
	m_hCacheDC = CreateCompatibleDC (hSrcDC);
	m_hCacheBitmap = CreateCompatibleBitmap (hSrcDC, m_nWidth, m_nHeight);
	m_hCacheOldBitmap = (HBITMAP)SelectObject (m_hCacheDC, m_hCacheBitmap);
	::ReleaseDC(m_hWnd,hSrcDC);
	//--------------------------------------------------------
	SetType(0);
	SetTimer(100,200,NULL);
}
void CRotateAnimation::Release()
{
	if(m_hCacheDC)
	{
		SelectObject(m_hCacheDC,m_hCacheOldBitmap);
		DeleteObject(m_hCacheBitmap);
		DeleteDC(m_hCacheDC);
	}
	m_hCacheDC=NULL;
	m_hCacheBitmap=NULL;
	m_hCacheOldBitmap=NULL;
	if(m_pColorArray)
		delete[] m_pColorArray;
	if(m_pAnimationArray)
		delete[] m_pAnimationArray;
	m_nWidth=0;
	m_nHeight=0;
	m_pColorArray=NULL;
	m_pAnimationArray=NULL;
	m_AnimationCount=0;
	m_AnimationIndex=0;
}
void CRotateAnimation::SetType(int nType,int nMarginAngle)
{
	m_AnimationIndex = 0;
	m_MarginAngle = nMarginAngle;
	//--------------------------------------------------------
	switch(nType)
	{
	case 0:
		{
			m_AnimationType = nType;
			break;
		}
	case 1:
		{
			m_AnimationType = nType;
			break;
		}
	case 2:
		{
			m_AnimationType = nType;
			for(int i=0;i<m_AnimationCount;i++)
			{
				m_pAnimationArray[i] = m_pColorArray[i];
			}
			break;
		}
	case 3:
		{
			m_AnimationType = nType;
			for(int i=0;i<m_AnimationCount;i++)
			{
				m_pAnimationArray[i] = m_pColorArray[i];
			}
			break;
		}
	default:
		SetType(0);
		return;
		break;
	}
	//--------------------------------------------------------
	if(m_MarginAngle>10)
		m_MarginAngle=10;
	if(m_MarginAngle<0)
		m_MarginAngle=0;
	Draw(NULL);
	InvalidateRect(NULL,TRUE);
}
void CRotateAnimation::PlayNext(HDC hDestDC)
{
	switch(m_AnimationType)
	{
	case 0:
		{
			m_AnimationIndex++;
			if(m_AnimationIndex > m_AnimationCount)
			{
				m_AnimationIndex = 0;
				m_AnimationType = 1;
			}
			for(int i=0;i<m_AnimationIndex;i++)
			{
				m_pAnimationArray[i] = m_pColorArray[i];
			}
			break;
		}
	case 1:
		{
			m_AnimationIndex++;
			if(m_AnimationIndex > m_AnimationCount)
			{
				m_AnimationIndex = 0;
				m_AnimationType = 0;
			}
			for(int i=0;i<m_AnimationIndex;i++)
			{
				m_pAnimationArray[i] = m_ColorBasic;
			}
			break;
		}
	case 2:
		{
			m_AnimationIndex=0;
			AnimationItem item=m_pAnimationArray[m_AnimationCount-1];
			for(int i=m_AnimationCount-1;i>=0;i--)
			{
				m_pAnimationArray[i] = m_pAnimationArray[i-1];
			}
			m_pAnimationArray[0] = item;
			break;
		}
	case 3:
		{
			m_AnimationIndex++;
			if(m_AnimationIndex > m_AnimationCount)
			{
				m_AnimationIndex = 0;
			}
			break;
		}
	}
	//--------------------------------------------------------
	Draw(hDestDC);
}
void CRotateAnimation::Draw(HDC hDestDC)
{
	//给整个画布填充底色，FillSolidRect
	SetBkColor (m_hCacheDC, m_ColorBack);
	ExtTextOut (m_hCacheDC, 0, 0, ETO_OPAQUE, CRect(0,0,m_nWidth, m_nHeight), NULL, 0, 0);
	//--------------------------------------------------------
	DrawPie(m_hCacheDC);
	//--------------------------------------------------------
	if(hDestDC)
	{
		BitBlt(hDestDC);
	}

}
void CRotateAnimation::DrawPie(HDC hDC)
{
	Gdiplus::Graphics* pGraphics=new Gdiplus::Graphics(hDC);
	pGraphics->SetSmoothingMode(SmoothingModeHighQuality);
	Gdiplus::Color clr(150,0,0,0);
	Gdiplus::SolidBrush* pBrush=new Gdiplus::SolidBrush(clr);
	//--------------------------------------------------------
	//计算外圈、内圈位置
	Gdiplus::Rect rcOut(m_Rect);
	Gdiplus::Rect rcIn(rcOut);
	rcIn.Inflate(-m_ItemSize,-m_ItemSize);
	//--------------------------------------------------------
	//先画出外圈小方块
	float fStartAngle = -90;//起始绘制角度
	float fSweepAngle = 360 / m_AnimationCount;//每小块的角度
	for(int i=0;i<m_AnimationCount;i++)
	{
		clr.SetFromCOLORREF(m_pAnimationArray[i].clrOut);
		pBrush->SetColor(clr);
		pGraphics->FillPie(pBrush,rcOut, fStartAngle, fSweepAngle - m_MarginAngle);
		fStartAngle = fStartAngle + fSweepAngle;
	}
	//--------------------------------------------------------
	//画出内圈小方块;
	fStartAngle = -90;
	for(int i=0;i<m_AnimationCount;i++)
	{
		clr.SetFromCOLORREF(m_pAnimationArray[i].clrIn);
		pBrush->SetColor(clr);
		pGraphics->FillPie(pBrush,rcIn, fStartAngle, fSweepAngle - m_MarginAngle);
		fStartAngle = fStartAngle + fSweepAngle;
	}
	//--------------------------------------------------------
	//画出高亮色块
	if(m_AnimationType==3)
	{
		if(m_AnimationIndex>0)
		{
			fStartAngle = -90;
			fStartAngle +=m_AnimationIndex*fSweepAngle;
			pBrush->SetColor(Color(150,255,255,255));
			pGraphics->FillPie(pBrush,rcOut, fStartAngle, fSweepAngle - m_MarginAngle);
		}
	}
	//--------------------------------------------------------
	//画出中间圆心，用控件底色填充
	rcIn.Inflate(-m_ItemSize,-m_ItemSize);
	clr.SetFromCOLORREF(m_ColorBack);
	pBrush->SetColor(clr);
	pGraphics->FillEllipse(pBrush,rcIn);
	//--------------------------------------------------------
	delete pBrush;
	delete pGraphics;
}
void CRotateAnimation::BitBlt(HDC hDestDC)
{
	::BitBlt (hDestDC, 0, 0, m_nWidth, m_nHeight, m_hCacheDC, 0, 0, SRCCOPY);
}



void CRotateAnimation::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==100)
	{
		KillTimer(nIDEvent);
		HDC hDC = ::GetDC (m_hWnd);
		PlayNext(hDC);
		::ReleaseDC (m_hWnd, hDC);
		SetTimer(nIDEvent,80,NULL);
		return;
	}
}
