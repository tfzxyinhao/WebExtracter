; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWebExtractDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WebExtract.h"

ClassCount=3
Class1=CWebExtractApp
Class2=CWebExtractDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CSourceEdit
Resource2=IDD_WEBEXTRACT_DIALOG

[CLS:CWebExtractApp]
Type=0
HeaderFile=WebExtract.h
ImplementationFile=WebExtract.cpp
Filter=N
LastObject=CWebExtractApp

[CLS:CWebExtractDlg]
Type=0
HeaderFile=WebExtractDlg.h
ImplementationFile=WebExtractDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_WEB



[DLG:IDD_WEBEXTRACT_DIALOG]
Type=1
Class=CWebExtractDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_URL,edit,1350631552
Control3=IDC_GETSOUCRCE,button,1342242816
Control4=IDC_SOURCE,edit,1353781508
Control5=IDC_REGEX,edit,1350635652
Control6=IDC_GETRESULT,button,1342242816
Control7=IDC_STATIC_INFO,static,1350696960
Control8=IDC_CHECK_SETTOP,button,1342242819
Control9=IDC_WEB,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control10=IDC_TREE,SysTreeView32,1350633479

[CLS:CSourceEdit]
Type=0
HeaderFile=SourceEdit.h
ImplementationFile=SourceEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

