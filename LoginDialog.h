#if !defined(AFX_LOGINDIALOG_H__6324091F_42FE_4C79_ABAB_7C1117E9C5EA__INCLUDED_)
#define AFX_LOGINDIALOG_H__6324091F_42FE_4C79_ABAB_7C1117E9C5EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

class CLoginDialog : public CDialog
{
// Construction
public:
	BOOL SetInPass(CString str);
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor
	BOOL bConfirmed;
	CString m_strInPass;

// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_strPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDIALOG_H__6324091F_42FE_4C79_ABAB_7C1117E9C5EA__INCLUDED_)
