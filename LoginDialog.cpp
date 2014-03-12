// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "KillGames.h"
#include "LoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	m_strPass = _T("");
	
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Text(pDX, IDC_EDIT1, m_strPass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

void CLoginDialog::OnOK() 
{
	UpdateData(TRUE);
	if(m_strInPass.Compare(m_strPass)==0)
	{
		bConfirmed = TRUE;
		CDialog::OnOK();
	}else
	{
		MessageBox("密码错误，请重新输入","提示",MB_OK|MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT1)->SetWindowText("");
		GetDlgItem(IDC_EDIT1)->SetFocus();
	}
}

void CLoginDialog::OnCancel() 
{	
	//bConfirmed = FALSE;
	CDialog::OnCancel();
}

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	bConfirmed = FALSE;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDialog::SetInPass(CString str)
{
	m_strInPass = str;
	return TRUE;
}

void CLoginDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	GetDlgItem(IDC_EDIT1)->SetFocus();
}
