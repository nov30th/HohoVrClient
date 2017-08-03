// HOHO_VR_Client.h : main header file for the HOHO_VR_CLIENT application
//

#if !defined(AFX_HOHO_VR_CLIENT_H__E6C8ECF0_4163_4D55_A4B3_3ACF781DF30A__INCLUDED_)
#define AFX_HOHO_VR_CLIENT_H__E6C8ECF0_4163_4D55_A4B3_3ACF781DF30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHOHO_VR_ClientApp:
// See HOHO_VR_Client.cpp for the implementation of this class
//

class CHOHO_VR_ClientApp : public CWinApp
{
public:
	CHOHO_VR_ClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHOHO_VR_ClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHOHO_VR_ClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOHO_VR_CLIENT_H__E6C8ECF0_4163_4D55_A4B3_3ACF781DF30A__INCLUDED_)
