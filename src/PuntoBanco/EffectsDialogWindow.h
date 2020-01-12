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

    int p;// λ��
    bool done; // �Ƿ�
    float x[PARICLES_COUNTNUM], y[PARICLES_COUNTNUM]; // ��������
    float dx[PARICLES_COUNTNUM], dy[PARICLES_COUNTNUM]; // ��������
    int tm[PARICLES_COUNTNUM]; // ���Ӵ��ʱ��

public:

    // ��ȡ��ǰ״̬��һ����λ��
    // ��ȡ�ɹ���������
    bool GetNext(int& tx, int& ty) {
        if (done) {            
            while (p < PARICLES_COUNTNUM && tm[p] <= 0) { 
                // �ҵ���һδ��ʧ����
                p++;
            }
            if (p < PARICLES_COUNTNUM) {
                tx = (int)x[p];
                ty = (int)y[p];
                p++;
                return true; // ��ȡ�ɹ�
            }
        }
        return false;
    }
    // �̻������ӽ�����һ״̬
    // ������ȫ����ʧ���򷵻�false
    bool DoNext() {
        if (done) {
            int c = 0;
            for (int i = 0; i < PARICLES_COUNTNUM; i++) {
                if (tm[i] > 0) { // ������ʱ�������
                    x[i] += dx[i]; // �ı�����λ��
                    y[i] += dy[i];
                    tm[i]--; // ���ʱ���һ
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

    // ��ʼ��������Ϊ�̻����ĵ�
    void Init(int tx, int ty) {
        int count = 0;
        double d = 0.0f;
        srand(time(NULL));
        count = (PARICLES_COUNTNUM / 2) + rand() % (PARICLES_COUNTNUM / 2);
        for (int i = 0; i < PARICLES_COUNTNUM; i++) {
            if (i < count) {
                d = float(rand() % 628) / 100.0f; // �����ƶ��Ƕ�
                x[i] = (float)tx;
                y[i] = (float)ty;
                dy[i] = float(rand() % 600) / 100.0f; // �����ƶ�����
                dx[i] = sin(d) * dy[i]; // ����x��������
                dy[i] = cos(d) * dy[i]; // ����y��������
                tm[i] = (PARICLES_LIVETIME / 2) + rand() % (PARICLES_LIVETIME / 2); // ���Ӵ��ʱ��
            }
            else {
                tm[i] = 0;
            }
        }
        done = true;
        p = 0;
    }
};
/// <summary>
/// ����ɫ������л��
/// </summary>
/// <param name="colors"></param>
/// <returns></returns>
Gdiplus::Color BlendColor(Gdiplus::Color * colors, UINT nCount)
{
    if (nCount <= 0)
    {
        return Gdiplus::Color::Transparent;
    }

    ULONG asum = 0, rsum = 0, gsum = 0, bsum = 0;

    for (int i = 0, len = nCount; i < len; i++)
    {
        asum += colors[i].GetA();
        rsum += (ULONG)(colors[i].GetA() * colors[i].GetR());
        gsum += (ULONG)(colors[i].GetG() * colors[i].GetA());
        bsum += (ULONG)(colors[i].GetB() * colors[i].GetA());
    }

    if (asum == 0)
    {
        return Gdiplus::Color::Transparent;
    }
    rsum /= asum;
    gsum /= asum;
    bsum /= asum;
    asum /= (ULONG)nCount;
    return Gdiplus::Color((int)asum, (int)rsum, (int)gsum, (int)bsum);
}

/// <summary>
/// ë����Ч��
/// </summary>
/// <param name="srcBmp">ԴͼƬ</param>
/// <param name="minRadius">��С��ɢ�뾶</param>
/// <param name="maxRadius">�����ɢ�뾶</param>
/// <param name="samples">��������</param>
/// <returns></returns>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif
Gdiplus::Bitmap * FrostedEffect(Gdiplus::Bitmap * srcBmp, int minRadius, int maxRadius, int nSamples)
{
    int width = srcBmp->GetWidth();
    int height = srcBmp->GetHeight();
    Gdiplus::Bitmap * targBmp = new Gdiplus::Bitmap(width, height, srcBmp->GetPixelFormat());
    if (targBmp != NULL)
    {
        Gdiplus::Rect rect(0, 0, width, height);
        Gdiplus::BitmapData srcData;
        srcBmp->LockBits(&rect, Gdiplus::ImageLockMode::ImageLockModeRead, srcBmp->GetPixelFormat(), &srcData);

        Gdiplus::BitmapData targData;
        targBmp->LockBits(&rect, Gdiplus::ImageLockMode::ImageLockModeWrite, targBmp->GetPixelFormat(), &targData);

        int pxsize = Gdiplus::GetPixelFormatSize(srcBmp->GetPixelFormat()) / 8;//���ش�С

        bool bAlpha = Gdiplus::IsAlphaPixelFormat(srcBmp->GetPixelFormat());

        int offset = srcData.Stride - srcData.Width * pxsize;

        srand(time(0));
        Gdiplus::Color* sampleColors = new Gdiplus::Color[nSamples];
        if(sampleColors != NULL)
        {
            byte* srcptr = (byte*)srcData.Scan0;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    for (int s = 0; s < nSamples; s++)
                    {
                        double d = minRadius + (rand() % (maxRadius - minRadius + 1));
                        double angle = M_PI * 2 * (rand() / double(RAND_MAX));
                        double p = sin(angle);
                        int samh = (int)(i + sin(angle) * d);
                        int samw = (int)(j + cos(angle) * d);
                        samh = samh < 0 ? 0 : (samh > height - 1 ? height - 1 : samh);
                        samw = samw < 0 ? 0 : (samw > width ? width : samw);
                        byte* ptr = srcptr + samh * srcData.Stride + samw * pxsize;
                        if (bAlpha)
                        {
                            sampleColors[s] = Gdiplus::Color(*(ptr + 3), *(ptr + 2), *(ptr + 1), *ptr);
                        }
                        else
                        {
                            sampleColors[s] = Gdiplus::Color(*(ptr + 2), *(ptr + 1), *ptr);
                        }
                    }

                    Gdiplus::Color col = BlendColor(sampleColors, nSamples);
                    byte* targptr = (byte*)targData.Scan0 + srcData.Stride * i + j * pxsize;
                    *targptr = col.GetB();
                    *(targptr + 1) = col.GetG();
                    *(targptr + 2) = col.GetR();
                    if (bAlpha)
                    {
                        *(targptr + 3) = col.GetA();
                    }
                }
            }
            delete sampleColors;
            sampleColors = NULL;
        }

        srcBmp->UnlockBits(&srcData);

        targBmp->UnlockBits(&targData);
    }

    return targBmp;

}
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
            CEffectsDialogWindow::CallBack_DlgProc, 
            CEffectsDialogWindow::CallBack_WndProc,
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

        if (CEffectsDialogWindow::Instance()->GdiplusLoadBitmapFromResource(&pBitmapBackground, GetModuleHandle(NULL), (MAKEINTRESOURCE(IDB_PNG_BACKGROUND)), _T(RES_PNG_TYPE_NAME)))
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

                Gdiplus::Bitmap* pBitmapForstedEffect = FrostedEffect(pBitmapBackground, 5, 8, 10);
                if (pBitmapForstedEffect != NULL)
                {
                    pGraphicsMemory->DrawImage(pBitmapForstedEffect,
                        Gdiplus::RectF(0, 0, pBitmapMemory->GetWidth(), pBitmapMemory->GetHeight()),
                        0, 0, pBitmapBackground->GetWidth(), pBitmapBackground->GetHeight(), Gdiplus::Unit::UnitPixel);
                    delete pBitmapForstedEffect;
                }
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
  
    static void yinying_handler(HWND hWnd)
    {
        Gdiplus::Graphics* pGraphicsMemory = NULL;
        pGraphicsMemory = reinterpret_cast<Gdiplus::Graphics*>(GetProp(hWnd, _T(PROP_GRAPHICS_MEMORY)));
        
        RECT rcWnd = { 0 };
        CStringW strTxt("19:20:30");

        GetClientRect(hWnd, &rcWnd);
        Gdiplus::RectF         desRC(rcWnd.left, rcWnd.top, (rcWnd.right - rcWnd.left) / 2, (rcWnd.bottom - rcWnd.top) / 4);
        Gdiplus::PointF        txtPos(0, 0);
        Gdiplus::FontFamily    fontFamily(L"Times New Roman");
        Gdiplus::Font font(&fontFamily, 100, Gdiplus::FontStyle::FontStyleBold, Gdiplus::Unit::UnitPixel);
        
        Gdiplus::Bitmap bmpBack(desRC.Width, desRC.Height, pGraphicsMemory);

        Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(&bmpBack);

        //1.0 ��䱳��ɫ
        g->FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color::LightSlateGray), desRC);

        //2.0 ����һ��С�ߴ���ڴ�λͼ���������ĳ���Ϊ�ܳߴ��1/4
        Gdiplus::Bitmap bmp(bmpBack.GetWidth() / 2, bmpBack.GetHeight() / 2, g);

        //2.1 ���û���ģʽΪ������ģʽ
        Gdiplus::Graphics* pTempG = Gdiplus::Graphics::FromImage(&bmp);
        pTempG->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);

        //2.2 ����һ������ʹ����Ϊԭ����1/4����Ӱ����ҲΪ��Ҫ�����ı���1/4����
        Gdiplus::Matrix mx((float)bmp.GetWidth() / bmpBack.GetWidth(), 0, 0, (float)bmp.GetHeight() / bmpBack.GetHeight(), 3, 3);
        pTempG->SetTransform(&mx);
        pTempG->RotateTransform(6);

        //2.3 ��λͼ�ϻ����ı���ʹ����͸���ȵĻ��ʣ�����50%͸����
        pTempG->DrawString(strTxt, -1, &font, txtPos, NULL, &Gdiplus::SolidBrush(Gdiplus::Color(128, 0, 0, 0)));

        //3.1 ��ֵģʽΪ������˫���β�ֵ������ֵ���ǳ���Ҫ����Ϊ˫���β�ֵʹ�ı��ı�ģ���������ͳ�����Ӱ���ӰЧ��
        g->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeHighQualityBicubic);

        //3.2 ���û���ģʽΪ������ģʽ�Ա�֤��ȷ�ķ�Χ
        g->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);

        //3.3 ��λͼ��ʾ����Ļ�ϣ������������϶��Ŵ�4��
        g->DrawImage(&bmp, desRC, 0, 0, bmp.GetWidth(), bmp.GetHeight(), Gdiplus::Unit::UnitPixel);

        //3.4 ���ı����Ƶ���ͼƽ����, ʹ�ð�ɫ����      
        g->RotateTransform(6);
        g->DrawString(strTxt, -1, &font, txtPos, NULL, &Gdiplus::SolidBrush(Gdiplus::Color::White));

        pGraphicsMemory->DrawImage(&bmpBack, desRC, 0, 0, bmpBack.GetWidth(), bmpBack.GetHeight(), Gdiplus::Unit::UnitPixel);

        //4.0 �ͷ��ڴ�
        if (NULL != pTempG)
        {
            delete pTempG;
            pTempG = NULL;
        }
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
    static CParicles cyh[20];
    static int col[20];
    static int pc;

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
                //chuizhibaiyechuang_handler(hWnd);
                yinying_handler(hWnd);
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
        CEffectsDialogWindow::Instance()->ScreenToClient(hWnd, (LPPOINT)&rcBtn, sizeof(rcBtn)/sizeof(POINT));
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
                CEffectsDialogWindow::Instance()->ScreenToClient(hWnd, (LPPOINT)&point, sizeof(point) / sizeof(POINT));

                GetClientRect(hWnd, &rcWindow);
                point.x = 10 + rand() % (rcWindow.right - rcWindow.left - 10);
                point.y = 10 + rand() % (rcWindow.bottom - rcWindow.top - 10);
                // ������������һ�̻�
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