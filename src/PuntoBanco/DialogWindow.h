#pragma once

#include <windows.h>
#include <windowsx.h>
#include <atlimage.h>

class CDialogWindow {
    typedef VOID(*PFN_CALLBACK)(HWND);
protected:
    INT DialogBoxRun(HINSTANCE hInstance,
        LPCTSTR lpTemplateName = MAKEINTRESOURCE(NULL),
        DLGPROC dlgProc = DlgProc,
        WNDPROC wndProc = WndProc,
        PFN_CALLBACK cbInit = NULL,
        PFN_CALLBACK cbExit = NULL,
        HWND hParent = NULL,
        LPARAM lParam = NULL)
    {
        INT nResult = (-1);
        ULONG_PTR ulongPtrToken = NULL;
        Gdiplus::Status status = (Gdiplus::Status::Ok);
        Gdiplus::GdiplusStartupInput gdiplusStartupInput = { 0 };
        Gdiplus::GdiplusStartupOutput gdiplusStartupOutput = { 0 };
        status = Gdiplus::GdiplusStartup(&ulongPtrToken, &gdiplusStartupInput, &gdiplusStartupOutput);
        if (status == Gdiplus::Status::Ok)
        {
            HWND hWnd = CreateDialogParam(hInstance, lpTemplateName, hParent, dlgProc, lParam);
            if (hWnd != NULL)
            {
                SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)wndProc));

                if (cbInit != NULL)
                {
                    cbInit(hWnd);
                }

                ShowWindow(hWnd, SW_SHOW);

                MessageProcess(hWnd);

                if (cbExit != NULL)
                {
                    cbExit(hWnd);
                }

                DestroyWindow(hWnd);
                nResult = (0);
            }
            //nResult = (INT)DialogBox(hInstance, MAKEINTRESOURCE(IDD_PUNTOBANCO_DIALOG), NULL, PuntoBancoCallback);
            Gdiplus::GdiplusShutdown(ulongPtrToken);
            ulongPtrToken = NULL;
        }

        return nResult;
    }
    bool GdiplusLoadBitmapFromResource(Gdiplus::Bitmap** pBitmap, HMODULE hInstance, LPCTSTR pName, LPCTSTR pType)
    {
        HRSRC hResource = NULL;
        DWORD dwImageSize = 0L;
        LPVOID lpResourceData = NULL;
        HGLOBAL m_hGlobal = NULL;
        LPVOID lpBuffer = NULL;
        IStream* pIStream = NULL;

        hResource = ::FindResource(hInstance, pName, pType);
        if (!hResource)
        {
            return false;
        }
        dwImageSize = ::SizeofResource(hInstance, hResource);
        if (!dwImageSize)
        {
            return false;
        }
        lpResourceData = ::LockResource(::LoadResource(hInstance, hResource));
        if (!lpResourceData)
        {
            return false;
        }
        m_hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, dwImageSize);
        if (m_hGlobal)
        {
            lpBuffer = ::GlobalLock(m_hGlobal);
            if (lpBuffer)
            {
                CopyMemory(lpBuffer, lpResourceData, dwImageSize);

                if (::CreateStreamOnHGlobal(m_hGlobal, FALSE, &pIStream) == S_OK)
                {
                    (*pBitmap) = Gdiplus::Bitmap::FromStream(pIStream);
                    pIStream->Release();
                    if ((*pBitmap))
                    {
                        if ((*pBitmap)->GetLastStatus() == Gdiplus::Ok)
                        {
                            return true;
                        }
                        delete (*pBitmap);
                        (*pBitmap) = NULL;
                    }
                }
                (*pBitmap) = NULL;
                ::GlobalUnlock(m_hGlobal);
            }
            ::GlobalFree(m_hGlobal);
            m_hGlobal = NULL;
        }
        return false;
    }
    //显示在屏幕中央
    void CenterWindowInScreen(HWND hWnd, LONG lPosX = (0), LONG lPosY = (0))
    {
        RECT rcWindow = { 0 };
        RECT rcScreen = { 0 };
        SIZE szAppWnd = { 300, 160 };
        POINT ptAppWnd = { 0, 0 };

        // Get workarea rect.
        BOOL fResult = SystemParametersInfo(SPI_GETWORKAREA,   // Get workarea information
            0,              // Not used
            &rcScreen,    // Screen rect information
            0);             // Not used

        GetWindowRect(hWnd, &rcWindow);
        szAppWnd.cx = (rcWindow.right - rcWindow.left);
        szAppWnd.cy = (rcWindow.bottom - rcWindow.top);

        //居中显示
        ptAppWnd.x = (lPosX != (0)) ? lPosX : ((rcScreen.right - rcScreen.left - szAppWnd.cx) / 2);
        ptAppWnd.y = (lPosY != (0)) ? lPosY : ((rcScreen.bottom - rcScreen.top - szAppWnd.cy) / 2);
        MoveWindow(hWnd, ptAppWnd.x, ptAppWnd.y, szAppWnd.cx, szAppWnd.cy, TRUE);
    }
    //显示在父窗口中央
    void CenterWindowInParent(HWND hWnd, HWND hParentWnd, LONG lPosX = (0), LONG lPosY = (0))
    {
        RECT rcWindow = { 0 };
        RECT rcParent = { 0 };
        SIZE szAppWnd = { 300, 160 };
        POINT ptAppWnd = { 0, 0 };

        GetWindowRect(hParentWnd, &rcParent);
        GetWindowRect(hWnd, &rcWindow);
        szAppWnd.cx = (rcWindow.right - rcWindow.left);
        szAppWnd.cy = (rcWindow.bottom - rcWindow.top);

        //居中显示
        ptAppWnd.x = (lPosX != (0)) ? lPosX : ((rcParent.right - rcParent.left - szAppWnd.cx) / 2);
        ptAppWnd.y = (lPosY != (0)) ? lPosY : ((rcParent.bottom - rcParent.top - szAppWnd.cy) / 2);
        MoveWindow(hWnd, ptAppWnd.x, ptAppWnd.y, szAppWnd.cx, szAppWnd.cy, TRUE);
    }

private:
    virtual VOID MessageProcess(HWND hWnd)
    {
        while (TRUE)
        {
            MSG msg = { 0 };
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    break;
                }

                if (!IsWindow(hWnd) || !IsDialogMessage(hWnd, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                {
                    switch (msg.message)
                    {
                    case WM_KEYDOWN:
                    case WM_KEYUP:
                    case WM_CHAR:
                    case WM_DEADCHAR:
                    case WM_SYSKEYDOWN:
                    case WM_SYSKEYUP:
                    case WM_SYSCHAR:
                    case WM_SYSDEADCHAR:
                    {
                        SendMessage(hWnd, msg.message, msg.wParam, msg.lParam);
                    }
                    break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                // 完成某些工作的其它行程序
            }
        }
    }
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_NCHITTEST:
        {
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
            case '1':
            {
                //MessageBox(hWnd, _T("1"), _T("Message"), MB_OK);
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
    static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);

        switch (uMsg)
        {
        case WM_INITDIALOG:
        {
            return (INT_PTR)TRUE;
        }
        break;
        case WM_PAINT:
        {
            HDC hDC = NULL;
            PAINTSTRUCT ps = { 0 };

            hDC = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDOK:
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

public:
    virtual VOID Run(HINSTANCE hInstance) = 0;
};

