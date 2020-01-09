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
#define PROP_IMG_TOP            "IMG_TOP"
#define PROP_IMG_MIDDLE         "IMG_MIDDLE"
#define PROP_IMG_BOTTOM         "IMG_BOTTOM"
#define PROP_BITMAP_MEMORY      "BITMAP_MEMORY"
#define PROP_GRAPHICS_MEMORY    "GRAPHICS_MEMORY"
/////////////////////////////////////////////////////////////////////////////////
//
class CPuntoBancoDialogWindow : public CDialogWindow {
public:
    static CPuntoBancoDialogWindow* Instance() {
        static CPuntoBancoDialogWindow instance;
        return &instance;
    }
    virtual VOID Run(HINSTANCE hInstance)
    {
        DialogBoxRun(hInstance, MAKEINTRESOURCE(IDD_PUNTOBANCO_DIALOG), PuntoBancoDlgProc, PuntoBancoWndproc,
            [](HWND _hWnd) {
                SetWindowPos(_hWnd, HWND_DESKTOP, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME | SWP_HIDEWINDOW);
                StartupResources(_hWnd);
            },
            [](HWND _hWnd) {
                CleanupResources(_hWnd);
            });
    }
public:
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

        if (CPuntoBancoDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapBackground, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_BACKGROUND)), _T(RES_PNG_TYPE_NAME)))
        {
            SetProp(hWnd, _T(PROP_IMG_BACKGROUND), (HANDLE)pBitmapBackground);
        }
        if (CPuntoBancoDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapTop, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_TOP)), _T(RES_PNG_TYPE_NAME)))
        {
            SetProp(hWnd, _T(PROP_IMG_TOP), (HANDLE)pBitmapTop);
        }
        if (CPuntoBancoDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapMiddle, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_MIDDLE)), _T(RES_PNG_TYPE_NAME)))
        {
            SetProp(hWnd, _T(PROP_IMG_MIDDLE), (HANDLE)pBitmapMiddle);
        }
        if (CPuntoBancoDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapBottom, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_BOTTOM)), _T(RES_PNG_TYPE_NAME)))
        {
            SetProp(hWnd, _T(PROP_IMG_BOTTOM), (HANDLE)pBitmapBottom);
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
                pGraphicsMemory->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBilinear);

                pGraphicsMemory->DrawImage(pBitmapBackground,
                    Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
                    0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);

                pGraphicsMemory->DrawImage(pBitmapTop,
                    Gdiplus::RectF(0, 60, pBitmapTop->GetWidth(), pBitmapTop->GetHeight()),
                    0, 0, pBitmapTop->GetWidth(), pBitmapTop->GetHeight(), Gdiplus::Unit::UnitPixel);

                pGraphicsMemory->DrawImage(pBitmapMiddle,
                    Gdiplus::RectF(0, pBitmapTop->GetHeight() + 10 + 60, pBitmapMiddle->GetWidth(), pBitmapMiddle->GetHeight()),
                    0, 0, pBitmapMiddle->GetWidth(), pBitmapMiddle->GetHeight(), Gdiplus::Unit::UnitPixel);

                pGraphicsMemory->DrawImage(pBitmapBottom,
                    Gdiplus::RectF(0, pBitmapTop->GetHeight() + 10 + pBitmapMiddle->GetHeight() + 10 + 60, pBitmapBottom->GetWidth(), pBitmapBottom->GetHeight()),
                    0, 0, pBitmapBottom->GetWidth(), pBitmapBottom->GetHeight(), Gdiplus::Unit::UnitPixel);
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
        Gdiplus::Bitmap* pBitmapTop = NULL;
        Gdiplus::Bitmap* pBitmapMiddle = NULL;
        Gdiplus::Bitmap* pBitmapBottom = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;

        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pBitmapTop = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_TOP)));
        pBitmapMiddle = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_MIDDLE)));
        pBitmapBottom = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BOTTOM)));
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));

        if (pBitmapBackground != NULL)
        {
            SetProp(hWnd, _T(PROP_IMG_BACKGROUND), (HANDLE)NULL);
            delete pBitmapBackground;
            pBitmapBackground = NULL;
        }
        if (pBitmapTop != NULL)
        {
            SetProp(hWnd, _T(PROP_IMG_TOP), (HANDLE)NULL);
            delete pBitmapTop;
            pBitmapTop = NULL;
        }
        if (pBitmapMiddle != NULL)
        {
            SetProp(hWnd, _T(PROP_IMG_MIDDLE), (HANDLE)NULL);
            delete pBitmapMiddle;
            pBitmapMiddle = NULL;
        }
        if (pBitmapBottom != NULL)
        {
            SetProp(hWnd, _T(PROP_IMG_BOTTOM), (HANDLE)NULL);
            delete pBitmapBottom;
            pBitmapBottom = NULL;
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
        Gdiplus::Bitmap* pBitmapTop = NULL;
        Gdiplus::Bitmap* pBitmapMiddle = NULL;
        Gdiplus::Bitmap* pBitmapBottom = NULL;
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
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));

                Gdiplus::Pen redPen(Gdiplus::Color(255, 0, 0));
                pGraphicsMemory->DrawEllipse(&redPen, Gdiplus::RectF(3, 64, 17, 17));

                Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 0, 0));
                pGraphicsMemory->FillEllipse(&redBrush, Gdiplus::RectF(65, 64, 18, 18));

                Gdiplus::SolidBrush redFontBrush(Gdiplus::Color(255, 0, 0));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("庄")), -1, &font, Gdiplus::RectF(127, 66, 18, 18), NULL, &redFontBrush);
               
                GetClientRect(hWnd, &rcWindow);
                rcWindow.top == 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
            }
            break;
            case '2'://闲
            {
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
                Gdiplus::Pen bluePen(Gdiplus::Color(0, 0, 255));
                pGraphicsMemory->DrawEllipse(&bluePen, Gdiplus::RectF(24, 64, 17, 17));
               
                Gdiplus::SolidBrush blueBrush(Gdiplus::Color(0, 0, 255));
                pGraphicsMemory->FillEllipse(&blueBrush, Gdiplus::RectF(86, 64, 18, 18));
                
                Gdiplus::SolidBrush blueFontBrush(Gdiplus::Color(0, 0, 255));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("闲")), -1, &font, Gdiplus::RectF(148, 66, 18, 18), NULL, &blueFontBrush);

                GetClientRect(hWnd, &rcWindow);
                rcWindow.top == 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
            }
            break;
            case '3'://和
            {
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
                Gdiplus::Pen greenPen(Gdiplus::Color(0, 255, 0));
                pGraphicsMemory->DrawEllipse(&greenPen, Gdiplus::RectF(45, 64, 17, 17));

                Gdiplus::SolidBrush greenBrush(Gdiplus::Color(0, 255, 0));
                pGraphicsMemory->FillEllipse(&greenBrush, Gdiplus::RectF(107, 64, 18, 18));

                Gdiplus::SolidBrush greenFontBrush(Gdiplus::Color(0, 255, 0));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("和")), -1, &font, Gdiplus::RectF(169, 66, 18, 18), NULL, &greenFontBrush);

                GetClientRect(hWnd, &rcWindow);
                rcWindow.top == 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
            }
            break;
            case '4'://庄对子
            case '5'://闲对子
            case '7'://设置
            case '9'://退出
            case '-'://修改
            case '+'://新开局
            case '*'://取消
            case VK_RETURN://回车
            {
                MessageBox(hWnd, _T("1"), _T("Message"), MB_OK);
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
    static INT_PTR CALLBACK PuntoBancoDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);

        HDC hDC = NULL;
        RECT rcWindow = { 0 };
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Bitmap* pBitmapTop = NULL;
        Gdiplus::Bitmap* pBitmapMiddle = NULL;
        Gdiplus::Bitmap* pBitmapBottom = NULL;
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;

        switch (uMsg)
        {
        case WM_INITDIALOG:
        {
            ShowWindow(GetDlgItem(hWnd, IDOK), SW_HIDE);
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
                GetClientRect(hWnd, &rcWindow);
                pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
                if (pBitmapMemory != NULL)
                {
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

