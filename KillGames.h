// KillGames.h : main header file for the KILLGAMES application
//

#if !defined(AFX_KILLGAMES_H__CB4D452D_6142_48A8_96ED_90011E751F5D__INCLUDED_)
#define AFX_KILLGAMES_H__CB4D452D_6142_48A8_96ED_90011E751F5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKillGamesApp:
// See KillGames.cpp for the implementation of this class
//

class CKillGamesApp : public CWinApp
{
public:
	CKillGamesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKillGamesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKillGamesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KILLGAMES_H__CB4D452D_6142_48A8_96ED_90011E751F5D__INCLUDED_)
