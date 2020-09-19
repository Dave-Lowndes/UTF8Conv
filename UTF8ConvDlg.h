// UTF8ConvDlg.h : header file
//

#if !defined(AFX_UTF8CONVDLG_H__A22124A9_8D7A_4D81_AD2F_E07620E978F7__INCLUDED_)
#define AFX_UTF8CONVDLG_H__A22124A9_8D7A_4D81_AD2F_E07620E978F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUTF8ConvDlg dialog

class CUTF8ConvDlg : public CDialog
{
// Construction
public:
	CUTF8ConvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUTF8ConvDlg)
	enum { IDD = IDD_UTF8CONV_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTF8ConvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUTF8ConvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvert();
	afx_msg void OnToascii();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeUtf8AsAnsi();
	afx_msg void OnEnChangeUnicodeEntry();
private:
	bool m_bUpdatingUnicode;
	bool m_bUpdatingHex;
	bool m_bUpdatingANSI;
public:
afx_msg void OnEnChangeHexTxt();
private:
	int m_CodePageItem;
public:
	afx_msg void OnCbnSelchangeUtfBase();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTF8CONVDLG_H__A22124A9_8D7A_4D81_AD2F_E07620E978F7__INCLUDED_)
