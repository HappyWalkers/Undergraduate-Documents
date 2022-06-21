// øŒ…Ë3.h : main header file for the øŒ…Ë3 application
//

#if !defined(AFX_3_H__53837F72_ED2C_4311_9BDC_DD3A1905BE6C__INCLUDED_)
#define AFX_3_H__53837F72_ED2C_4311_9BDC_DD3A1905BE6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy3App:
// See øŒ…Ë3.cpp for the implementation of this class
//

class CMy3App : public CWinApp
{
public:
	CMy3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3_H__53837F72_ED2C_4311_9BDC_DD3A1905BE6C__INCLUDED_)
