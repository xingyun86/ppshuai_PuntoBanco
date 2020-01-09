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
class CParicles
{
#define PARICLES_LIVETIME   20
#define PARICLES_COUNTNUM   128
public:
    CParicles() {
        p = 0;
        done = false;
        memset(x, 0x00, sizeof(x));
        memset(y, 0x00, sizeof(y));
        memset(dx, 0x00, sizeof(dx));
        memset(dy, 0x00, sizeof(dy));
        memset(tm, 0x00, sizeof(tm));
    }
    virtual ~CParicles() {

    }

private:

    int p;// 位置
    bool done; // 是否
    float x[PARICLES_COUNTNUM], y[PARICLES_COUNTNUM]; // 粒子坐标
    float dx[PARICLES_COUNTNUM], dy[PARICLES_COUNTNUM]; // 粒子增量
    int tm[PARICLES_COUNTNUM]; // 粒子存活时间

public:

    // 获取当前状态下一粒子位置
    // 获取成功，返回真
    bool GetNext(int& tx, int& ty) {
        if (done) {            
            while (p < PARICLES_COUNTNUM && tm[p] <= 0) { 
                // 找到下一未消失粒子
                p++;
            }
            if (p < PARICLES_COUNTNUM) {
                tx = (int)x[p];
                ty = (int)y[p];
                p++;
                return true; // 获取成功
            }
        }
        return false;
    }
    // 烟花各粒子进入下一状态
    // 如粒子全部消失，则返回false
    bool DoNext() {
        if (done) {
            int c = 0;
            for (int i = 0; i < PARICLES_COUNTNUM; i++) {
                if (tm[i] > 0) { // 如果存活时间大于零
                    x[i] += dx[i]; // 改变粒子位置
                    y[i] += dy[i];
                    tm[i]--; // 存活时间减一
                }
                else {
                    c++;
                }
            }
            done = (c != PARICLES_COUNTNUM);
            p = 0;
        }

        return done;
    }
    bool IsDone() { 
        return done;
    }

    // 初始化，输入为烟花中心点
    void Init(int tx, int ty) {
        int count = 0;
        double d = 0.0f;
        srand(time(NULL));
        count = (PARICLES_COUNTNUM / 2) + rand() % (PARICLES_COUNTNUM / 2);
        for (int i = 0; i < PARICLES_COUNTNUM; i++) {
            if (i < count) {
                d = float(rand() % 628) / 100.0f; // 粒子移动角度
                x[i] = (float)tx;
                y[i] = (float)ty;
                dy[i] = float(rand() % 600) / 100.0f; // 粒子移动长度
                dx[i] = sin(d) * dy[i]; // 粒子x方向增量
                dy[i] = cos(d) * dy[i]; // 粒子y方向增量
                tm[i] = (PARICLES_LIVETIME / 2) + rand() % (PARICLES_LIVETIME / 2); // 粒子存活时间
            }
            else {
                tm[i] = 0;
            }
        }
        done = true;
        p = 0;
    }
};

/////////////////////////////////////////////////////////////////////////////////
//
class CEffectsDialogWindow : public CDialogWindow {
public:
    static CEffectsDialogWindow* Instance() {
        static CEffectsDialogWindow instance;
        return &instance;
    }
    virtual VOID Run(HINSTANCE hInstance)
    {
        DialogBoxRun(hInstance, 
            MAKEINTRESOURCE(IDD_PUNTOBANCO_DIALOG), 
            CEffectsDialogWindow::PuntoBancoDlgProc, 
            CEffectsDialogWindow::PuntoBancoWndproc,
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

        if (CEffectsDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapBackground, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_BACKGROUND)), _T(RES_PNG_TYPE_NAME)))
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
                pGraphicsMemory->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBilinear);

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

    static void muke_handler(HWND hWnd)
    {
        Gdiplus::Bitmap* pBitmapMemory = NULL;
        Gdiplus::Bitmap* pBitmapBackground = NULL;
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pBitmapMemory = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_BITMAP_MEMORY)));
        pBitmapBackground = reinterpret_cast<Gdiplus::Bitmap*>(GetProp(hWnd, _T(PROP_IMG_BACKGROUND)));
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        //图像木刻处理
        Gdiplus::Color color, colorTemp;
        int avg, temp;
        for (int i = 0; i < pBitmapBackground->GetWidth(); i++)
        {
            for (int j = 0; j < pBitmapBackground->GetHeight(); j++)
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
        //图像雕刻处理
        Gdiplus::Color color, colorTemp, colorLeft;
        for (int i = pBitmapBackground->GetWidth(); i > 0; i--)
        {
            for (int j = pBitmapBackground->GetHeight(); j > 0; j--)
            {
                pBitmapBackground->GetPixel(i, j, &color);
                pBitmapBackground->GetPixel(i - 1, j - 1, &colorLeft);//分量值之差被限制在67-128之间，更改这两个值会得到不同的效果
                float r = max(67, min(255, abs(color.GetRed() - colorLeft.GetRed() + 128)));
                float g = max(67, min(255, abs(color.GetGreen() - colorLeft.GetGreen() + 128)));
                float b = max(67, min(255, abs(color.GetBlue() - colorLeft.GetBlue() + 128)));
                colorTemp.SetValue(color.MakeARGB(255, r, g, b));//将计算后的之写入到位图
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
        //水平百叶窗
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
        //垂直百叶窗
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
    static CParicles cyh[20];
    static int col[20];
    static int pc;

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
                rcWindow.top = 60;
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
                rcWindow.top = 60;
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
                rcWindow.top = 60;
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
            {
                MessageBox(hWnd, _T("1"), _T("Message"), MB_OK);
            }
            break;
            case VK_RETURN://回车
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
#define _TIMER_ID   1015
    static void CALLBACK TimerProc(HWND hWnd, UINT message, UINT_PTR iTimerID, DWORD dwTime)
    {
        // 定时器，每次已经产生的烟花进入下一状态
        for (int i = 0; i < 20; i++) {
            if (cyh[i].IsDone()) {
                cyh[i].DoNext();
            }
        }
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
            SetTimer(hWnd, _TIMER_ID, 100, CEffectsDialogWindow::TimerProc);
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

                    int i, x, y;
                    Gdiplus::Color c;
                    for (i = 0; i < 20; i++) {
                        if (cyh[i].IsDone()) {
                            while (cyh[i].GetNext(x, y)) {
                                switch (col[i]) {
                                case 0:
                                    c = Gdiplus::Color(255, 255, 255);
                                    break;
                                case 1:
                                    c = Gdiplus::Color(255, 0, 0);
                                    break;
                                case 2:
                                    c = Gdiplus::Color(255, 255, 0);
                                    break;
                                case 3:
                                    c = Gdiplus::Color(128, 128, 255);
                                    break;
                                case 4:
                                    c = Gdiplus::Color(128, 255, 128);
                                    break;
                                }
                                Gdiplus::SolidBrush brush(c);
                                Gdiplus::Graphics(hDC).FillEllipse(&brush, Gdiplus::Rect(x, y, 4, 4));
                            }
                        }
                    }
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
                POINT point = { 0 };
                GetCursorPos(&point);
                ScreenToClient(hWnd, &point);
                GetClientRect(hWnd, &rcWindow);
                point.x = 10 + rand() % (rcWindow.right - rcWindow.left - 10);
                point.y = 10 + rand() % (rcWindow.bottom - rcWindow.top - 10);
                // 左键点击，产生一烟花
                cyh[pc].Init(point.x - 10, point.y - 10);
                col[pc] = rand() % 5;
                pc++;
                if (pc == 20) {
                    pc = 0;
                }
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

CParicles CEffectsDialogWindow::cyh[20];
int CEffectsDialogWindow::col[20];
int CEffectsDialogWindow::pc = 0;