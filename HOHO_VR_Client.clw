; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHOHO_VR_ClientApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HOHO_VR_Client.h"

ClassCount=4
Class1=CHOHO_VR_ClientApp
Class2=CHOHO_VR_ClientDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_HOHO_VR_CLIENT_DIALOG
Resource2=IDR_MAINFRAME
Class4=CInfoDialog
Resource3=IDD_CONTROL_DIALOG
Resource4=IDD_ABOUTBOX
Resource5=IDR_MENUMAIN

[CLS:CHOHO_VR_ClientApp]
Type=0
HeaderFile=HOHO_VR_Client.h
ImplementationFile=HOHO_VR_Client.cpp
Filter=N
LastObject=CHOHO_VR_ClientApp

[CLS:CHOHO_VR_ClientDlg]
Type=0
HeaderFile=HOHO_VR_ClientDlg.h
ImplementationFile=HOHO_VR_ClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CHOHO_VR_ClientDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=HOHO_VR_ClientDlg.h
ImplementationFile=HOHO_VR_ClientDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_HOHO_VR_CLIENT_DIALOG]
Type=1
Class=CHOHO_VR_ClientDlg
ControlCount=31
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITUSERNAME,edit,1350631552
Control5=IDC_EDITPASSWORD,edit,1350631584
Control6=IDC_CHECK1,button,1476460547
Control7=IDC_STATIC,button,1342177287
Control8=IDC_COMBOSERVER,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECKPWD,button,1342242819
Control11=IDC_STATIC,button,1342177287
Control12=IDC_BUTTONDOWNLOAD,button,1476460544
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BUTTONLOGIN,button,1342242817
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_PROGRESSSPACE,msctls_progress32,1350565888
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATICUSERNAME,static,1342308352
Control24=IDC_STATICREGDATE,static,1342308352
Control25=IDC_STATICVIPEXPDATE,static,1342308352
Control26=IDC_STATICACCEXPDATE,static,1342308352
Control27=IDC_STATICVIPVALID,static,1342308352
Control28=IDC_STATICTURNONTIME,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATICLASTLOGIN,static,1342308352
Control31=IDC_CHECKAUTOOPEN,button,1342242819

[DLG:IDD_CONTROL_DIALOG]
Type=1
Class=CInfoDialog
ControlCount=1
Control1=IDC_EDITSTATUS,edit,1342244992

[MNU:IDR_MENUMAIN]
Type=1
Class=CHOHO_VR_ClientDlg
Command1=ID_MENUITEM3DAYS
Command2=ID_MENUITEM32772
Command3=ID_MENUITEM32773
Command4=ID_MENUITEM32774
Command5=ID_MENUITEM32775
Command6=ID_MENUITEM32776
Command7=ID_MENUITEM32777
Command8=ID_MENUITEM32778
Command9=ID_MENUITEM32780
Command10=ID_MENUITEMABOUT
CommandCount=10

[CLS:CInfoDialog]
Type=0
HeaderFile=InfoDialog.h
ImplementationFile=InfoDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CInfoDialog
VirtualFilter=dWC

