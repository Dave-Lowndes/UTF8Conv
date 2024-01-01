// UTF8Conv.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <commctrl.h>
#include "UTF8Conv.h"
#include "UTF8ConvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(_M_IA64)
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#if defined(_M_X64)
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvApp

BEGIN_MESSAGE_MAP(CUTF8ConvApp, CWinApp)
	//{{AFX_MSG_MAP(CUTF8ConvApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvApp construction

CUTF8ConvApp::CUTF8ConvApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUTF8ConvApp object

CUTF8ConvApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvApp initialization

BOOL CUTF8ConvApp::InitInstance()
{
	const INITCOMMONCONTROLSEX iccex{ sizeof( iccex ), ICC_LINK_CLASS };

	if ( InitCommonControlsEx( &iccex ) )
	{
		CUTF8ConvDlg dlg;
		m_pMainWnd = &dlg;
		const auto nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
