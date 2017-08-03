#if !defined(AFX_INFODIALOG_H__8EE30D36_DAF5_4750_8074_51D5CFE140CE__INCLUDED_)
#define AFX_INFODIALOG_H__8EE30D36_DAF5_4750_8074_51D5CFE140CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDialog dialog

class CInfoDialog : public CDialog
{
// Construction
public:
	CInfoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoDialog)
	enum { IDD = IDD_CONTROL_DIALOG };
	CString	m_Status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODIALOG_H__8EE30D36_DAF5_4750_8074_51D5CFE140CE__INCLUDED_)
