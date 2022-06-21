// 课设4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "课设4.h"
#include "课设4Dlg.h"
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
// CMy4Dlg dialog

CMy4Dlg::CMy4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy4Dlg)
	m_name = _T("");
	m_unit = 0;
	m_date = 0;
	m_number = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy4Dlg)
	DDX_Control(pDX, IDC_LIST3, m_list3);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_unit);
	DDX_Text(pDX, IDC_EDIT3, m_date);
	DDX_Text(pDX, IDC_EDIT4, m_number);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy4Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy4Dlg message handlers

BOOL CMy4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
    m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//添加表格第一行
	m_list.InsertColumn(0,"用户名",LVCFMT_CENTER,75);
	m_list.InsertColumn(1,"楼栋号",LVCFMT_CENTER,75);
	m_list.InsertColumn(2,"抄表日期（月日）",LVCFMT_CENTER,120);
	m_list.InsertColumn(3,"电表读数",LVCFMT_CENTER,100);

	ifstream f2("F:\\C++\\课设4\\f1.txt",ios::in|ios::nocreate);
	char name[1000];
	int date;
	int unit;
    int number;

	while(!f2.eof())
	{
		f2>>name>>unit>>date>>number;//读出：从文件读出到自定义变量，自定义变量改变格式到字符串流，再插入到添加表格
		if(f2.fail())break;
		CString s1,s2,s3,s4;
		s1.Format("%s",name);
		m_list.InsertItem(0,s1);
		s2.Format("%d",unit);
		m_list.SetItemText(0,1,s2);
		s3.Format("%d",date);
		m_list.SetItemText(0,2,s3);
		s4.Format("%d",number);
     	m_list.SetItemText(0,3,s4);
	}
	f2.close();	


	m_list3.SetExtendedStyle(m_list3.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list3.InsertColumn(0,"用户名",LVCFMT_CENTER,100);
	m_list3.InsertColumn(1,"该用户总用电量",LVCFMT_CENTER,100);

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

void CMy4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy4Dlg::OnPaint() 
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
HCURSOR CMy4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy4Dlg::OnButton1() //添加：从编辑框变量读入到文件，改变格式为字符串流，编辑框变量到表格
{
	ofstream f1("F:\\C++\\课设4\\f1.txt",ios::app);
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
	t4.Format("%d",m_number);
	m_list.SetItemText(0,3,t4);
	UpdateData(false);	


}

void CMy4Dlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) //添加列表
{
	
	*pResult = 0;	
}

void CMy4Dlg::OnButton2() //排序按钮：读取到自定义的数组和变量里，电表读数累加，排列顺序，输出到排序列表
{
    ifstream f3("F:\\C++\\课设4\\f1.txt",ios::in|ios::nocreate);
	char name[1000][1000];
	int number[1000];
	int unit;
	int date;
	char newname[1000][1000];
	int newnumber[1000];

	while(!f3.eof())
	{
		int i;
		for(i=0;i<=1000;i++)//文件读取到自定义数组和变量中
		{
			f3>>name[i]>>unit>>date>>number[i];
			if(f3.fail())break;
		}
	}
		int t,j,k;
		for(t=0;t<=1000;t++)
		{
			for(k=0;k<t;k++)//查看是否有与之前相同用户名
			{
				if(!strcmp(name[t],name[k]))goto end;
			}
			for(j=t+1;j<=1000;j++)//找到相同用户名，累加电表读数
			{
				if(!strcmp(name[t],name[j]))
				{
					number[t]+=number[j];
					number[j]=0;
				}
			}
			strcpy(newname[t],name[t]);	
			newnumber[t]=number[t];
end:;
		}
		int m,n;//排序
		for(m=0;m<=1000;m++)
		{
			for(n=m;n<=1000;n++)
			{
				int s;
				char r[1000];
				if(newnumber[m]<newnumber[n])
				{
					s=newnumber[n];
					newnumber[n]=newnumber[m];
					newnumber[m]=s;
					strcpy(r,newname[n]);
					strcpy(newname[n],newname[m]);
					strcpy(newname[m],r);
				}
			}
		}
	
		for(int i=0;i<=1000;i++)
		{
	    	CString s1,s2;
	    	s1.Format("%s",newname[i]);
		    m_list3.InsertItem(i,s1);
	    	s2.Format("%d",newnumber);
     	    m_list3.SetItemText(i,1,s2);
			if(newnumber[i]==0)break;
		}
	
	f3.close();
}

void CMy4Dlg::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) //排序列表
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMy4Dlg::OnButton3()//排序按钮2 
{
	ifstream f4("F:\\C++\\课设4\\f1.txt",ios::in|ios::nocreate);
	char name[1000][1000];
	int number[1000];
	int unit;
	int date;
	char newname[1000][1000];
	int newnumber[1000];
	int i,j;
	bool x=false;

	while(!f4.eof())
	{
		int i;
		for(i=0;i<=1000;i++)//文件读取到自定义数组和变量中
		{
			f4>>name[i]>>unit>>date>>number[i];
			if(f4.fail())break;
		}
	}


	for(i=0;i<=1000;i++)
	{
		for(j=0;j<=1000;j++)//将name中元素与所有newname中元素依次比较，不同的粘贴过去,电量累加
		{
			if(strcmp(name[i],newname[j])==0)
				x=true;
		}
		if(!x)
		{
			int s;
			strcpy(newname[s],name[i]);
			newnumber[s]+=number[i];
			s++;
		}
	}

	int m,n;//排序
		for(m=0;m<=1000;m++)
		{
			for(n=m;n<=1000;n++)
			{
				int s;
				char r[1000];
				if(newnumber[m]<newnumber[n])
				{
					s=newnumber[n];
					newnumber[n]=newnumber[m];
					newnumber[m]=s;
					strcpy(r,newname[n]);
					strcpy(newname[n],newname[m]);
					strcpy(newname[m],r);
				}
			}
		}

	
		for(i=0;i<=1000;i++)
		{
	    	CString s1,s2;
	    	s1.Format("%s",newname[i]);
		    m_list3.InsertItem(i,s1);
	    	s2.Format("%d",newnumber);
     	    m_list3.SetItemText(i,1,s2);
			if(newnumber[i]==0)break;
		}

	f4.close();
}
