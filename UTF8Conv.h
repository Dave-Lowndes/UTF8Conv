// UTF8Conv.h : main header file for the UTF8CONV application
//

#if !defined(AFX_UTF8CONV_H__BA5C5808_95EE_4F29_A50A_1F95705DFE32__INCLUDED_)
#define AFX_UTF8CONV_H__BA5C5808_95EE_4F29_A50A_1F95705DFE32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvApp:
// See UTF8Conv.cpp for the implementation of this class
//

class CUTF8ConvApp : public CWinApp
{
public:
	CUTF8ConvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTF8ConvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUTF8ConvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTF8CONV_H__BA5C5808_95EE_4F29_A50A_1F95705DFE32__INCLUDED_)
