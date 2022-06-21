// ¿ÎÉè2Dlg.h : header file
//

#if !defined(AFX_2DLG_H__9F242602_642E_4F89_B5F0_F82806119BF6__INCLUDED_)
#define AFX_2DLG_H__9F242602_642E_4F89_B5F0_F82806119BF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy2Dlg dialog

class CMy2Dlg : public CDialog
{
// Construction
public:
	CMy2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy2Dlg)
	enum { IDD = IDD_MY2_DIALOG };
	CListCtrl	m_list;
	CString	m_name;
	int		m_unit;
	double	m_number;
	CString	m_searchname;
	int		m_searchmonth;
	int		m_searchunit;
	int		m_searchmonth1;
	int		m_searchmonth2;
	int		m_date;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DLG_H__9F242602_642E_4F89_B5F0_F82806119BF6__INCLUDED_)
