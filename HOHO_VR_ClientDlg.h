// HOHO_VR_ClientDlg.h : header file
//

#if !defined(AFX_HOHO_VR_CLIENTDLG_H__3854BB17_C266_4B6F_9BEF_2C4D0C8CBFB5__INCLUDED_)
#define AFX_HOHO_VR_CLIENTDLG_H__3854BB17_C266_4B6F_9BEF_2C4D0C8CBFB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHOHO_VR_ClientDlg dialog

class CHOHO_VR_ClientDlg : public CDialog
{
// Construction
public:
	CHOHO_VR_ClientDlg(CWnd* pParent = NULL);	// standard constructor
	bool SendCommandToServer(CString strcmd,CString strpaprm);
    bool isInstallCorrect(CString username);
	void ShowStatus(CString strStatus);
	void ShowStatus();
// Dialog Data
	//{{AFX_DATA(CHOHO_VR_ClientDlg)
	enum { IDD = IDD_HOHO_VR_CLIENT_DIALOG };
	CComboBox	m_serverip;
	CProgressCtrl	m_showspace;
	BOOL	m_rememberpassword;
	CString	m_password;
	CString	m_username;
	CString	m_showaccountexpdate;
	CString	m_showregdate;
	CString	m_showturnedontime;
	CString	m_showusername;
	CString	m_showvipexpdate;
	CString	m_showvipvaildtime;
	CString	m_showlastlogin;
	BOOL	m_issavetofile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHOHO_VR_ClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHOHO_VR_ClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonlogin();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnCheckpwd();
	afx_msg void OnButtondownload();
	afx_msg void OnMenuitem3days();
	afx_msg void OnMenuitem32772();
	afx_msg void OnMenuitem32773();
	afx_msg void OnMenuitem32774();
	afx_msg void OnMenuitem32775();
	afx_msg void OnMenuitemabout();
	afx_msg void OnMenuitem32780();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOHO_VR_CLIENTDLG_H__3854BB17_C266_4B6F_9BEF_2C4D0C8CBFB5__INCLUDED_)
