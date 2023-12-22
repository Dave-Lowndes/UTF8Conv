// UTF8ConvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UTF8Conv.h"
#include "UTF8ConvDlg.h"
#include <vector>
#include <string_view>
using namespace std;

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
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
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
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
	ON_NOTIFY(NM_RETURN, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()

void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	PNMLINK pNMLink = reinterpret_cast<PNMLINK>( pNMHDR );
	if ( pNMLink->item.szUrl[0] != L'\0' )
	{
		ShellExecute( m_hWnd, NULL, pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL );
	}
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvDlg dialog

CUTF8ConvDlg::CUTF8ConvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUTF8ConvDlg::IDD, pParent)
	, m_CodePageItem( 0 )
{
	//{{AFX_DATA_INIT(CUTF8ConvDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bUpdatingANSI = false;
	m_bUpdatingHex = false;
	m_bUpdatingUnicode = false;
}

void CUTF8ConvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUTF8ConvDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_CBIndex( pDX, IDC_UTF_BASE, m_CodePageItem );
}

BEGIN_MESSAGE_MAP(CUTF8ConvDlg, CDialog)
	//{{AFX_MSG_MAP(CUTF8ConvDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnConvert)
	ON_BN_CLICKED(IDC_TOASCII, OnToascii)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_ANSI_TXT, &CUTF8ConvDlg::OnEnChangeUtf8AsAnsi)
	ON_EN_CHANGE(IDC_UNICODE_TXT, &CUTF8ConvDlg::OnEnChangeUnicodeEntry)
	ON_EN_CHANGE(IDC_HEX_TXT, &CUTF8ConvDlg::OnEnChangeHexTxt)
	ON_CBN_SELCHANGE( IDC_UTF_BASE, &CUTF8ConvDlg::OnCbnSelchangeUtfBase )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvDlg message handlers

BOOL CUTF8ConvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

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
#ifdef _DEBUG
	// https://en.wikipedia.org/wiki/UTF-7
	// https://www.utf8-chartable.de/
	// "1香港版 (Hong Kong)  2العالم العربي (Arabic)"
	SetDlgItemText( IDC_UNICODE_TXT, L"£ - U+00A2, utf-8 0xc2 0xa3, uft-7 +AKM-" );
#endif
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUTF8ConvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUTF8ConvDlg::OnPaint() 
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
HCURSOR CUTF8ConvDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

static const char HexChars[] =  {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static_assert( _countof( HexChars ) == 16, "HexChars must be 16 characters long" );

// Note: Although this is passed a wide character representation, it's only ever single byte characters, so the upper byte is always 0
static CString ConvertStringToHexPresentation( wstring_view sUtf )
{
	const size_t NumChars = sUtf.length();

	CString strResults;
	// Hex is shown as 3 chars per character "xx "
	LPTSTR pszResults = strResults.GetBuffer( 3* NumChars );

	for ( size_t indx = 0; indx < NumChars; ++indx )
	{
		const BYTE ch = static_cast<BYTE>( sUtf[indx] );
		pszResults[indx*3] = HexChars[( ch >> 4 ) & 0x0f ];
		pszResults[indx*3 + 1] = HexChars[ ch & 0x0f ];
		pszResults[indx*3 + 2] = ' ';
	}
	strResults.ReleaseBuffer();
	strResults.Trim();

	return strResults;
}

constexpr static BYTE CharToBin( TCHAR ch )
{
	BYTE Value = 0x0FF;
#if 1	// Use the modern STL approach
	auto it = std::ranges::find( HexChars, ch );
	if ( it != end( HexChars ) )
	{
		Value = static_cast<BYTE>( std::distance( begin( HexChars ), it ) );
	}
#else	// Use the old fashioned loop (though much less code generated)
	for ( BYTE indx = 0; indx < _countof( HexChars ); ++indx )
	{
		if ( ch == HexChars[indx] )
		{
			Value = indx;
			break;
		}
	}
#endif
	_ASSERT( Value != 0x0FF );	// Should never happen, not called with non-hex characters
	return Value;
}

// Bit of a mouthful, but this is what it does:
// Converts a UTF-16 string to the single byte (UTF7/8) form, but returns it in a UTF-16 string.
static CString Utf16StringToSingleByteStringAsUtf16String( const CString& Utf16String, UINT CodePage )
{
	// Convert to the single byte code page
	CW2AEX pA( Utf16String, CodePage );

	const auto len = strlen( pA );

	// convert the single byte form to a wide form
	CString str;
	for ( size_t indx = 0; indx < len; ++indx )
	{
		// Must use BYTE here to prevent sign extension doing the wrong thing
		const BYTE ch = pA[indx];
		str += ch;
	}

	return str;
}

// Uses the UTF16 field as the source, and populates the UTF-7/8 & Hex fields
void CUTF8ConvDlg::OnConvert() 
{
	CString sUtf16;
	GetDlgItemText( IDC_UNICODE_TXT, sUtf16 );

	// Get the code page combo box item value
	UpdateData();
	const UINT cp = m_CodePageItem != 0 ? CP_UTF7 : CP_UTF8;

	const auto sUtf8{ Utf16StringToSingleByteStringAsUtf16String( sUtf16, cp ) };

	m_bUpdatingANSI = true;
	// Don't use the ANSI Windows API (as I had done) as it gives the wrong result
	// when Windows is set to use UTF-8 as its system codepage.
	SetDlgItemText( IDC_ANSI_TXT, sUtf8 );
	m_bUpdatingANSI = false;

	const auto strHex{ ConvertStringToHexPresentation( { sUtf8, static_cast<size_t>(sUtf8.GetLength()) } ) };

	m_bUpdatingHex = true;
	SetDlgItemText( IDC_HEX_TXT, strHex );
	m_bUpdatingHex = false;
}

// Uses the Hex as the source and populates the other fields
void CUTF8ConvDlg::OnToascii() 
{
	CString sHexText;
	GetDlgItemText( IDC_HEX_TXT, sHexText );

	{
		/* The text should be pairs of hex characters with optional white-space characters */

		/* Parse each hex pair and convert to binary */
		const int NumChars = sHexText.GetLength();

		bool bSecondOfPair = false;
		bool bContentsOK = true;
		BYTE Value = 0;	// Init to quieten compiler

		CWnd* pInvalidMarker = GetDlgItem( IDC_INVALID_HEX );

		/* Store the results in this vector */
		vector<BYTE> vBin;
		vBin.reserve( NumChars/2 );// Guess an initial size for the vector

		for ( int indx = 0; ( indx < NumChars ) && bContentsOK; ++indx )
		{
			TCHAR ch = sHexText[indx];

			if ( isspace( ch ) )
			{
				/* Ignore it */
			}
			else
			{
				/* It must be hex 0..9, A..F (or a..f) */
				if ( isxdigit( ch ) )
				{
					/* Jolly good */

					/* is this the first or second of the pair? */
					if ( bSecondOfPair )
					{
						Value <<= 4;
						Value += CharToBin( ch );

						vBin.push_back( Value );
					}
					else
					{
						Value = CharToBin( ch );
					}

					/* Next time it's the other way round */
					bSecondOfPair = !bSecondOfPair;
				}
				else
				{
					/* Non hex character - abort it */
					bContentsOK = false;
					CEdit * pE = static_cast<CEdit*>( GetDlgItem( IDC_HEX_TXT ) );
					GotoDlgCtrl( pE );
					pE->SetSel( indx, indx+1, true );
					pInvalidMarker->ShowWindow( SW_SHOWNA );
					break;
				}
			}
		}
		/* Check we've had reasonable content to convert */
		if ( bContentsOK )
		{
			/* Enable/Disable the red X (invalid hex) control */
			pInvalidMarker->ShowWindow( bSecondOfPair ? SW_SHOWNA : SW_HIDE );

			if ( bSecondOfPair )
			{
//				AfxMessageBox( _T("Data does not contain an even number of hex characters.") );
			}
			else
			{
				/* We have the binary in the vector */
				CStringA sUtf8A( reinterpret_cast<LPCSTR>( vBin.data() ), vBin.size() );

				m_bUpdatingANSI = true;
				// Don't use the ANSI Windows API (as I had done) as it gives the wrong result
				// when Windows is set to use UTF-8 as its system codepage.

				// Copy the characters of the single byte string into a UTF16 string
				CString sUtf8W;
				for ( int indx = 0; indx < sUtf8A.GetLength(); ++indx )
				{
					// Must use BYTE here to prevent sign extension doing the wrong thing
					const BYTE ch = sUtf8A[indx];
					sUtf8W += ch;
				}

				SetDlgItemText( IDC_ANSI_TXT, sUtf8W );
				m_bUpdatingANSI = false;

				const UINT cp = m_CodePageItem != 0 ? CP_UTF7 : CP_UTF8;

				// Convert the single byte UTF7/8 string to UTF16
				CA2WEX pszUnicode( sUtf8A, cp );

				m_bUpdatingUnicode = true;
				SetDlgItemText( IDC_UNICODE_TXT, pszUnicode );
				m_bUpdatingUnicode = false;
			}
		}
	}
}

// Uses the Utf-7/8 as the source and populates the other fields
void CUTF8ConvDlg::OnEnChangeUtf8AsAnsi()
{
	if ( !m_bUpdatingANSI )
	{
		/* Take the control's text and re-create the hex form of it */
		CString strUtf8;

		GetDlgItemText( IDC_ANSI_TXT, strUtf8 );

		{
			const CString strHex{ ConvertStringToHexPresentation( { strUtf8, static_cast<size_t>(strUtf8.GetLength()) } ) };

			m_bUpdatingHex = true;
			SetDlgItemText( IDC_HEX_TXT, strHex );
			m_bUpdatingHex = false;

			// Convert the string containing the utf7/8 form, into Windows UTF-16 form
			// So, first get it into single byte form
			CStringA sUtfA;
			// Since the Unicode string is really single byte, just loop and copy the characters
			for ( int indx = 0; indx < strUtf8.GetLength(); ++indx )
			{
				// Do as BYTE (unsigned) to prevent any unexpected sign extension
				const BYTE ch = static_cast<BYTE>(strUtf8[indx]);
				sUtfA += ch;
			}

			UpdateData();	// So as to get the combo variable updated
			const UINT cp = m_CodePageItem != 0 ? CP_UTF7 : CP_UTF8;

			// Convert the single byte string to UTF16 from the single byte UTF-7/8 format
			CA2WEX pszW( sUtfA, cp );

			m_bUpdatingUnicode = true;
			SetDlgItemText( IDC_UNICODE_TXT, pszW );
			m_bUpdatingUnicode = false;
		}
	}
}

void CUTF8ConvDlg::OnEnChangeUnicodeEntry()
{
	if ( !m_bUpdatingUnicode )
	{
		OnConvert();
	}
}

void CUTF8ConvDlg::OnEnChangeHexTxt()
{
	if ( !m_bUpdatingHex )
	{
		OnToascii();
	}
}


void CUTF8ConvDlg::OnCbnSelchangeUtfBase()
{
	// Utf7/8 combo changed - get everything to update
	OnConvert();
}
