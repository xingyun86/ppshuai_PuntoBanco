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
        DialogBoxRun(hInstance, 
            MAKEINTRESOURCE(IDD_PUNTOBANCO_DIALOG), 
            CPuntoBancoDialogWindow::CallBack_DlgProc,
            CPuntoBancoDialogWindow::CallBack_WndProc,
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

    static void muke_handler(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        //ͼ��ľ�̴���
        Gdiplus::Color color, colorTemp;
        int i, j, avg, temp;
        for (i = 0; i < pBitmapBackground->GetWidth(); i++)
        {
            for (j = 0; j < pBitmapBackground->GetHeight(); j++)
            {
                pBitmapBackground->GetPixel(i, j, &color);
                avg = (color.GetRed() + color.GetGreen() + color.GetBlue()) / 3;
                if (192 >= avg)
                {
                    temp = 255;
                }
                else if (128 < avg && avg < 192)
                {
                    temp = 150;
                }
                else if (64 <= avg && avg <= 128)
                {
                    temp = 150;
                }
                else if (avg < 64)
                {
                    temp = 8;
                }
                colorTemp.SetValue(color.MakeARGB(255, temp, temp, temp));
                pBitmapBackground->SetPixel(i, j, colorTemp);
            }
        }
        pGraphicsMemory->DrawImage(pBitmapBackground,
            Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
            0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    static void diaoke_handler(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        //ͼ���̴���
        Gdiplus::Color color, colorTemp, colorLeft;
        for (int i = pBitmapBackground->GetWidth(); i > 0; i--)
        {
            for (int j = pBitmapBackground->GetHeight(); j > 0; j--)
            {
                pBitmapBackground->GetPixel(i, j, &color);
                pBitmapBackground->GetPixel(i - 1, j - 1, &colorLeft);//����ֵ֮�������67-128֮�䣬����������ֵ��õ���ͬ��Ч��
                float r = max(67, min(255, abs(color.GetRed() - colorLeft.GetRed() + 128)));
                float g = max(67, min(255, abs(color.GetGreen() - colorLeft.GetGreen() + 128)));
                float b = max(67, min(255, abs(color.GetBlue() - colorLeft.GetBlue() + 128)));
                colorTemp.SetValue(color.MakeARGB(255, r, g, b));//��������֮д�뵽λͼ
                pBitmapBackground->SetPixel(i, j, colorTemp);
            }
        }
        pGraphicsMemory->DrawImage(pBitmapBackground,
            Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
            0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    static void shuipingbaiyechuang_handler(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        //ˮƽ��Ҷ��
        int i, j, n = 12;
        for (j = 0; j <= pBitmapBackground->GetHeight() / n; j++)
        {
            for (i = 0; i <= n; i++)
            {
                HDC hDC = GetDC(hWnd);
                Gdiplus::ImageAttributes ImgAttr;
                Gdiplus::Graphics graphics(hDC);
                graphics.DrawImage(pBitmapBackground, Gdiplus::Rect(0, i * pBitmapBackground->GetHeight() / n, pBitmapBackground->GetWidth(), j), 0, i * pBitmapBackground->GetHeight() / n, pBitmapBackground->GetWidth(), j, Gdiplus::Unit::UnitPixel, &ImgAttr);

                ReleaseDC(hWnd, hDC);
            }
        }
        pGraphicsMemory->DrawImage(pBitmapBackground,
            Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
            0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    static void chuizhibaiyechuang_handler(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        //��ֱ��Ҷ��
        int i, j, n = 28;
        for (i = 0; i <= pBitmapBackground->GetWidth() / n; i++)
        {
            for (j = 0; j <= n; j++)
            {
                HDC hDC = GetDC(hWnd);
                Gdiplus::ImageAttributes ImgAttr;
                Gdiplus::Graphics graphics(hDC);
                graphics.DrawImage(pBitmapBackground, Gdiplus::Rect(j * pBitmapBackground->GetWidth() / n, 0, i, pBitmapBackground->GetHeight()), j * pBitmapBackground->GetWidth() / n, 0, i, pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel, &ImgAttr);
            
                ReleaseDC(hWnd, hDC);
            }
        }
        pGraphicsMemory->DrawImage(pBitmapBackground,
            Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
            0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
        InvalidateRect(hWnd, NULL, FALSE);
    }

    static LRESULT CALLBACK CallBack_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));

                Gdiplus::Pen redPen(Gdiplus::Color(255, 0, 0));
                pGraphicsMemory->DrawEllipse(&redPen, Gdiplus::RectF(3, 64, 17, 17));

                Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 0, 0));
                pGraphicsMemory->FillEllipse(&redBrush, Gdiplus::RectF(65, 64, 18, 18));

                Gdiplus::SolidBrush redFontBrush(Gdiplus::Color(255, 0, 0));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("ׯ")), -1, &font, Gdiplus::RectF(127, 66, 18, 18), NULL, &redFontBrush);
               
                GetClientRect(hWnd, &rcWindow);
                rcWindow.top = 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
            }
            break;
            case '2'://��
            {
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
                Gdiplus::Pen bluePen(Gdiplus::Color(0, 0, 255));
                pGraphicsMemory->DrawEllipse(&bluePen, Gdiplus::RectF(24, 64, 17, 17));
               
                Gdiplus::SolidBrush blueBrush(Gdiplus::Color(0, 0, 255));
                pGraphicsMemory->FillEllipse(&blueBrush, Gdiplus::RectF(86, 64, 18, 18));
                
                Gdiplus::SolidBrush blueFontBrush(Gdiplus::Color(0, 0, 255));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("��")), -1, &font, Gdiplus::RectF(148, 66, 18, 18), NULL, &blueFontBrush);

                GetClientRect(hWnd, &rcWindow);
                rcWindow.top = 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
            }
            break;
            case '3'://��
            {
                pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
                Gdiplus::Pen greenPen(Gdiplus::Color(0, 255, 0));
                pGraphicsMemory->DrawEllipse(&greenPen, Gdiplus::RectF(45, 64, 17, 17));

                Gdiplus::SolidBrush greenBrush(Gdiplus::Color(0, 255, 0));
                pGraphicsMemory->FillEllipse(&greenBrush, Gdiplus::RectF(107, 64, 18, 18));

                Gdiplus::SolidBrush greenFontBrush(Gdiplus::Color(0, 255, 0));
                Gdiplus::FontFamily fontfamily(CStringW(_T("Arial")));
                Gdiplus::Font font(&fontfamily, 10, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPoint);
                pGraphicsMemory->DrawString(CStringW(_T("��")), -1, &font, Gdiplus::RectF(169, 66, 18, 18), NULL, &greenFontBrush);

                GetClientRect(hWnd, &rcWindow);
                rcWindow.top = 60;
                InvalidateRect(hWnd, &rcWindow, FALSE);
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
                //muke_handler(hWnd);
                //diaoke_handler(hWnd);
                //shuipingbaiyechuang_handler(hWnd);
                chuizhibaiyechuang_handler(hWnd);
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
    static INT_PTR CALLBACK CallBack_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            ShowWindow(GetDlgItem(hWnd, IDC_STATIC), SW_HIDE);
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

