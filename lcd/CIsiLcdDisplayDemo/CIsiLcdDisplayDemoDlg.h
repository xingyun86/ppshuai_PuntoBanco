// CIsiLcdDisplayDemoDlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"


// boîte de dialogue CCIsiLcdDisplayDemoDlg
class CCIsiLcdDisplayDemoDlg : public CDialog
{
// Construction
public:
	CCIsiLcdDisplayDemoDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_CISILCDDISPLAYDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIsiLcdDisplay m_CIsiLcdSample1;
	CIsiLcdDisplay m_CIsiLcdSample2;
	CIsiLcdDisplay m_CIsiLcdSample3;
	CIsiLcdDisplay m_CIsiLcdSample4;
	CIsiLcdDisplay m_CIsiLcdSample5;
	CIsiLcdDisplay m_CIsiLcdSample6;
	CIsiLcdDisplay m_CIsiLcdSample7;
	CIsiLcdDisplay m_CIsiLcdSample8;
	CIsiLcdDisplay m_CIsiLcdSample9;
	CIsiLcdDisplay m_CIsiLcdSample10;
	CIsiLcdDisplay m_CIsiLcdSample11;
	CIsiLcdDisplay m_CIsiLcdSample12;
	CIsiLcdDisplay m_CIsiLcdSample13;
	CIsiLcdDisplay m_CIsiLcdSample14;
	CIsiLcdDisplay m_CIsiLcdSample15;
	CIsiLcdDisplay m_CIsiLcdSample16;
	CIsiLcdDisplay m_CIsiLcdSample17;
	afx_msg void OnBnClickedButtonTest();
};
