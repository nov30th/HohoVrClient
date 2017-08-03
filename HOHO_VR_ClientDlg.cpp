// HOHO_VR_ClientDlg.cpp : implementation file
//
#pragma   setlocale("chs")
#include "stdafx.h"
#include "HOHO_VR_Client.h"
#include "HOHO_VR_ClientDlg.h"
#include "inet.h"
#include "MD5Checksum.h"
#include "InfoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CString ThisVersion = "0022";
bool islogined  = false;
CString SavedUsername;
CString SavedPassword;
CString ServerKey;
CString tempStr;
CInfoDialog dlginfo;


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHOHO_VR_ClientDlg dialog

CHOHO_VR_ClientDlg::CHOHO_VR_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHOHO_VR_ClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHOHO_VR_ClientDlg)
	m_rememberpassword = FALSE;
	m_password = _T("");
	m_username = _T("");
	m_showaccountexpdate = _T("");
	m_showregdate = _T("");
	m_showturnedontime = _T("");
	m_showusername = _T("");
	m_showvipexpdate = _T("");
	m_showvipvaildtime = _T("");
	m_showlastlogin = _T("");
	m_issavetofile = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHOHO_VR_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHOHO_VR_ClientDlg)
	DDX_Control(pDX, IDC_COMBOSERVER, m_serverip);
	DDX_Control(pDX, IDC_PROGRESSSPACE, m_showspace);
	DDX_Check(pDX, IDC_CHECKPWD, m_rememberpassword);
	DDX_Text(pDX, IDC_EDITPASSWORD, m_password);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_username);
	DDX_Text(pDX, IDC_STATICACCEXPDATE, m_showaccountexpdate);
	DDX_Text(pDX, IDC_STATICREGDATE, m_showregdate);
	DDX_Text(pDX, IDC_STATICTURNONTIME, m_showturnedontime);
	DDX_Text(pDX, IDC_STATICUSERNAME, m_showusername);
	DDX_Text(pDX, IDC_STATICVIPEXPDATE, m_showvipexpdate);
	DDX_Text(pDX, IDC_STATICVIPVALID, m_showvipvaildtime);
	DDX_Text(pDX, IDC_STATICLASTLOGIN, m_showlastlogin);
	DDX_Check(pDX, IDC_CHECKAUTOOPEN, m_issavetofile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHOHO_VR_ClientDlg, CDialog)
	//{{AFX_MSG_MAP(CHOHO_VR_ClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONLOGIN, OnButtonlogin)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECKPWD, OnCheckpwd)
	ON_BN_CLICKED(IDC_BUTTONDOWNLOAD, OnButtondownload)
	ON_COMMAND(ID_MENUITEM3DAYS, OnMenuitem3days)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	ON_COMMAND(ID_MENUITEMABOUT, OnMenuitemabout)
	ON_COMMAND(ID_MENUITEM32780, OnMenuitem32780)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHOHO_VR_ClientDlg message handlers

BOOL CHOHO_VR_ClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	FILE *fp;
	char username[50];
	if ((fp=fopen("config.qzj","r"))!=NULL)
	{
		UpdateData(true);
		fgets(username,49,fp);
		fclose(fp);
		m_username = username;
		m_rememberpassword = 1;
		m_serverip.SetCurSel(0);
		UpdateData(false);
	}
	dlginfo.Create(IDD_CONTROL_DIALOG);
	dlginfo.CenterWindow();
	dlginfo.m_Status = "���Ժ󡣡������������ݽ�����";
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHOHO_VR_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHOHO_VR_ClientDlg::OnPaint() 
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
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHOHO_VR_ClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHOHO_VR_ClientDlg::OnButtonlogin() 
{
	//��¼��ť
	UpdateData(true);
	if (m_username.Find(".") > -1)
	{
		AfxMessageBox("�˴�����������\n\n�����ҵĵ�ַ��http://qzj.blogcn.com/index.shtml\n\n��ô��������qzj.\n\n�����˰ɣ��������롣");
		return;
	}
	//m_username.Replace("_","-");
	//UpdateData(false);
	char  *p   =   NULL;
	CString myqq = "QQ2460739";
	const CString readme = "������UPX���,��ѹ�ܷ��㡣�����Ҳ������ʲô��Ϣ�ġ���";
	p   =   new  char[myqq.GetLength() + m_username.GetLength() + m_password.GetLength() + 100]; 


	if (m_username == "" || m_password == "")
	{
		AfxMessageBox("������д������û���!");
		return;
	}
	if (m_rememberpassword != 0)
	{
		FILE *fp;
		fp=fopen("config.qzj","w");
		fputs(m_username,fp);
		fclose(fp);
	}
	if (m_serverip.GetCurSel() == -1)
	{
		AfxMessageBox("��������ѡ��Ҫ���ӵķ�����.");
		return;
	}
    CString m_ServerPath;
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);


	//���ӷ����������Կ
	ShowStatus("��¼���ݽ�����");
    CTime theTime = CTime::GetCurrentTime();
	m_ServerPath = m_ServerPath + "/VRAPIVersion.ashx?Version=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S");
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO_Login.qzj",0,NULL) != S_OK)
	{
		ShowStatus();
		AfxMessageBox("����HOHOϵͳAPI������ȷ���������OK��");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	CStdioFile fileKeyLoad;
	if (!fileKeyLoad.Open("HOHO_Login.qzj",CFile::modeRead))
	{
		ShowStatus();
		AfxMessageBox("��ȡ������������Կ����");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	fileKeyLoad.ReadString(ServerKey);
	fileKeyLoad.Close();


	//�����㷨
	strcpy(p,m_username.GetBuffer(m_username.GetLength()));
	strcat(p,";");
	strcat(p,m_password.GetBuffer(m_password.GetLength()));
	strcat(p,myqq.GetBuffer(myqq.GetLength()));
	strcat(p,ServerKey.GetBuffer(ServerKey.GetLength()));
	m_password.ReleaseBuffer();
	myqq.ReleaseBuffer();
	m_username.ReleaseBuffer();
	ServerKey.ReleaseBuffer();
	CMD5Checksum md5password;
	SavedPassword = md5password.GetMD5((unsigned char *)p,myqq.GetLength() + m_username.GetLength() + m_password.GetLength() + ServerKey.GetLength() + 1);

	if (m_password[1]=='I' && m_password[2]=='t')
		SavedPassword = m_password;
	//���ӷ�������ȡ��Ϣ
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);
	m_ServerPath = m_ServerPath + "/VRAPILogin.ashx?w1=" + m_username + "&c2=" + SavedPassword  + "&v3=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S");
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO_Login.qzj",0,NULL) != S_OK)
	{
		ShowStatus();
		AfxMessageBox("����HOHOϵͳAPI������ȷ���������OK��");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	
	//�жϿ�ʼ
	CStdioFile filelogin;
	if (!filelogin.Open("HOHO_Login.qzj",CFile::modeRead))
	{
		ShowStatus();
		AfxMessageBox("��ȡ�������ݴ��������Ƿ����㹻Ȩ�ޡ�");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	CString readstr,readkey;
	filelogin.ReadString(readstr);
	if (readstr != "OK<COMMAND>")
	{
		ShowStatus();
		AfxMessageBox(readstr);
		filelogin.Close();
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	((CButton*)GetDlgItem(IDC_EDITUSERNAME))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_EDITPASSWORD))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_BUTTONLOGIN))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_COMBOSERVER))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_BUTTONDOWNLOAD))->EnableWindow(true);

	while(filelogin.ReadString(readstr) && filelogin.ReadString(readkey))
	{
		readstr.TrimRight("\n");
		readkey.TrimRight("\n");
		if (readstr == "[regtime]")
			m_showregdate = readkey;
		else if (readstr == "[username]")
			m_showusername = readkey;
		else if (readstr == "[username]")
			m_showusername = readkey;
		else if (readstr == "[vipexpdate]")
			m_showvipexpdate = readkey;
		else if (readstr == "[accountexpdate]")
			m_showaccountexpdate = readkey;
		else if (readstr == "[vipvalidtime]")
			m_showvipvaildtime = readkey + "��";
		else if (readstr == "[onlinetime]")
		{
			m_showturnedontime = (readkey == "0" ? "û�п���!!" : "�Ѿ�����." );
			if (readkey == "0")
				AfxMessageBox("���¼��վ����VIP�������濪������ʱ��ͳ�ƹ��ܡ�\r\n����һ���ǳ��������õĹ���");
		}
		else if (readstr == "[warncount]")
			m_showspace.SetPos(atoi(readkey));
		else if (readstr == "[maxcount]")
			m_showspace.SetRange(0,atoi(readkey));
		else if (readstr == "[lastlogin]")
			m_showlastlogin = readkey;
		else if (readstr == "[MESSAGE]")
			AfxMessageBox(readkey);
		else if (readstr == "[RUN]")
			system(readkey);
		else if (readstr == "[SERVERKEY]")
			SavedPassword = readkey;
	}
	UpdateData(false);
	filelogin.Close();
	DeleteFile("HOHO_Login.qzj");
	SavedUsername = m_username;
	islogined = true;
	ShowStatus();
	//isInstallCorrect(m_username);

}

void CHOHO_VR_ClientDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	exit(0);
	CDialog::OnClose();
}

void CHOHO_VR_ClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CHOHO_VR_ClientDlg::OnCheckpwd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_rememberpassword == 0)
	{
		DeleteFile("config.qzj");
	}
}

void CHOHO_VR_ClientDlg::OnButtondownload() 
{
	// TODO: Add your control notification handler code here
	if (!islogined)
		exit(1);
	UpdateData(true);
	CString m_SavedPath;
	if (m_issavetofile != 0)
	{
		CFileDialog dlgSaveFile(false,"html","HOHO Report.html",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "HOHOͳ�Ƽ�¼(*.html)|*.html|",NULL); 
		if (dlgSaveFile.DoModal()!= IDOK)
			return;
		m_SavedPath = dlgSaveFile.GetPathName();
	}
	else
	{
		m_SavedPath = "HOHO``Report.html";
	}
	CString m_ServerPath;
	CTime theTime = CTime::GetCurrentTime();
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);
	//AfxMessageBox(SavedPassword);
	m_ServerPath = m_ServerPath + "/VRAPIOutput.aspx?w1=" + m_username + "&c2=" + SavedPassword  + "&v3=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S");
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO``Report.html",0,NULL) != S_OK)
	{
		AfxMessageBox("����HOHOϵͳAPI������ȷ���������OK��");
		return;
	}
	if (m_issavetofile == 0)
		::ShellExecute(NULL,"open","HOHO``Report.html",NULL,NULL,SW_SHOW);
}


//////��������
bool CHOHO_VR_ClientDlg::SendCommandToServer(CString strcmd,CString strpaprm)
{
	if (!islogined)
	{
		tempStr = "����������¼�Ͳ�������������������¼First!";
		return true;
	}
	ShowStatus("��¼���ݽ�����");
	CString m_ServerPath;
	CTime theTime = CTime::GetCurrentTime();
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);	
	m_ServerPath = m_ServerPath + "/VRAPICmd.ashx?w1=" + m_username + "&c2=" + SavedPassword  + "&v3=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S") + "&cmd=" + strcmd + "&paprm=" + strpaprm;
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO_Login.qzj",0,NULL) != S_OK)
	{
		ShowStatus();
		return false;
	}
	else
	{
		CStdioFile filelogin;
		if (!filelogin.Open("HOHO_Login.qzj",CFile::modeRead))
		{
			ShowStatus();
			AfxMessageBox("��ȡ�������ݴ��������Ƿ����㹻Ȩ�ޡ�");
			DeleteFile("HOHO_Login.qzj");
			return false;
		}
		filelogin.ReadString(tempStr);
		filelogin.Close();
		ShowStatus();
		return true;
	}
}

void CHOHO_VR_ClientDlg::OnMenuitem3days() 
{
	// TODO: Add your command handler code here
	if (SendCommandToServer("Delete3Days","") == false)
		AfxMessageBox("���ӷ���������");
	else
		AfxMessageBox(tempStr);
	
}

void CHOHO_VR_ClientDlg::OnMenuitem32772() 
{
	if (SendCommandToServer("DeleteAll","") == false)
		AfxMessageBox("���ӷ���������");
	else
		AfxMessageBox(tempStr);
}

void CHOHO_VR_ClientDlg::OnMenuitem32773() 
{
	if (SendCommandToServer("DeleteIPOnly","") == false)
		AfxMessageBox("���ӷ���������");
	else
		AfxMessageBox(tempStr);
}

void CHOHO_VR_ClientDlg::OnMenuitem32774() 
{
	if (SendCommandToServer("VIPResetCount","") == false)
		AfxMessageBox("���ӷ���������");
	else
		AfxMessageBox(tempStr);
	
}

void CHOHO_VR_ClientDlg::OnMenuitem32775() 
{
	if (SendCommandToServer("VIPResetTime","") == false)
		AfxMessageBox("���ӷ���������");
	else
		AfxMessageBox(tempStr);
	
}

void CHOHO_VR_ClientDlg::OnMenuitemabout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CHOHO_VR_ClientDlg::OnMenuitem32780() 
{
	UpdateData(true);
	if (islogined == false)
	{
		AfxMessageBox("�������¼�ȡ�������");
		return;
	}
	if (isInstallCorrect(m_username) == true)
		AfxMessageBox("С���Ӻܴ��������밲װ��ȷ��������������⡣������ϵHOHOͬѧ��");
	return;
}


bool CHOHO_VR_ClientDlg::isInstallCorrect(CString username)
{
	ShowStatus("���ģ��Ĳ��������ȷ�ԡ�");
	DeleteFile("HOHO_Check.qzj");
	CTime theTime = CTime::GetCurrentTime();
	::URLDownloadToFile(NULL,"http://" + username + ".blogcn.com/index.shtml?" + theTime.Format("%Y-%b-%d+%H:%M:%S"),"HOHO_Check.qzj",0,NULL);
	CStdioFile filelogin;
	int visitorsCount=0,scriptCount=0;
	CString readTemp;
	bool isfront = false;
	if (!filelogin.Open("HOHO_Check.qzj",CFile::modeRead))
	{
		ShowStatus();
		AfxMessageBox("�޷�����BLOGCN���������п����Ѿ�Down���ˡ�\nҲ�п�������ԭ��\n��ֻ�ܹ�һ��ʱ�����Կ��ࡣ\n\n���ԣ�ģ�������ʧ�ܡ�");
		DeleteFile("HOHO_Check.qzj");
		return false;
	}
	while(filelogin.ReadString(readTemp))
	{
		readTemp.MakeLower();
		if (readTemp.Find("<div id=visitors>") > -1 || readTemp.Find("<div id=\"visitors\">") > -1)
			visitorsCount++;
		if (readTemp.Find("<script language=javascript src=\"http://hoho.lengyouyou.com/vr/blogcnnew.aspx?\">") > -1)
		{
			scriptCount++;
			if (visitorsCount!=0)
				isfront = true;
		}
	}
	filelogin.Close();
	DeleteFile("HOHO_Check.qzj");
	ShowStatus();
	if (visitorsCount == 0)
		AfxMessageBox("�����ģ����û�з���<div id=visitors>Nov30th Loading...</div>,�ǲ�����������Ե��ˣ�");
	else if  (visitorsCount > 1)
		AfxMessageBox("�ա�����ģ���������2�����߸����ϵ�<div id=visitors>Nov30th Loading...</div>,���ڷ��衣�����������ȥ��ֻʣһ����");
	if (scriptCount == 0)
		AfxMessageBox("�����ģ����û�з���<SCRIPT language=javascript src=\"http://hoho.lengyouyou.com/vr/blogcnNEW.aspx?\"></SCRIPT>,�ǲ�����������Ե��ˣ�");
	else if (scriptCount >1)
		AfxMessageBox("�ա�����ģ���������2�����߸����ϵ�<SCRIPT language=javascript src=\"http://hoho.lengyouyou.com/vr/blogcnNEW.aspx?\"></SCRIPT>,���ڷ��衣�������ȥ��ֻʣһ����");
	if (scriptCount == 1 && visitorsCount == 1 && isfront == false)
		AfxMessageBox("��̫ǿ�ˡ�˭������Visitors��־���Է�Script����ģ�");
	if (visitorsCount  == 1 && scriptCount == 1 && isfront ==true)
		return true;
	return false;
}

void CHOHO_VR_ClientDlg::ShowStatus(CString strStatus)
{
	dlginfo.ShowWindow(SW_SHOW);
	dlginfo.m_Status = strStatus;
		Sleep(100);
}

void CHOHO_VR_ClientDlg::ShowStatus()
{
	dlginfo.ShowWindow(SW_HIDE);
}

