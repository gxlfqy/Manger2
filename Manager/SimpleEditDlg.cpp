// SimpleEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SimpleEditDlg.h"
#include "afxdialogex.h"


// CSimpleEditDlg �Ի���

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


// CSimpleEditDlg ��Ϣ�������
