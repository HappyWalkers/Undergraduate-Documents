// øŒ…Ë4.h : main header file for the øŒ…Ë4 application
//

#if !defined(AFX_4_H__103B66AF_E222_433C_A4B0_7EFD0C35EEB9__INCLUDED_)
#define AFX_4_H__103B66AF_E222_433C_A4B0_7EFD0C35EEB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy4App:
// See øŒ…Ë4.cpp for the implementation of this class
//

class CMy4App : public CWinApp
{
public:
	CMy4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_4_H__103B66AF_E222_433C_A4B0_7EFD0C35EEB9__INCLUDED_)
