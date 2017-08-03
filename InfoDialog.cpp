// InfoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HOHO_VR_Client.h"
#include "InfoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDialog dialog


CInfoDialog::CInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDialog)
	m_Status = _T("");
	//}}AFX_DATA_INIT
}


void CInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDialog)
	DDX_Text(pDX, IDC_EDITSTATUS, m_Status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDialog, CDialog)
	//{{AFX_MSG_MAP(CInfoDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDialog message handlers
