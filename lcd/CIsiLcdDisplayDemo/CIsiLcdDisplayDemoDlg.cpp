// CIsiLcdDisplayDemoDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "CIsiLcdDisplayDemo.h"
#include "CIsiLcdDisplayDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Données de boîte de dialogue
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// boîte de dialogue CCIsiLcdDisplayDemoDlg




CCIsiLcdDisplayDemoDlg::CCIsiLcdDisplayDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCIsiLcdDisplayDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCIsiLcdDisplayDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LCD_SAMPLE1, m_CIsiLcdSample1);
	DDX_Control(pDX, IDC_LCD_SAMPLE2, m_CIsiLcdSample2);
	DDX_Control(pDX, IDC_LCD_SAMPLE3, m_CIsiLcdSample3);
	DDX_Control(pDX, IDC_LCD_SAMPLE4, m_CIsiLcdSample4);
	DDX_Control(pDX, IDC_LCD_SAMPLE5, m_CIsiLcdSample5);
	DDX_Control(pDX, IDC_LCD_SAMPLE6, m_CIsiLcdSample6);
	DDX_Control(pDX, IDC_LCD_SAMPLE7, m_CIsiLcdSample7);
	DDX_Control(pDX, IDC_LCD_SAMPLE8, m_CIsiLcdSample8);
	DDX_Control(pDX, IDC_LCD_SAMPLE9, m_CIsiLcdSample9);
	DDX_Control(pDX, IDC_LCD_SAMPLE10, m_CIsiLcdSample10);
	DDX_Control(pDX, IDC_LCD_SAMPLE11, m_CIsiLcdSample11);
	DDX_Control(pDX, IDC_LCD_SAMPLE12, m_CIsiLcdSample12);
	DDX_Control(pDX, IDC_LCD_SAMPLE13, m_CIsiLcdSample13);
	DDX_Control(pDX, IDC_LCD_SAMPLE14, m_CIsiLcdSample14);
	DDX_Control(pDX, IDC_LCD_SAMPLE15, m_CIsiLcdSample15);
	DDX_Control(pDX, IDC_LCD_SAMPLE16, m_CIsiLcdSample16);
	DDX_Control(pDX, IDC_LCD_SAMPLE17, m_CIsiLcdSample17);
}

BEGIN_MESSAGE_MAP(CCIsiLcdDisplayDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CCIsiLcdDisplayDemoDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// gestionnaires de messages pour CCIsiLcdDisplayDemoDlg

BOOL CCIsiLcdDisplayDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire
	m_CIsiLcdSample6.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample6.SetSegmentStyle( MatrixDot, FALSE );
	m_CIsiLcdSample6.ShowOffSegment( FALSE );
	m_CIsiLcdSample6.SetValueNbDigit( 20,0 ); // 20 caracteres
	m_CIsiLcdSample6.SetScrollSpeed( 500 );
	m_CIsiLcdSample6.Transparent( TRUE );
	m_CIsiLcdSample6.StringMode( TRUE, FALSE);
	m_CIsiLcdSample6.SetWindowText( _T("The Code Project") );


	m_CIsiLcdSample1.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample1.SetValueNbDigit( 20,0 ); // 20 caracteres
	m_CIsiLcdSample1.SetColor( RGB(0,200,0) );
	m_CIsiLcdSample1.SetBlink( 500 );
	m_CIsiLcdSample1.StringMode( TRUE, FALSE);
	m_CIsiLcdSample1.SetWindowText( _T("100% Code Project") );

	m_CIsiLcdSample10.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample10.SetSegmentStyle( MatrixDot, FALSE );
	m_CIsiLcdSample10.SetValueNbDigit( 20,0 ); // 20 caracteres
	m_CIsiLcdSample10.SetColor( RGB(200,0,0) );
	m_CIsiLcdSample10.StringMode( TRUE, FALSE);
	m_CIsiLcdSample10.SetWindowText( _T("100% Code Project") );

	m_CIsiLcdSample11.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample11.SetSegmentStyle( MatrixSquare, FALSE );
	m_CIsiLcdSample11.SetWindowText( _T("100% Code Project") );
	m_CIsiLcdSample11.SetColor( RGB(0,0,200) );
	m_CIsiLcdSample11.SetValueNbDigit( 20,0 ); // 20 caracteres
	m_CIsiLcdSample11.StringMode( TRUE, FALSE);


	m_CIsiLcdSample2.SetSegmentStyle( Segment7, FALSE );
	m_CIsiLcdSample2.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample2.ShowSign( TRUE );
	m_CIsiLcdSample2.SetColor( RGB(150,0,0) );
	m_CIsiLcdSample2.SetValue( -2.35 );

	m_CIsiLcdSample3.SetSegmentStyle( Segment7, FALSE );
	m_CIsiLcdSample3.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample3.ShowSign( FALSE );
	m_CIsiLcdSample3.SetColor( RGB(150,150,0) );
	m_CIsiLcdSample3.SetValue( 2.35 );

	m_CIsiLcdSample4.SetSegmentStyle( Segment7, FALSE );
	m_CIsiLcdSample4.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample4.ShowSign( TRUE );
	m_CIsiLcdSample4.SetColor( RGB(0,150,0) );
	m_CIsiLcdSample4.SetValue( 2.35 );

	m_CIsiLcdSample7.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample7.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample7.ShowSign( TRUE );
	m_CIsiLcdSample7.SetColor( RGB(150,0,0) );
	m_CIsiLcdSample7.SetValue( -2.35 );

	m_CIsiLcdSample8.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample8.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample8.ShowSign( FALSE );
	m_CIsiLcdSample8.SetColor( RGB(150,150,0) );
	m_CIsiLcdSample8.SetSegmentSize(1.5);
	m_CIsiLcdSample8.SetValue( 2.35 );

	m_CIsiLcdSample9.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample9.SetValueNbDigit( 4,2 ); 
	m_CIsiLcdSample9.ShowSign( TRUE );
	m_CIsiLcdSample9.SetColor( RGB(0,150,0) );
	m_CIsiLcdSample9.SetSegmentSize(2);
	m_CIsiLcdSample9.SetValue( 2.35 );

	m_CIsiLcdSample12.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample12.SetSegmentStyle( MatrixDot, FALSE );
	m_CIsiLcdSample12.SetValueNbDigit( 6,2 ); 
	m_CIsiLcdSample12.ShowSign( TRUE );
	m_CIsiLcdSample12.SetColor( RGB(150,0,0) );
	m_CIsiLcdSample12.SetValue( -2.35 );
	m_CIsiLcdSample12.GetBorder()->SetStyle( CGdiBorder::Chrome );
	m_CIsiLcdSample12.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample12.InvalidateBorder();

	m_CIsiLcdSample13.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample13.SetSegmentStyle( MatrixSquare, FALSE );
	m_CIsiLcdSample13.SetValueNbDigit( 6,2 ); 
	m_CIsiLcdSample13.ShowSign( FALSE );
	m_CIsiLcdSample13.SetColor( RGB(150,150,0) );
	m_CIsiLcdSample13.SetValue( 2.35 );
	m_CIsiLcdSample13.GetBorder()->SetStyle( CGdiBorder::Lower );
	m_CIsiLcdSample13.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample13.GetBorder()->SetShape( CGdiBorder::RoundRect, 10 );
	m_CIsiLcdSample13.InvalidateBorder();

	//m_CIsiLcdSample14.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample14.SetSegmentStyle( Segment7, FALSE );
	m_CIsiLcdSample14.SetValueNbDigit( 6,2 ); 
	//m_CIsiLcdSample14.ShowSign( TRUE );
	m_CIsiLcdSample14.SetColor( RGB(0,150,0) );
	//m_CIsiLcdSample14.SetValue( 2.35 );
	m_CIsiLcdSample14.StringMode( TRUE, FALSE );
	m_CIsiLcdSample14.SetWindowText( _T("12:04:43") );
	m_CIsiLcdSample14.GetBorder()->SetStyle( CGdiBorder::Both );
	m_CIsiLcdSample14.GetBorder()->SetShape( CGdiBorder::Ellipse, 10 );
	m_CIsiLcdSample14.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample14.InvalidateBorder();

	m_CIsiLcdSample5.SetValueNbDigit( 1,0 ); 
	m_CIsiLcdSample5.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample5.SetColor( RGB(0,200,0) );
	m_CIsiLcdSample5.SetScrollSpeed( 1000 );
	m_CIsiLcdSample5.StringMode( TRUE, FALSE);
	m_CIsiLcdSample5.SetWindowText( _T("0123456789ABCDEF") );
	m_CIsiLcdSample5.ShowGlass(0,FALSE);	// No glass effect

	m_CIsiLcdSample15.SetValueNbDigit( 1,0 ); 
	m_CIsiLcdSample15.SetSegmentStyle( Segment16, FALSE );
	m_CIsiLcdSample15.SetColor( RGB(0,200,0), 0, RGB(255,255,255) ); // No light effect
	m_CIsiLcdSample15.SetScrollSpeed( 1000 );
	m_CIsiLcdSample15.StringMode( TRUE, FALSE);
	m_CIsiLcdSample15.SetWindowText( _T("0123456789ABCDEFGHIJKLMNOPGRSTUVWXYZ") );
	m_CIsiLcdSample15.ShowGlass(50,FALSE);	// light glass effect
	m_CIsiLcdSample15.GetBorder()->SetStyle( CGdiBorder::Bump );
	m_CIsiLcdSample15.GetBorder()->SetShape( CGdiBorder::RoundRect, 20 );
	m_CIsiLcdSample15.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample15.GetBorder()->SetColor( 0x10FFFFFF, GDIBORDER_COLOR_START);
	m_CIsiLcdSample15.GetBorder()->SetColor( Color::Black, GDIBORDER_COLOR_END );
	m_CIsiLcdSample15.InvalidateBorder();

	m_CIsiLcdSample16.SetValueNbDigit( 1,0 );
	m_CIsiLcdSample16.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample16.SetSegmentStyle( MatrixDot, FALSE );
	m_CIsiLcdSample16.SetColor( RGB(0,200,0) );
	m_CIsiLcdSample16.SetScrollSpeed( 1000 );
	m_CIsiLcdSample16.SetSegmentSize( 0.8f );	// Adjust segments size ( 80% )
	m_CIsiLcdSample16.StringMode( TRUE, FALSE);
	m_CIsiLcdSample16.SetWindowText( _T("0123456789ABCDEFGHIJKLMNOPGRSTUVWXYZabcdefghijklmnopqrstuvxwyz") );
	m_CIsiLcdSample16.ShowGlass(100,FALSE);	// medium glass effect
	m_CIsiLcdSample16.GetBorder()->SetStyle( CGdiBorder::Chrome );
	m_CIsiLcdSample16.GetBorder()->SetShape( CGdiBorder::RoundRect, 10 );
	m_CIsiLcdSample16.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample16.InvalidateBorder();

	m_CIsiLcdSample17.SetValueNbDigit( 1,0 );
	m_CIsiLcdSample17.LoadMatrix( IDB_MATRIX5x7 );
	m_CIsiLcdSample17.SetSegmentStyle( MatrixSquare, FALSE );
	m_CIsiLcdSample17.SetColor( RGB(0,200,0), 0, RGB(255,255,255) );
	m_CIsiLcdSample17.SetScrollSpeed( 1000 );
	m_CIsiLcdSample17.SetSegmentSize( 0.7f );	// Adjust segments size ( 80% )
	m_CIsiLcdSample17.StringMode( TRUE, FALSE);
	m_CIsiLcdSample17.SetWindowText( _T("0123456789ABCDEFGHIJKLMNOPGRSTUVWXYZabcdefghijklmnopqrstuvxwyz") );
	m_CIsiLcdSample17.ShowGlass(255,FALSE);	// hard glass effect
	m_CIsiLcdSample17.GetBorder()->SetStyle( CGdiBorder::Chrome );
	m_CIsiLcdSample17.GetBorder()->SetShape( CGdiBorder::Ellipse, 10 );
	m_CIsiLcdSample17.GetBorder()->SetSize( 10 );
	m_CIsiLcdSample17.InvalidateBorder();

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CCIsiLcdDisplayDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône. Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CCIsiLcdDisplayDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CCIsiLcdDisplayDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCIsiLcdDisplayDemoDlg::OnBnClickedButtonTest()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
	m_CIsiLcdSample10.SetWindowText( _T("TEST") );
}
