
// Manager.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "FindDlg.h"
#include "ManagerADO.h"
#include "PatientDirectoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CManagerApp

BEGIN_MESSAGE_MAP(CManagerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CManagerApp 构造

CManagerApp::CManagerApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CManagerApp theApp;

BOOL CManagerApp::InitInstance()
{
#if defined(_SKIN_)
	skinppLoadSkin(_T("avfone.ssk"));
#endif
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//CManagerDlg dlg;
	g_SQL.LinkLocalDataBase(L"BASICINFO_MHID");
	//CWinThread *pThread = AfxBeginThread(ThreadFunc, NULL);
	COnlyMangerDlg::InitOnlyMangerDlg();
	CPatientDirectoryDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.Unfold();
	nResponse = IDOK;
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	return FALSE;
}

int CManagerApp::ExitInstance()
{
#if defined(_SKIN_)
	skinppExitSkin();
#endif
	return CWinApp::ExitInstance();
}
