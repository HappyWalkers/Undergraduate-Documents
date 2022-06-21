// ����3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "����3.h"
#include "����3Dlg.h"
#include "fstream.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3Dlg dialog

CMy3Dlg::CMy3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy3Dlg)
	m_name = _T("");
	m_unit = 0;
	m_date = 0;
	m_number = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3Dlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_unit);
	DDX_Text(pDX, IDC_EDIT3, m_date);
	DDX_Text(pDX, IDC_EDIT4, m_number);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy3Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3Dlg message handlers

BOOL CMy3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"�û���",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,"��������",LVCFMT_CENTER,100);
	m_list.InsertColumn(2,"¥����",LVCFMT_CENTER,100);
	m_list.InsertColumn(3,"������",LVCFMT_CENTER,100);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy3Dlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	// TODO: Add your control notification handler code 
	ifstream f2("F:\\C++\\����3\\f1.txt",ios::in|ios::nocreate);
	char name[20];
	int date;
	int unit;
	double number;
	while(!f2.eof())
	{
		f2>>name>>unit>>date>>number;
		CString s1,s2,s3,s4;
		s1.Format("%s",name);
		m_list.InsertItem(0,s1);
		s2.Format("%d",unit);
		m_list.SetItemText(0,1,s2);
		s3.Format("%d",date);
		m_list.SetItemText(0,2,s3);
		s4.Format("%lf",number);
     	m_list.SetItemText(0,3,s4);
	}
	f2.close();
	*pResult = 0;
}

void CMy3Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	ofstream f1("F:\\C++\\����3\\f1.txt",ios::app);
	UpdateData(true);
	f1<<m_name<<" "<<m_unit<<" "<<m_date<<" "<<m_number<<endl;
	m_list.InsertItem(0,m_name);
	CString t2;
	t2.Format("%d",m_unit);
	m_list.SetItemText(0,1,t2);
    CString t3;
	t3.Format("%d",m_date);
	m_list.SetItemText(0,2,t3);
	CString t4;
	t4.Format("%ld",m_number);
	m_list.SetItemText(0,3,t4);
	UpdateData(false);


}
