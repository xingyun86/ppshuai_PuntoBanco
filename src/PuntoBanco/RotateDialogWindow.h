#pragma once

#include "DialogWindow.h"
#include "RotateAnimation.h"


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
            CRotateDialogWindow::PuntoBancoDlgProc,
            CRotateDialogWindow::PuntoBancoWndproc,
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
        Gdiplus::Bitmap* pBitmapTop = NULL;
        Gdiplus::Bitmap* pBitmapMiddle = NULL;
        Gdiplus::Bitmap* pBitmapBottom = NULL;
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
            if (pBitmapMemory != NULL)
            {
                SetProp(hWnd, _T(PROP_GRAPHICS_MEMORY), (HANDLE)(pGraphicsMemory));
                pGraphicsMemory->SetCompositingMode(Gdiplus::CompositingModeSourceOver);
                pGraphicsMemory->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
                pGraphicsMemory->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

                pGraphicsMemory->DrawImage(pBitmapMemory,
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
   
    static LRESULT CALLBACK PuntoBancoWndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
       
        //InvalidateRect(hWnd, NULL, FALSE);

        HWND btnWnd = GetDlgItem(hWnd, IDOK);
        RECT rcBtn = { 0 };
        RECT rcWnd = { 0 };
        GetClientRect(hWnd, &rcWnd);
        GetWindowRect(btnWnd, &rcBtn);
        ScreenToClient(hWnd, (LPPOINT)&rcBtn + 0);
        ScreenToClient(hWnd, (LPPOINT)&rcBtn + 1);
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
    static INT_PTR CALLBACK PuntoBancoDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            srand(time(NULL));
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

    CRotateAnimation m_RotateAnimation;
};