// PuntoBanco.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PuntoBanco.h"
#include "PuntoBancoDialogWindow.h"


/////////////////////////////////////////////////////////////////////////////////
//

//static _TCHAR G_WORK_PATH[MAX_PATH] = { 0 };

/////////////////////////////////////////////////////////////////////////////////
//
typedef enum ENUMKEYTYPE {
    EKT_NULL=0,
    EKT_1='1',//ׯ
    EKT_2='2',//��
    EKT_3='3',//��
    EKT_4='4',//ׯ����
    EKT_5='5',//�ж���
    EKT_7='7',//����
    EKT_9='9',//�˳�
    EKT_SUBTRACT='-',//�޸�
    EKT_ADD='+',//�¿�ѥ
    EKT_STAR,//ȡ��
    EKT_ENTER,//ȷ��
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

    CPuntoBancoDialogWindow::Instance()->Run(hInstance);

    return nResult;
}
