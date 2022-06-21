// ¿ÎÉè4Dlg.h : header file
//

#if !defined(AFX_4DLG_H__D5E59686_A3E8_4B5A_8C67_CC23765DA0D1__INCLUDED_)
#define AFX_4DLG_H__D5E59686_A3E8_4B5A_8C67_CC23765DA0D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy4Dlg dialog

class CMy4Dlg : public CDialog
{
// Construction
public:
	CMy4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy4Dlg)
	enum { IDD = IDD_MY4_DIALOG };
	CListCtrl	m_list3;
	CListCtrl	m_list2;
	CListCtrl	m_list;
	CString	m_name;
	int		m_unit;
	int		m_date;
	int		m_number;
	CString	m_searchname;
	int		m_searchmonth;
	int		m_searchunit;
	int		m_searchmonth1;
	int		m_searchmonth2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton2();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_4DLG_H__D5E59686_A3E8_4B5A_8C67_CC23765DA0D1__INCLUDED_)
