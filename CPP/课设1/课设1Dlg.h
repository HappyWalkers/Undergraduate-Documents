// ¿ÎÉè1Dlg.h : header file
//

#if !defined(AFX_1DLG_H__1DF5167C_A481_4098_B7C7_6D4C8D19A85F__INCLUDED_)
#define AFX_1DLG_H__1DF5167C_A481_4098_B7C7_6D4C8D19A85F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy1Dlg dialog

class CMy1Dlg : public CDialog
{
// Construction
public:
	CMy1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1Dlg)
	enum { IDD = IDD_MY1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1DLG_H__1DF5167C_A481_4098_B7C7_6D4C8D19A85F__INCLUDED_)
