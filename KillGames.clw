; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKillGamesDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KillGames.h"

ClassCount=3
Class1=CKillGamesApp
Class2=CKillGamesDlg

ResourceCount=3
Resource2=IDD_KILLGAMES_DIALOG
Resource1=IDR_MAINFRAME
Class3=CLoginDialog
Resource3=IDD_DIALOG1

[CLS:CKillGamesApp]
Type=0
HeaderFile=KillGames.h
ImplementationFile=KillGames.cpp
Filter=N

[CLS:CKillGamesDlg]
Type=0
HeaderFile=KillGamesDlg.h
ImplementationFile=KillGamesDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CKillGamesDlg



[DLG:IDD_KILLGAMES_DIALOG]
Type=1
Class=CKillGamesDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON2,button,1342251008
Control7=IDC_EDIT1,edit,1342251168
Control8=IDC_EDIT2,edit,1342251168
Control9=IDC_EDIT3,edit,1344340036
Control10=IDC_BUTTON3,button,1342251008
Control11=IDC_BUTTON4,button,1342242816
Control12=IDC_BUTTON5,button,1342242816
Control13=IDC_BUTTON6,button,1342242816
Control14=IDC_BUTTON7,button,1342242816
Control15=IDC_BUTTON8,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CLoginDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1342251041
Control4=IDC_STATIC,button,1342177287

[CLS:CLoginDialog]
Type=0
HeaderFile=LoginDialog.h
ImplementationFile=LoginDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginDialog
VirtualFilter=dWC

