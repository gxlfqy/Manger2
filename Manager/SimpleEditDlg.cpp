// SimpleEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SimpleEditDlg.h"
#include "afxdialogex.h"


// CSimpleEditDlg 对话框

IMPLEMENT_DYNAMIC(CSimpleEditDlg, CDialogEx)

CSimpleEditDlg::CSimpleEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleEditDlg::IDD, pParent)
{

}

CSimpleEditDlg::~CSimpleEditDlg()
{
}

void CSimpleEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSimpleEditDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimpleEditDlg 消息处理程序
