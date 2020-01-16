#pragma once

#include "DialogWindow.h"


/////////////////////////////////////////////////////////////////////////////////
//
#define WINDOW_WIDTH            837
#define WINDOW_HEIGHT           600
/////////////////////////////////////////////////////////////////////////////////
//
#define RES_PNG_TYPE_NAME       "PNG"
#define PROP_IMG_BACKGROUND     "IMG_BACKGROUND"
#define PROP_BITMAP_MEMORY      "BITMAP_MEMORY"
#define PROP_GRAPHICS_MEMORY    "GRAPHICS_MEMORY"

/////////////////////////////////////////////////////////////////////////////////
//
#include <time.h>
/////////////////////////////////////////////////////////////////////////////////
//
typedef struct tagAnimationItem
{
    COLORREF clrOut;//��Ȧ��ɫ
    COLORREF clrIn;//��Ȧ��ɫ
} AnimationItem, * PAnimationItem;

#define ANIMATION_COUNTSIZE 12

static int m_ItemSize = 0;
static int m_MarginAngle = 0;
static COLORREF m_ColorBack = 0;
static int m_AnimationIndex = 0;
static int m_AnimationType = 0;
static Gdiplus::Rect m_Rect;
static AnimationItem m_ColorArray[ANIMATION_COUNTSIZE] = { 0 };
static AnimationItem m_AnimationArray[ANIMATION_COUNTSIZE] = { 0 };
static AnimationItem m_ColorBasic = { 0 };
__inline static 
void InitAnimation(HWND hWnd)
{
    //--------------------------------------------------------
    RECT rc;
    GetClientRect(hWnd, &rc);
    int m_nWidth = 0;
    int m_nHeight = 0;
    m_nWidth = (rc.right - rc.left) / 4;
    m_nHeight = (rc.bottom - rc.top) / 4;
    m_Rect.Width = m_nWidth > m_nHeight ? m_nHeight - 2 : m_nWidth - 2;
    m_Rect.Height = m_Rect.Width;
    m_Rect.X = (m_nWidth - m_Rect.Width) / 2;
    m_Rect.Y = (m_nHeight - m_Rect.Height) / 2;
    m_ItemSize = m_Rect.Width / 8;
    if (m_ItemSize < 5)
    {
        m_ItemSize = 5;
    }
    m_MarginAngle = 0;
    m_ColorBack = GetSysColor(COLOR_BTNFACE);
    m_AnimationIndex = 0;
    m_AnimationType = 3;
    //--------------------------------------------------------

    m_ColorBasic.clrOut = RGB(128, 128, 128);
    m_ColorBasic.clrIn = RGB(192, 192, 192);

    m_ColorArray[0].clrOut = RGB(251, 244, 31);
    m_ColorArray[1].clrOut = RGB(140, 249, 7);
    m_ColorArray[2].clrOut = RGB(4, 168, 145);
    m_ColorArray[3].clrOut = RGB(2, 147, 204);
    m_ColorArray[4].clrOut = RGB(1, 88, 175);
    m_ColorArray[5].clrOut = RGB(107, 66, 156);
    m_ColorArray[6].clrOut = RGB(167, 68, 151);
    m_ColorArray[7].clrOut = RGB(228, 65, 152);
    m_ColorArray[8].clrOut = RGB(238, 27, 36);
    m_ColorArray[9].clrOut = RGB(245, 114, 36);
    m_ColorArray[10].clrOut = RGB(244, 144, 33);
    m_ColorArray[11].clrOut = RGB(255, 194, 18);

    m_ColorArray[0].clrIn = RGB(255, 245, 52);
    m_ColorArray[1].clrIn = RGB(163, 253, 60);
    m_ColorArray[2].clrIn = RGB(51, 184, 165);
    m_ColorArray[3].clrIn = RGB(51, 167, 216);
    m_ColorArray[4].clrIn = RGB(54, 118, 182);
    m_ColorArray[5].clrIn = RGB(136, 105, 173);
    m_ColorArray[6].clrIn = RGB(185, 104, 173);
    m_ColorArray[7].clrIn = RGB(233, 102, 172);
    m_ColorArray[8].clrIn = RGB(239, 74, 81);
    m_ColorArray[9].clrIn = RGB(245, 141, 78);
    m_ColorArray[10].clrIn = RGB(250, 165, 75);
    m_ColorArray[11].clrIn = RGB(254, 206, 62);

    //--------------------------------------------------------
    for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
    {
        m_AnimationArray[i] = m_ColorBasic;
    }
    //--------------------------------------------------------
    m_AnimationIndex = 0;
    m_MarginAngle = 2;
    //--------------------------------------------------------
    switch (m_AnimationType)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        break;
    }
    case 2:
    {
        for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
        {
            m_AnimationArray[i] = m_ColorArray[i];
        }
        break;
    }
    case 3:
    {
        for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
        {
            m_AnimationArray[i] = m_ColorArray[i];
        }
        break;
    }
    default:
        return;
        break;
    }
    //--------------------------------------------------------
    if (m_MarginAngle > 10)
    {
        m_MarginAngle = 10;
    }
    if (m_MarginAngle < 0)
    {
        m_MarginAngle = 0;
    }
}
//����Բ��
__inline static 
void DrawPie(Gdiplus::Graphics* pGraphics, HWND hWnd) {
    RECT rc;
    GetClientRect(hWnd, &rc); 
    
    Gdiplus::Bitmap* targBmp = new Gdiplus::Bitmap((rc.right - rc.left)/4, (rc.bottom - rc.top)/4);

    Gdiplus::Graphics* pGraphicsTmp = new Gdiplus::Graphics(targBmp);
    {
        pGraphicsTmp->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
        pGraphicsTmp->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
        pGraphicsTmp->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    }
    Gdiplus::Color clr(150, 0, 0, 0);
    Gdiplus::SolidBrush* pBrush = new Gdiplus::SolidBrush(clr);

    //������Ȧ����Ȧλ��
    Gdiplus::Rect rcOut(m_Rect);
    Gdiplus::Rect rcIn(rcOut);
    rcIn.Inflate(-m_ItemSize, -m_ItemSize);
    //--------------------------------------------------------
    //�Ȼ�����ȦС����
    float fStartAngle = -90;//��ʼ���ƽǶ�
    float fSweepAngle = 360 / ANIMATION_COUNTSIZE;//ÿС��ĽǶ�
    for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
    {
        clr.SetFromCOLORREF(m_AnimationArray[i].clrOut);
        pBrush->SetColor(clr);
        pGraphicsTmp->FillPie(pBrush, rcOut, fStartAngle, fSweepAngle - m_MarginAngle);
        fStartAngle = fStartAngle + fSweepAngle;
    }
    //--------------------------------------------------------
    //������ȦС����;
    fStartAngle = -90;
    for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
    {
        clr.SetFromCOLORREF(m_AnimationArray[i].clrIn);
        pBrush->SetColor(clr);
        pGraphicsTmp->FillPie(pBrush, rcIn, fStartAngle, fSweepAngle - m_MarginAngle);
        fStartAngle = fStartAngle + fSweepAngle;
    }
    //--------------------------------------------------------
    //��������ɫ��
    if (m_AnimationType == 3)
    {
        if (m_AnimationIndex > 0)
        {
            fStartAngle = -90;
            fStartAngle += m_AnimationIndex * fSweepAngle;
            pBrush->SetColor(Gdiplus::Color(150, 255, 255, 255));
            pGraphicsTmp->FillPie(pBrush, rcOut, fStartAngle, fSweepAngle - m_MarginAngle);
        }
    }
    //--------------------------------------------------------
    //�����м�Բ�ģ��ÿؼ���ɫ���
    rcIn.Inflate(-m_ItemSize, -m_ItemSize);
    clr.SetFromCOLORREF(m_ColorBack);
    pBrush->SetColor(clr);
    pGraphicsTmp->FillEllipse(pBrush, rcIn);
    //
    pGraphics->DrawImage(targBmp,
        Gdiplus::RectF(0, 0, targBmp->GetWidth(), targBmp->GetHeight()),
        0, 0, targBmp->GetWidth(), targBmp->GetHeight(), Gdiplus::Unit::UnitPixel);
    //--------------------------------------------------------
    delete pBrush;
    delete pGraphicsTmp;
    delete targBmp;

    {
        switch (m_AnimationType)
        {
        case 0:
        {
            m_AnimationIndex++;
            if (m_AnimationIndex > ANIMATION_COUNTSIZE)
            {
                m_AnimationIndex = 0;
                m_AnimationType = 1;
            }
            for (int i = 0; i < m_AnimationIndex; i++)
            {
                m_AnimationArray[i] = m_ColorArray[i];
            }
            break;
        }
        case 1:
        {
            m_AnimationIndex++;
            if (m_AnimationIndex > ANIMATION_COUNTSIZE)
            {
                m_AnimationIndex = 0;
                m_AnimationType = 0;
            }
            for (int i = 0; i < m_AnimationIndex; i++)
            {
                m_AnimationArray[i] = m_ColorBasic;
            }
            break;
        }
        case 2:
        {
            m_AnimationIndex = 0;
            AnimationItem item = m_AnimationArray[ANIMATION_COUNTSIZE - 1];
            for (int i = ANIMATION_COUNTSIZE - 1; i >= 0; i--)
            {
                m_AnimationArray[i] = m_AnimationArray[i - 1];
            }
            m_AnimationArray[0] = item;
            break;
        }
        case 3:
        {
            m_AnimationIndex++;
            if (m_AnimationIndex > ANIMATION_COUNTSIZE)
            {
                m_AnimationIndex = 0;
            }
            break;
        }
        }
    }
    if (m_MarginAngle > 10)
    {
        m_MarginAngle = 10;
    }
    if (m_MarginAngle < 0)
    {
        m_MarginAngle = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////
// ���Բ�Ǿ���
static void addRoundRect(Gdiplus::GraphicsPath& path, RECT rc, int r1, int r2 = 0, int r3 = 0, int r4 = 0)
{
    int x = rc.left;
    int y = rc.top;
    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    if (r2 == 0) r2 = r1;
    if (r3 == 0) r3 = r1;
    if (r4 == 0) r4 = r2;
    path.AddBezier(x, y + r1, x, y, x + r1, y, x + r1, y);
    path.AddLine(x + r1, y, (x + w) - r2, y);
    path.AddBezier((x + w) - r2, y, x + w, y, x + w, y + r2, x + w, y + r2);
    path.AddLine((x + w), (y + r2), (x + w), (y + h) - r3);
    path.AddBezier(x + w, (y + h) - r3, x + w, y + h, (x + w) - r3, y + h, (x + w) - r3, y + h);
    path.AddLine((x + w) - r3, y + h, x + r4, y + h);
    path.AddBezier(x + r4, y + h, x, y + h, x, (y + h) - r4, x, (y + h) - r4);
    path.AddLine(x, (y + h) - r4, x, y + r1);
}
//����������
void DrawWordArt(Gdiplus::Graphics* pGraphics)
{
    Gdiplus::Bitmap bitmap(500, 300, pGraphics);
    Gdiplus::Graphics graphics(&bitmap);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

    Gdiplus::FontFamily fontFamily(CStringW(_T("Arial Black")));
    Gdiplus::StringFormat strformat;
    _TCHAR pszbuf[][MAXCHAR] = {
        {_T("Hello everyone!")},
        {_T("���Ĳ��ԣ�123")}
    };

    Gdiplus::GraphicsPath path;
    path.AddString(CStringW(pszbuf[0]), _tcslen(pszbuf[0]), &fontFamily,
        Gdiplus::FontStyleRegular, 38, Gdiplus::Point(10, 10), &strformat);

    path.AddString(CStringW(pszbuf[1]), _tcslen(pszbuf[1]), &fontFamily,
        Gdiplus::FontStyleRegular, 38, Gdiplus::Point(100, 60), &strformat);

    Gdiplus::Pen pen(Gdiplus::Color(200, 215, 0, 0), 3);

    // ��������·��
    graphics.DrawPath(&pen, &path);

    // ��䱳��ɫ
    Gdiplus::SolidBrush brush(Gdiplus::Color(200, 228, 228, 228));
    graphics.FillRectangle(&brush, 3, 5, 750, 90);

    // ���·����ɫ�����������ֵ���ɫ
    Gdiplus::LinearGradientBrush linGrBrush(
        Gdiplus::Point(0, 0),
        Gdiplus::Point(0, 90),
        Gdiplus::Color(255, 0, 255, 255),
        Gdiplus::Color(255, 30, 120, 195));
    graphics.FillPath(&linGrBrush, &path);

    // ����Բ�Ǿ���
    Gdiplus::GraphicsPath path2;
    RECT rt = { 50,120,200,270 };
    addRoundRect(path2, rt, 40);

    Gdiplus::HatchBrush myHatchBrush(
        Gdiplus::HatchStyleWave,  // 50������Ӱ
        Gdiplus::Color(200, 0, 0, 255), // ��Ӱ����ɫ
        Gdiplus::Color(200, 0, 255, 0)); // ��䱳��ɫ
    graphics.FillPath(&myHatchBrush, &path2);

    pGraphics->DrawImage(&bitmap,
        Gdiplus::RectF(0, 200, bitmap.GetWidth(), bitmap.GetHeight()),
        0, 0, bitmap.GetWidth(), bitmap.GetHeight(), Gdiplus::Unit::UnitPixel);
}
////////////////////////////////////////////////////////////////////////////////
//
Gdiplus::SizeF GetTextBounds(const Gdiplus::Font& font, const Gdiplus::StringFormat& strFormat, const CString& szText)
{
    Gdiplus::RectF rcBound;
    Gdiplus::FontFamily fontFamily;
    Gdiplus::GraphicsPath graphicsPath;
    font.GetFamily(&fontFamily);
    graphicsPath.AddString(szText, -1, &fontFamily, font.GetStyle(), font.GetSize(), \
        Gdiplus::PointF(0, 0), &strFormat);
    /// ��ȡ�߽緶Χ
    graphicsPath.GetBounds(&rcBound);
    /// �����ı��Ŀ��
    return Gdiplus::SizeF(rcBound.Width, rcBound.Height);
}
Gdiplus::Bitmap* GetPumpImage(float fMin, float fMax, float fValue, CString strUnit)
{
    const float PI = 3.141592653;
    if (fMin > fValue)
    {
        fMin = fValue;
    }
    if (fValue > fMax)
    {
        fMax = fValue;
    }
    int nWidth, nHeight;
    nWidth = nHeight = 200;
    Gdiplus::Rect rect(0, 0, nWidth, nHeight);
    int nTable = 5;		//	���
    int nScale = 5;		//	ÿС�������С��
    //	ÿ����ɫ
    Gdiplus::Color TableColor[] =
    {
        Gdiplus::Color::Green,
        Gdiplus::Color::Blue,
        Gdiplus::Color::Cyan,
        Gdiplus::Color::Yellow,
        Gdiplus::Color::Red
    };
    //	�ſ��Ļ���
    float fRadian = 60;
    //	ͬ��Բ�뾶
    int nRadius[] =
    {
        200,
        160,
        90
    };
    //	Բ��
    Gdiplus::Point ptCenter(nWidth / 2, nHeight + 20);
    //	�̶��߳���
    int nLongScal = 15;
    int nShortScal = 10;
    //	����ɫ
    Gdiplus::Color bkColor = Gdiplus::Color::SkyBlue;
    //	�̶�����,��С,��ɫ
    Gdiplus::Color ScaleColor = Gdiplus::Color::Blue;
    Gdiplus::REAL	ScaleSize = 8;
    CString ScaleFont = _T("Times New Roman");
    //CString ScaleFont = _T("����");

    Gdiplus::Bitmap* pImage = new Gdiplus::Bitmap(nWidth, nHeight);
    Gdiplus::Graphics* pGraph = Gdiplus::Graphics::FromImage(pImage);
    Gdiplus::StringFormat format;
    //	�������
    format.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
    format.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
    pGraph->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
    pGraph->Clear(Gdiplus::Color::Transparent);
    Gdiplus::Color LineColor = Gdiplus::Color::Chocolate;
    Gdiplus::Pen LinePen(LineColor, 1);
    //	�����λ�
    rect = Gdiplus::Rect(ptCenter.X - nRadius[0], ptCenter.Y - nRadius[0], 2 * nRadius[0], 2 * nRadius[0]);
    pGraph->DrawArc(&LinePen, rect, 180 + (90 - fRadian / 2), fRadian);
    rect = Gdiplus::Rect(ptCenter.X - nRadius[1], ptCenter.Y - nRadius[1], 2 * nRadius[1], 2 * nRadius[1]);
    pGraph->DrawArc(&LinePen, rect, 180 + (90 - fRadian / 2), fRadian);
    rect = Gdiplus::Rect(ptCenter.X - nRadius[2], ptCenter.Y - nRadius[2], 2 * nRadius[2], 2 * nRadius[2]);
    pGraph->DrawArc(&LinePen, rect, 180 + (90 - fRadian / 2), fRadian);

    //	��̶�

    //	�ֶ�
    for (int i = 0; i <= nTable * nScale; i++)
    {
        Gdiplus::Point p1, p0;
        double f0 = ((180 - fRadian) / 2 + fRadian / (nTable * nScale) * i) / 180 * PI;
        p1.X = ptCenter.X + nRadius[1] * cos(f0);
        p1.Y = ptCenter.Y - nRadius[1] * sin(f0);
        if (i % nTable == 0)
        {

            {
                p0.X = ptCenter.X + (nRadius[1] + nLongScal) * cos(f0);
                p0.Y = ptCenter.Y - (nRadius[1] + nLongScal) * sin(f0);

                CString str;
                str.Format(_T("%.0f"), fMax - (fMax - fMin) / (nTable * nScale) * i);
                //	��ȡ�ı���ռ�Ĵ�С
                //CSize size = CGraphCurveView::GetOutPutTextSize(pGraph, str, ScaleFont, ScaleSize);
                Gdiplus::SizeF size = GetTextBounds(Gdiplus::Font(CStringW(ScaleFont), ScaleSize), format, str);
                Gdiplus::RectF textrc;
                textrc.X = p0.X - size.Width / 2;
                textrc.Y = p0.Y - size.Height;
                textrc.Width = size.Width;
                textrc.Height = size.Height;
                pGraph->DrawString(
                    str,
                    -1,
                    &Gdiplus::Font(ScaleFont, ScaleSize),
                    textrc,
                    &format,
                    &Gdiplus::SolidBrush(ScaleColor)
                );
                Gdiplus::Point p2, p3;
                int nGap = 5;
                p3.X = ptCenter.X + (nRadius[0] + 0) * cos(f0);
                p3.Y = ptCenter.Y - (nRadius[0] + 0) * sin(f0);
                p2.X = ptCenter.X + (nRadius[0] - nGap) * cos(f0);
                p2.Y = ptCenter.Y - (nRadius[0] - nGap) * sin(f0);
                pGraph->DrawLine(&LinePen, p2, p3);
            }

        }
        else
        {
            p0.X = ptCenter.X + (nRadius[1] + nShortScal) * cos(f0);
            p0.Y = ptCenter.Y - (nRadius[1] + nShortScal) * sin(f0);
        }

        pGraph->DrawLine(&LinePen, p0, p1);
    }

    CString strDataFont = _T("Times New Roman");
    //CString strDataFont = _T("����");
    int DataSize = 8;
    Gdiplus::Color DataColor = Gdiplus::Color::Red;

    //	��λ
    Gdiplus::RectF UnitRc;
    
    //CSize size = CGraphCurveView::GetOutPutTextSize(pGraph, strUnit, strDataFont, DataSize);
    Gdiplus::SizeF size = GetTextBounds(Gdiplus::Font(CStringW(strDataFont), DataSize), format, strUnit);
    UnitRc.X = ptCenter.X - size.Width / 2;
    UnitRc.Y = ptCenter.Y - (nRadius[0] - nRadius[1] + nRadius[2] + size.Height / 2);
    UnitRc.Width = size.Width;
    UnitRc.Height = size.Height;
    pGraph->DrawString(
        strUnit,
        -1,
        &Gdiplus::Font(strDataFont, DataSize),
        UnitRc,
        &format,
        &Gdiplus::SolidBrush(DataColor)
    );

    //	����
    CString strData;
    strData.Format(_T("%.0f"), fValue);
    //size = CGraphCurveView::GetOutPutTextSize(pGraph, strData, strDataFont, DataSize);
    size = GetTextBounds(Gdiplus::Font(CStringW(strDataFont), DataSize), format, strData);
    Gdiplus::RectF DataRc;
    DataRc.X = ptCenter.X - size.Width / 2;
    DataRc.Y = ptCenter.Y - (nRadius[2] - nLongScal);
    DataRc.Width = size.Width;
    DataRc.Height = size.Height;
    pGraph->DrawString(
        strData,
        -1,
        &Gdiplus::Font(strDataFont, DataSize),
        DataRc,
        &format,
        &Gdiplus::SolidBrush(DataColor)
    );

    //	��ָ��
    Gdiplus::Pen PointPen(Gdiplus::Color::Green, 2);
    Gdiplus::Point p0, p1;
    double f0 = ((180 - fRadian) / 2 + fRadian / (fMax - fMin) * (-fValue + fMax)) / 180 * PI;
    p0.X = ptCenter.X + (nRadius[2] * cos(f0));
    p0.Y = ptCenter.Y - (nRadius[2] * sin(f0));
    p1.X = ptCenter.X + ((nRadius[1] + nShortScal / 2) * cos(f0));
    p1.Y = ptCenter.Y - ((nRadius[1] + nShortScal / 2) * sin(f0));
    pGraph->DrawLine(&PointPen, p0, p1);

    delete pGraph;
    return pImage;
}
/////////////////////////////////////////////////////////////////////////////////
//
class CRotateDialogWindow : public CDialogWindow {
public:
    static CRotateDialogWindow* Instance() {
        static CRotateDialogWindow instance;
        return &instance;
    }
    virtual VOID Run(HINSTANCE hInstance)
    {
        DialogBoxRun(hInstance, 
            MAKEINTRESOURCE(IDD_PUNTOBANCO_DIALOG), 
            CRotateDialogWindow::CallBack_DlgProc,
            CRotateDialogWindow::CallBack_WndProc,
            [](HWND _hWnd) {
                SetWindowPos(_hWnd, HWND_DESKTOP, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME | SWP_HIDEWINDOW);
                StartupResources(_hWnd);
            },
            [](HWND _hWnd) {
                CleanupResources(_hWnd);
            },
            [](HWND _hWnd) {
                TimeTask(_hWnd);
            });
    }
public:
    static VOID TimeTask(HWND hWnd)
    {
        
    }
    static INT StartupResources(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        RECT rcWindow = { 0, 0, 0, 0 };
        GetClientRect(hWnd, &rcWindow);

        if (CRotateDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapBackground, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_BACKGROUND)), _T(RES_PNG_TYPE_NAME)))
        {
            SetProp(hWnd, _T(PROP_IMG_BACKGROUND), (HANDLE)pBitmapBackground);
        }
       
        pBitmapMemory = new Gdiplus::Bitmap(rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);
        if (pBitmapMemory != NULL)
        {
            SetProp(hWnd, _T(PROP_BITMAP_MEMORY), (HANDLE)(pBitmapMemory));
            pGraphicsMemory = Gdiplus::Graphics::FromImage(pBitmapMemory);
            if (pGraphicsMemory != NULL)
            {
                SetProp(hWnd, _T(PROP_GRAPHICS_MEMORY), (HANDLE)(pGraphicsMemory));
                pGraphicsMemory->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
                pGraphicsMemory->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
                pGraphicsMemory->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

                pGraphicsMemory->DrawImage(pBitmapBackground,
                    Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
                    0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
            }
            else
            {
                SetProp(hWnd, _T(PROP_BITMAP_MEMORY), (HANDLE)NULL);
                delete pBitmapMemory;
                pBitmapMemory = NULL;
            }
        }
        return (INT)(0);
    }
    static INT CleanupResources(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;

        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));

        if (pBitmapBackground != NULL)
        {
            SetProp(hWnd, _T(PROP_IMG_BACKGROUND), (HANDLE)NULL);
            delete pBitmapBackground;
            pBitmapBackground = NULL;
        }
        if (pBitmapMemory != NULL)
        {
            SetProp(hWnd, _T(PROP_BITMAP_MEMORY), (HANDLE)NULL);
            delete pBitmapMemory;
            pBitmapMemory = NULL;
        }
        if (pGraphicsMemory != NULL)
        {
            SetProp(hWnd, _T(PROP_GRAPHICS_MEMORY), (HANDLE)NULL);
            delete pGraphicsMemory;
            pGraphicsMemory = NULL;
        }
        return (INT)(0);
    }
   
    static LRESULT CALLBACK CallBack_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);

        RECT rcWindow = { 0 };
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;

        switch (uMsg)
        {
        case WM_NCHITTEST:
        {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);
            ::ScreenToClient(hWnd, &pt);

            RECT rcClient;
            ::GetClientRect(hWnd, &rcClient);

            if (pt.x < rcClient.left + 20 && pt.y < rcClient.top + 20)//���Ͻ�,�ж��ǲ��������Ͻǣ����ǿ���ǰ�����ǲ��Ǽ�������϶��ķ�Χ�ڣ������ϱ��϶��ķ�Χ�ڣ��������жϷ�������
            {
                return HTTOPLEFT;
            }
            else if (pt.x > rcClient.right - 20 && pt.y < rcClient.top + 20)//���Ͻ�
            {
                return HTTOPRIGHT;
            }
            else if (pt.x<rcClient.left + 20 && pt.y>rcClient.bottom - 20)//���½�
            {
                return HTBOTTOMLEFT;
            }
            else if (pt.x > rcClient.right - 20 && pt.y > rcClient.bottom - 20)//���½�
            {
                return HTBOTTOMRIGHT;
            }
            else if (pt.x < rcClient.left + 20)
            {
                return HTLEFT;
            }
            else if (pt.x > rcClient.right - 20)
            {
                return HTRIGHT;
            }
            else if (pt.y < rcClient.top + 20)
            {
                return HTTOP;
            }if (pt.y > rcClient.bottom - 20)
            {
                return HTBOTTOM;          //�������ĸ����ϡ��¡������ĸ���
            }
            else
            {
                return HTCAPTION;
            }

            return (LRESULT)HTNOWHERE;
        }
        break;
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_DEADCHAR:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_SYSCHAR:
        case WM_SYSDEADCHAR:
        {
            switch (wParam)
            {
            case '1'://ׯ
            {
            }
            break;
            case '2'://��
            {
            }
            break;
            case '3'://��
            {
            }
            break;
            case '4'://ׯ����
            case '5'://�ж���
            case '7'://����
            case '9'://�˳�
            case '-'://�޸�
            case '+'://�¿���
            case '*'://ȡ��
            {
                MessageBox(hWnd, _T("1"), _T("Message"), MB_OK);
            }
            break;
            case VK_RETURN://�س�
            {
            }
            break;
            default:
                break;
            }
        }
        break;
        default:
        {
        }
        break;
        }
        return CallWindowProc((WNDPROC)GetWindowLongPtr(hWnd, GWLP_USERDATA), hWnd, uMsg, wParam, lParam);
    }
#define _TIMER_ID   1015
    static void CALLBACK TimerProc(HWND hWnd, UINT message, UINT_PTR iTimerID, DWORD dwTime)
    {
        // ��ʱ����ÿ���Ѿ��������̻�������һ״̬
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        
        DrawPie(pGraphicsMemory, hWnd);
        DrawWordArt(pGraphicsMemory);
		Gdiplus::Bitmap * _bitmap = GetPumpImage(0.0f, 100.0f, 50.0f, _T("KN"));
		if (_bitmap != NULL)
		{
            pGraphicsMemory->DrawImage(_bitmap,
		       Gdiplus::RectF(150, 0, _bitmap->GetWidth(), _bitmap->GetHeight()),
		       0, 0, _bitmap->GetWidth(), _bitmap->GetHeight(), Gdiplus::Unit::UnitPixel);
		   delete _bitmap;
		   _bitmap = NULL;
		}
				   
        HWND btnWnd = GetDlgItem(hWnd, IDOK);
        RECT rcBtn = { 0 };
        RECT rcWnd = { 0 };
        GetClientRect(hWnd, &rcWnd);
        GetWindowRect(btnWnd, &rcBtn);
        CRotateDialogWindow::Instance()->ScreenToClient(hWnd, (LPPOINT)&rcBtn, sizeof(rcBtn) / sizeof(POINT));
        HRGN hRgnWnd = CreateRectRgnIndirect(&rcWnd);
        HRGN hRgnBtn = CreateRectRgnIndirect(&rcBtn);
        if (hRgnWnd && hRgnBtn)
        {
            CombineRgn(hRgnWnd, hRgnWnd, hRgnBtn, RGN_XOR);
            InvalidateRgn(hWnd, hRgnWnd, FALSE);
        }
        if (hRgnWnd)
        {
            DeleteObject(hRgnWnd);
        }
        if (hRgnBtn)
        {
            DeleteObject(hRgnBtn);
        }
    }
    
    static INT_PTR CALLBACK CallBack_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);

        RECT rcWindow = { 0 };
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;

        switch (uMsg)
        {
        case WM_INITDIALOG:
        {
            InitAnimation(hWnd);
            SetTimer(hWnd, _TIMER_ID, 100, CRotateDialogWindow::TimerProc);
            ShowWindow(GetDlgItem(hWnd, IDC_STATIC), SW_HIDE);
            //ShowWindow(GetDlgItem(hWnd, IDOK), SW_HIDE);
            ShowWindow(GetDlgItem(hWnd, IDCANCEL), SW_HIDE);
            return (INT_PTR)FALSE;
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps = { 0 };
            HDC hDC = NULL;

            hDC = BeginPaint(hWnd, &ps);

            // TODO: Add any drawing code that uses hdc here...
            if (hDC != NULL)
            {
                pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
                if (pBitmapMemory != NULL)
                {
                    GetClientRect(hWnd, &rcWindow);
                    Gdiplus::Graphics(hDC).DrawImage(pBitmapMemory,
                        Gdiplus::RectF(0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top),
                        0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight(), Gdiplus::Unit::UnitPixel);
                }
            }

            EndPaint(hWnd, &ps);
        }
        break;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDOK:
            {
                m_AnimationType = (m_AnimationType + 1) % 4;
                m_ColorBack = RGB(rand() % 0x100, rand() % 0x100, rand() % 0x100);
                return (INT_PTR)TRUE;
            }
            break;
            case IDCANCEL:
            {
                KillTimer(hWnd, _TIMER_ID);
                EndDialog(hWnd, LOWORD(wParam));
                PostQuitMessage(WM_QUIT);
                return (INT_PTR)TRUE;
            }
            break;
            default:
            {
                
            }
            break;
            }
        }
        break;
        default:
        {

        }
        break;
        }

        return (INT_PTR)FALSE;
    }

};