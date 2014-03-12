// KillGamesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KillGames.h"
#include "KillGamesDlg.h"
#include "LoginDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VK_D 68


BOOL CALLBACK EnumWindowsProc(HWND hwnd, DWORD lParam);

/////////////////////////////////////////////////////////////////////////////
// CKillGamesDlg dialog

CKillGamesDlg::CKillGamesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillGamesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKillGamesDlg)
	m_strKeyword = _T("");
	m_strPass1 = _T("");
	m_strPass2 = _T("");
	firstShow = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKillGamesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKillGamesDlg)
	DDX_Text(pDX, IDC_EDIT3, m_strKeyword);
	DDX_Text(pDX, IDC_EDIT1, m_strPass1);
	DDX_Text(pDX, IDC_EDIT2, m_strPass2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKillGamesDlg, CDialog)
	//{{AFX_MSG_MAP(CKillGamesDlg)
	ON_WM_PAINT()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKillGamesDlg message handlers

BOOL CKillGamesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	hide = FALSE;
	OnMoniter = TRUE;
	m_nHotKeyID=0;
	pMR = new CModifeReg();

	BOOL m_isKeyRegistered = RegisterHotKey(GetSafeHwnd(),m_nHotKeyID,MOD_ALT,VK_D);
	ASSERT(m_isKeyRegistered != FALSE);

	m_strKeyword = pMR->GetKeyword();
	if(m_strKeyword.GetLength()==0) 
	{
		m_strKeyword = "注册表%启动项%任务管理器%系统配置%游戏%植物大战";
		pMR->SetKeyword(m_strKeyword);
	}
	UpdateData(FALSE);

	SetTimer(1, 1000, NULL); //启动每1秒扫描一次的定时器
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKillGamesDlg::OnPaint() 
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
	
	//如果是首次启动，刚不显示窗口，但首次启动时会两次调用OnPaint
	if(firstShow<3)
	{
		ShowWindow(SW_HIDE);
		firstShow +=1;
	}
}


LONG CKillGamesDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if(hide)
	{
		ShowWindow(FALSE);
		hide = !hide;
	}
	else
	{
		CString inPass = pMR->GetPassword();
		if(inPass.GetLength() == 0)
		{
			ShowWindow(TRUE);
			hide = !hide;
			AfxMessageBox("首次使用请设置密码！\n\n密码只能是数字，请至少设置5位以上。\t\t");
		}else{
			CLoginDialog *lg = new CLoginDialog();
			lg->SetInPass(inPass);
			if(lg->DoModal() == IDOK)
			{
				if(lg->bConfirmed) //验证成功
				{
					ShowWindow(TRUE);
					hide = !hide;
					delete lg;
				}
			}
		}
	}
	return 0;
}

// The system calls this to obtain the cursor to display while the user drags


BOOL CALLBACK EnumWindowsProc(HWND hwnd, DWORD lParam) 
{
  // 窗口是否可视
    if (!IsWindowVisible(hwnd))
        return TRUE;
 
    // 窗口是否可激活
    if (!IsWindowEnabled(hwnd))
        return TRUE;
	
	int length = ::GetWindowTextLength(hwnd);
	// 窗口是否有标题，无标题则无法判断
	if(length <1) 
		return TRUE;

	char *buffer = new char[length+2];
	::GetWindowText(hwnd,buffer,length+2);

	CString str_Title = buffer;
	CString keywords = *((CString*)lParam);

	CString temp;

	int i=0;
	while(AfxExtractSubString(temp,(LPCTSTR)keywords,i++,'%'))
	{
		if(temp.GetLength()>0 && str_Title.Find(temp,0) != -1)  //看窗口标题中是否包含关键字，若有，则发送关闭消息使其关闭
			::PostMessage(hwnd,WM_CLOSE,0,0);
	}

    return TRUE;
}


void CKillGamesDlg::OnOK() {}
void CKillGamesDlg::OnCancel() {}


void CKillGamesDlg::OnTimer(UINT nIDEvent)
{
	
	if(OnMoniter)
	{
		EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&m_strKeyword); //遍历所有窗口，回调处理函数

		GetDlgItem(IDC_BUTTON4)->SetWindowText("当前正在运行，点击停止");
	}else
		GetDlgItem(IDC_BUTTON4)->SetWindowText("当前已停止运行，点击开始");

	CDialog::OnTimer(nIDEvent);
}



void CKillGamesDlg::OnClose() 
{
	::ShowWindow(GetSafeHwnd(),SW_MINIMIZE);
}

void CKillGamesDlg::OnButton4() 
{
	OnMoniter = !OnMoniter;
}

//退出监控
void CKillGamesDlg::OnButton5() 
{
	BOOL m_isKeyRegistered = UnregisterHotKey(GetSafeHwnd(),m_nHotKeyID);
	ASSERT(m_isKeyRegistered != FALSE);
	CDialog::OnClose();
	CDialog::OnCancel();
}


void CKillGamesDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strPass1.Compare(m_strPass2)==0)
	{
		if(m_strPass1.GetLength() < 5) 
		{
			AfxMessageBox("请至少设置5位数字！\t\t");
		}else{
			pMR->SetPassword(m_strPass1);
			GetDlgItem(IDC_EDIT1)->SetWindowText("");
			GetDlgItem(IDC_EDIT2)->SetWindowText("");
			AfxMessageBox("密码修改成功\t\t\n\n");
		}	
	}else
	{
		AfxMessageBox("\n密码不匹配\t\t");
		GetDlgItem(IDC_EDIT1)->SetWindowText("");
		GetDlgItem(IDC_EDIT2)->SetWindowText("");
	}
}

void CKillGamesDlg::OnButton3() 
{
	UpdateData(TRUE);
	m_strKeyword.TrimLeft();
	m_strKeyword.TrimRight();
	//if(m_strKeyword.GetLength()<1)
	//	m_strKeyword = "游戏";

	pMR->SetKeyword(m_strKeyword);
	AfxMessageBox("关键字修改成功\t\t\n\n");
}

void CKillGamesDlg::OnButton6() 
{
	int n = MessageBox("确定要删除本程序？\t\t\t\n\n点[确定]手动删除程序文件\n\n点[取消]则返回。\t",
		"提示",MB_OKCANCEL|MB_ICONQUESTION);
	if(n == IDCANCEL) return;

	if(!pMR->ClearAll())
	{
		AfxMessageBox("抱歉，清除失败！\t\n\n");
		return;
	}else
	{
		char pBuf[512];
		GetCurrentDirectory(512,pBuf);
		CString PathName = CString(pBuf);
		ShellExecute(NULL,"open",PathName,NULL,NULL,SW_SHOWNORMAL);
		OnButton5();
	}
}


void CKillGamesDlg::OnButton7() 
{
 	if(!pMR->setStartUp())
		AfxMessageBox("抱歉，设置失败！");
	else 
		AfxMessageBox("设置为开机启动！");
}


void CKillGamesDlg::OnButton8() 
{
	CString info;
	info  = "1、程序打开后会自动隐藏\n\n";
	info += "2、快捷键【Alt+D】打开或隐藏窗口\n\n";
	info += "3、首次使用请设置密码，务必牢记密码，否则会比较麻烦\n\n";
	info += "4、设置【开机启动】能发挥程序的最大功效\n\n";
	info += "5、彻底删除程序请点击【卸载程序】\n\n";
	info += "6、为保护本程序，请将'注册表'、'启动项'、'任务管理器'等也加为关键字\n\n\n";
	info += "  邮箱 1151995489@qq.com      weibo.com/Edgar_bai\n\n";
	info += "                                  last modify: 2013-2-18";

	MessageBox(info,"帮助",MB_OK|MB_ICONINFORMATION);
 
}