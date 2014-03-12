// KillGamesDlg.h : header file
//
#include "ModifeReg.h"  //包含头文件



#if !defined(AFX_KILLGAMESDLG_H__179F957A_A7FB_490F_8BCB_2A62938CA0E9__INCLUDED_)
#define AFX_KILLGAMESDLG_H__179F957A_A7FB_490F_8BCB_2A62938CA0E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKillGamesDlg dialog

class CKillGamesDlg : public CDialog
{
// Construction
public:
	CKillGamesDlg(CWnd* pParent = NULL);	// standard constructor
	
	BOOL hide; //窗口是否显示的标志
	int firstShow;
	int m_nHotKeyID;
	CModifeReg *pMR;

private:
	BOOL OnMoniter;  //是否监控的标志

// Dialog Data
	//{{AFX_DATA(CKillGamesDlg)
	enum { IDD = IDD_KILLGAMES_DIALOG };
	CString	m_strKeyword;
	CString	m_strPass1;
	CString	m_strPass2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKillGamesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKillGamesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg LONG OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton7();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton6();
	afx_msg void OnButton1();
	afx_msg void OnButton8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KILLGAMESDLG_H__179F957A_A7FB_490F_8BCB_2A62938CA0E9__INCLUDED_)
