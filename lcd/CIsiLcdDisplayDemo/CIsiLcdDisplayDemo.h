// CIsiLcdDisplayDemo.h�: fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


#include ".\IsiLcdLib\IsiLcdDisplay.h"

// CCIsiLcdDisplayDemoApp:
// Consultez CIsiLcdDisplayDemo.cpp pour l'impl�mentation de cette classe
//

class CCIsiLcdDisplayDemoApp : public CWinApp
{
private:
	DECLARE_GDI_PLUS;

public:
	CCIsiLcdDisplayDemoApp();

// Substitutions
	public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CCIsiLcdDisplayDemoApp theApp;