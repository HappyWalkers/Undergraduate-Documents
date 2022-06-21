// ����4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "����4.h"
#include "����4Dlg.h"
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
	m_searchname = _T("");
	m_searchmonth = 0;
	m_searchunit = 0;
	m_searchmonth1 = 0;
	m_searchmonth2 = 0;
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
	DDX_Text(pDX, IDC_EDIT7, m_searchname);
	DDX_Text(pDX, IDC_EDIT8, m_searchmonth);
	DDX_Text(pDX, IDC_EDIT5, m_searchunit);
	DDX_Text(pDX, IDC_EDIT6, m_searchmonth1);
	DDX_Text(pDX, IDC_EDIT9, m_searchmonth2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy4Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)

	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy4Dlg message handlers

BOOL CMy4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
    m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//��ӱ���һ��
	m_list.InsertColumn(0,"�û���",LVCFMT_CENTER,75);
	m_list.InsertColumn(1,"¥����",LVCFMT_CENTER,75);
	m_list.InsertColumn(2,"�������ڣ����գ�",LVCFMT_CENTER,120);
	m_list.InsertColumn(3,"������",LVCFMT_CENTER,100);

	ifstream f2("C:\\f1.txt",ios::in|ios::nocreate);
	char name[1000];
	int date;
	int unit;
    int number;

	while(!f2.eof())
	{
		f2>>name>>unit>>date>>number;//���������ļ��������Զ���������Զ�������ı��ʽ���ַ��������ٲ��뵽��ӱ��
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
	m_list3.InsertColumn(0,"�û���",LVCFMT_CENTER,100);
	m_list3.InsertColumn(1,"���û����õ���",LVCFMT_CENTER,100);

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

void CMy4Dlg::OnButton1() //��ӣ��ӱ༭��������뵽�ļ����ı��ʽΪ�ַ��������༭����������
{
	ofstream f1("C:\\f1.txt",ios::app);
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

void CMy4Dlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) //����б�
{
	
	*pResult = 0;	
}



void CMy4Dlg::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) //�����б�
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CMy4Dlg::OnButton3()//����ť
{
	ifstream f4("C:\\f1.txt",ios::in|ios::nocreate);
	char name[100][100]={0};
	int number[100]={0};
	int unit;
	int date;
	char newname[100][100]={0};
	int newnumber[100]={0};
	int i,j;
	
   int c=0;
	while(!f4.eof())
	{
		int i;
		for(i=0;i<=100;i++)//�ļ���ȡ���Զ�������ͱ�����
		{
			f4>>name[i]>>unit>>date>>number[i];
			if(f4.fail())break;
			c++;
		}
	}

    int newnamecount=1;
    strcpy(newname[0],name[0]);
	for(i=0;i<c;i++)
	{   
		int flag=1;
		for(j=0;j<newnamecount;j++)//��name��Ԫ��������newname��Ԫ�����αȽϣ���ͬ�ĵ����ۼӣ���ͬ��ճ����ȥ,�����ۼ�
		{
			if(strcmp(name[i],newname[j])==0)
			{
				newnumber[j]+=number[i];
			    flag=0;
			}
		}
		    if(flag==1)
			{
		      strcpy(newname[newnamecount],name[i]);
			  newnumber[newnamecount]=number[i];
			  newnamecount++;
			}
	}

	
	int m,n;//����
		for(m=0;m<newnamecount;m++)
		{
            int t=0;
			char r[100]={0};
			for(n=m+1;n<newnamecount;n++)
			{
				if(newnumber[m]<newnumber[n])
				{
					t=newnumber[n];
					newnumber[n]=newnumber[m];
					newnumber[m]=t;
					strcpy(r,newname[n]);
					strcpy(newname[n],newname[m]);
					strcpy(newname[m],r);
				}
			}
		}

		for(i=0;i<newnamecount;i++)
		{
	    	CString s1,s2;
	    	s1.Format("%s",newname[i]);
		    m_list3.InsertItem(i,s1);
	    	s2.Format("%d",newnumber[i]);
     	    m_list3.SetItemText(i,1,s2);
			
		}

	f4.close();

}

void CMy4Dlg::OnButton4() //��ѯ�û��õ�����ť
{
	UpdateData(true);
	char name[1000][1000];
	int number[1000];
	int unit;
	int date[1000];

	int f=0;
	int x=0;

	ifstream f5("C:\\f1.txt",ios::in|ios::nocreate);
	while(!f5.eof())//���ļ������Զ�������ͱ���
	{
		for(int i=0;i<=1000;i++)
		{
		    f5>>name[i]>>unit>>date[i]>>number[i];
			if(f5.fail())break;
			f++;
		}
	}


	for(int i=0;i<f;i++)//�ҳ����������������ۼ�
	{
		int t=date[i]/100;
		if(strcmp(m_searchname,name[i])==0 && m_searchmonth==t)
		{x+=number[i];}
	}

	CString s1;//���
	s1.Format("%d",x);
	MessageBox(s1,TEXT("���û������õ���Ϊ��"),0);
	f5.close();
	UpdateData(false);
}

void CMy4Dlg::OnButton5()//��ѯĳ¥����ĳ�µ�ĳ���õ��� 
{
	UpdateData(true);
	char name[1000];
	int number[1000];
	int unit[1000];
	int date[1000];

	int x=0;
	int f=0;

	ifstream f5("C:\\f1.txt",ios::in|ios::nocreate);
	while(!f5.eof())//���ļ������Զ�������ͱ���
	{
		for(int i=0;i<=1000;i++)
		{
		    f5>>name>>unit[i]>>date[i]>>number[i];
			if(f5.fail())break;
			f++;
		}
	}


	for(int i=0;i<=f;i++)//�ҳ����������������ۼ�
	{
		int t=date[i]/100;
		if(m_searchunit==unit[i] && t>=m_searchmonth1 && t<=m_searchmonth2) 
			
			x+=number[i];
	}

	CString s1;//���
	s1.Format("%d",x);
	MessageBox(s1,TEXT("��¥�����ʱ���õ���Ϊ��"),0);	
	f5.close();
	UpdateData(false);
}
