
// Manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MyDialogEx.h"

// CManagerApp: 
// �йش����ʵ�֣������ Manager.cpp
//

class CManagerApp : public CWinApp
{
public:
	CManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CManagerApp theApp;

#if defined(_SKIN_)
#include "SkinPPWTL.h"
#pragma comment(lib, "SkinPPWTL.lib")
#endif