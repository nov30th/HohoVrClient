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
	dlginfo.m_Status = "请稍后。。。服务器数据交换中";
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
	//登录按钮
	UpdateData(true);
	if (m_username.Find(".") > -1)
	{
		AfxMessageBox("此处域名举例。\n\n比如我的地址是http://qzj.blogcn.com/index.shtml\n\n那么域名就是qzj.\n\n明白了吧？重新输入。");
		return;
	}
	//m_username.Replace("_","-");
	//UpdateData(false);
	char  *p   =   NULL;
	CString myqq = "QQ2460739";
	const CString readme = "程序用UPX打包,解压很方便。反汇编也看不到什么信息的。哈";
	p   =   new  char[myqq.GetLength() + m_username.GetLength() + m_password.GetLength() + 100]; 


	if (m_username == "" || m_password == "")
	{
		AfxMessageBox("必须填写密码和用户名!");
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
		AfxMessageBox("在最下面选择要连接的服务器.");
		return;
	}
    CString m_ServerPath;
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);


	//链接服务器获得密钥
	ShowStatus("登录数据交换中");
    CTime theTime = CTime::GetCurrentTime();
	m_ServerPath = m_ServerPath + "/VRAPIVersion.ashx?Version=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S");
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO_Login.qzj",0,NULL) != S_OK)
	{
		ShowStatus();
		AfxMessageBox("连接HOHO系统API出错。请确认你的网络OK。");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	CStdioFile fileKeyLoad;
	if (!fileKeyLoad.Open("HOHO_Login.qzj",CFile::modeRead))
	{
		ShowStatus();
		AfxMessageBox("读取服务器交换密钥错误。");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	fileKeyLoad.ReadString(ServerKey);
	fileKeyLoad.Close();


	//加密算法
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
	//链接服务器获取信息
	m_serverip.GetLBText(m_serverip.GetCurSel(),m_ServerPath);
	m_ServerPath = m_ServerPath + "/VRAPILogin.ashx?w1=" + m_username + "&c2=" + SavedPassword  + "&v3=" + ThisVersion + "&t4=" + theTime.Format("%Y-%b-%d+%H:%M:%S");
	if (::URLDownloadToFile(NULL,m_ServerPath,"HOHO_Login.qzj",0,NULL) != S_OK)
	{
		ShowStatus();
		AfxMessageBox("连接HOHO系统API出错。请确认你的网络OK。");
		DeleteFile("HOHO_Login.qzj");
		return;
	}
	
	//判断开始
	CStdioFile filelogin;
	if (!filelogin.Open("HOHO_Login.qzj",CFile::modeRead))
	{
		ShowStatus();
		AfxMessageBox("读取本地数据错误。请检查是否有足够权限。");
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
			m_showvipvaildtime = readkey + "天";
		else if (readstr == "[onlinetime]")
		{
			m_showturnedontime = (readkey == "0" ? "没有开启!!" : "已经开启." );
			if (readkey == "0")
				AfxMessageBox("请登录网站，在VIP操作里面开启在线时长统计功能。\r\n这是一个非常独特有用的功能");
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
		CFileDialog dlgSaveFile(false,"html","HOHO Report.html",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "HOHO统计记录(*.html)|*.html|",NULL); 
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
		AfxMessageBox("连接HOHO系统API出错。请确认你的网络OK。");
		return;
	}
	if (m_issavetofile == 0)
		::ShellExecute(NULL,"open","HOHO``Report.html",NULL,NULL,SW_SHOW);
}


//////发送命令
bool CHOHO_VR_ClientDlg::SendCommandToServer(CString strcmd,CString strpaprm)
{
	if (!islogined)
	{
		tempStr = "啊。。不登录就操作拉？厉害厉害！登录First!";
		return true;
	}
	ShowStatus("登录数据交换中");
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
			AfxMessageBox("读取本地数据错误。请检查是否有足够权限。");
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
		AfxMessageBox("链接服务器出错。");
	else
		AfxMessageBox(tempStr);
	
}

void CHOHO_VR_ClientDlg::OnMenuitem32772() 
{
	if (SendCommandToServer("DeleteAll","") == false)
		AfxMessageBox("链接服务器出错。");
	else
		AfxMessageBox(tempStr);
}

void CHOHO_VR_ClientDlg::OnMenuitem32773() 
{
	if (SendCommandToServer("DeleteIPOnly","") == false)
		AfxMessageBox("链接服务器出错。");
	else
		AfxMessageBox(tempStr);
}

void CHOHO_VR_ClientDlg::OnMenuitem32774() 
{
	if (SendCommandToServer("VIPResetCount","") == false)
		AfxMessageBox("链接服务器出错。");
	else
		AfxMessageBox(tempStr);
	
}

void CHOHO_VR_ClientDlg::OnMenuitem32775() 
{
	if (SendCommandToServer("VIPResetTime","") == false)
		AfxMessageBox("链接服务器出错。");
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
		AfxMessageBox("您必须登录先。。。。");
		return;
	}
	if (isInstallCorrect(m_username) == true)
		AfxMessageBox("小孩子很聪明。代码安装正确。如果还是有问题。可以联系HOHO同学。");
	return;
}


bool CHOHO_VR_ClientDlg::isInstallCorrect(CString username)
{
	ShowStatus("检查模板的插入代码正确性。");
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
		AfxMessageBox("无法链接BLOGCN服务器，有可能已经Down掉了。\n也有可能其他原因。\n你只能过一段时间试试看类。\n\n来自：模板代码检测失败。");
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
		AfxMessageBox("在你的模板里没有发现<div id=visitors>Nov30th Loading...</div>,是不是你把它给吃掉了？");
	else if  (visitorsCount > 1)
		AfxMessageBox("日。你在模板里添加了2个或者个以上的<div id=visitors>Nov30th Loading...</div>,你在发疯。。。。。快点去掉只剩一个。");
	if (scriptCount == 0)
		AfxMessageBox("在你的模板里没有发现<SCRIPT language=javascript src=\"http://hoho.lengyouyou.com/vr/blogcnNEW.aspx?\"></SCRIPT>,是不是你把它给吃掉了？");
	else if (scriptCount >1)
		AfxMessageBox("日。你在模板里添加了2个或者个以上的<SCRIPT language=javascript src=\"http://hoho.lengyouyou.com/vr/blogcnNEW.aspx?\"></SCRIPT>,你在发疯。。。快点去掉只剩一个。");
	if (scriptCount == 1 && visitorsCount == 1 && isfront == false)
		AfxMessageBox("你太强了。谁告诉你Visitors标志可以放Script后面的？");
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

