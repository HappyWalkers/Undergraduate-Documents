// ¿ÎÉè3Dlg.h : header file
//

#if !defined(AFX_3DLG_H__0DE30416_4FE0_486C_9738_0B84A045C05D__INCLUDED_)
#define AFX_3DLG_H__0DE30416_4FE0_486C_9738_0B84A045C05D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy3Dlg dialog

class CMy3Dlg : public CDialog
{
// Construction
public:
	CMy3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy3Dlg)
	enum { IDD = IDD_MY3_DIALOG };
	CListCtrl	m_list;
	CString	m_name;
	int		m_unit;
	int		m_date;
	int		m_number;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DLG_H__0DE30416_4FE0_486C_9738_0B84A045C05D__INCLUDED_)
