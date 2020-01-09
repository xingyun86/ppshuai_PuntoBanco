// PuntoBanco.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PuntoBanco.h"
#include "EffectsDialogWindow.h"
#include "PuntoBancoDialogWindow.h"


/////////////////////////////////////////////////////////////////////////////////
//

//static _TCHAR G_WORK_PATH[MAX_PATH] = { 0 };

/////////////////////////////////////////////////////////////////////////////////
//
typedef enum ENUMKEYTYPE {
    EKT_NULL=0,
    EKT_1='1',//庄
    EKT_2='2',//闲
    EKT_3='3',//和
    EKT_4='4',//庄对子
    EKT_5='5',//闲对子
    EKT_7='7',//设置
    EKT_9='9',//退出
    EKT_SUBTRACT='-',//修改
    EKT_ADD='+',//新开靴
    EKT_STAR,//取消
    EKT_ENTER,//确认
}ENUMKEYTYPE;

/////////////////////////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////////////////////////
//
INT APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ INT       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    INT nResult = (0);
    
    //_tcsncpy(G_WORK_PATH, *__targv, sizeof(G_WORK_PATH) / sizeof(*G_WORK_PATH)); 
    //(*_tcsrchr(G_WORK_PATH, _T('\\'))) = _T('\0');

    //CPuntoBancoDialogWindow::Instance()->Run(hInstance);
    CEffectsDialogWindow::Instance()->Run(hInstance);

    return nResult;
}
