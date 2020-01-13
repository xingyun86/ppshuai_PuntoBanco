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
    COLORREF clrOut;//外圈颜色
    COLORREF clrIn;//内圈颜色
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
//绘制圆饼
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

    //计算外圈、内圈位置
    Gdiplus::Rect rcOut(m_Rect);
    Gdiplus::Rect rcIn(rcOut);
    rcIn.Inflate(-m_ItemSize, -m_ItemSize);
    //--------------------------------------------------------
    //先画出外圈小方块
    float fStartAngle = -90;//起始绘制角度
    float fSweepAngle = 360 / ANIMATION_COUNTSIZE;//每小块的角度
    for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
    {
        clr.SetFromCOLORREF(m_AnimationArray[i].clrOut);
        pBrush->SetColor(clr);
        pGraphicsTmp->FillPie(pBrush, rcOut, fStartAngle, fSweepAngle - m_MarginAngle);
        fStartAngle = fStartAngle + fSweepAngle;
    }
    //--------------------------------------------------------
    //画出内圈小方块;
    fStartAngle = -90;
    for (int i = 0; i < ANIMATION_COUNTSIZE; i++)
    {
        clr.SetFromCOLORREF(m_AnimationArray[i].clrIn);
        pBrush->SetColor(clr);
        pGraphicsTmp->FillPie(pBrush, rcIn, fStartAngle, fSweepAngle - m_MarginAngle);
        fStartAngle = fStartAngle + fSweepAngle;
    }
    //--------------------------------------------------------
    //画出高亮色块
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
    //画出中间圆心，用控件底色填充
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
            for (int i = ANIMATION_COUNTSIZE - 1; i > 0; i--)
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

            if (pt.x < rcClient.left + 20 && pt.y < rcClient.top + 20)//左上角,判断是不是在左上角，就是看当前坐标是不是即在左边拖动的范围内，又在上边拖动的范围内，其它角判断方法类似
            {
                return HTTOPLEFT;
            }
            else if (pt.x > rcClient.right - 20 && pt.y < rcClient.top + 20)//右上角
            {
                return HTTOPRIGHT;
            }
            else if (pt.x<rcClient.left + 20 && pt.y>rcClient.bottom - 20)//左下角
            {
                return HTBOTTOMLEFT;
            }
            else if (pt.x > rcClient.right - 20 && pt.y > rcClient.bottom - 20)//右下角
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
                return HTBOTTOM;          //以上这四个是上、下、左、右四个边
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
            case '1'://庄
            {
            }
            break;
            case '2'://闲
            {
            }
            break;
            case '3'://和
            {
            }
            break;
            case '4'://庄对子
            case '5'://闲对子
            case '7'://设置
            case '9'://退出
            case '-'://修改
            case '+'://新开局
            case '*'://取消
            {
                MessageBox(hWnd, _T("1"), _T("Message"), MB_OK);
            }
            break;
            case VK_RETURN://回车
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
        // 定时器，每次已经产生的烟花进入下一状态
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        DrawPie(pGraphicsMemory, hWnd);

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