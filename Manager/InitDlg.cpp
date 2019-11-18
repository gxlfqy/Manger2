#include "stdafx.h"
#include "InitDlg.h"
#include "afxdialogex.h"

// CInitDlg ¶Ô»°¿ò

IMPLEMENT_DYNAMIC(CInitDlg, CDialogEx)

CInitDlg::CInitDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CInitDlg::IDD, pParent), m_isOver(false), m_nShowTimer(0)
{
}

void CInitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInitDlg, CDialogEx)
	ON_WM_NCPAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CInitDlg::OnNcPaint()
{
	if (m_isShow)
		CDialog::OnNcPaint();
	else
	{
		if (m_nShowTimer > -1)
		{
			m_nShowTimer--;
			ShowWindow(SW_HIDE);
		}
		else
			CDialog::OnNcPaint();
	}
}

#define TIMER_JUDGEISOVER 0x00000001L

BOOL CInitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_isOver = false;
	m_nShowTimer = 2;
	SetTimer(TIMER_JUDGEISOVER, m_nUpdateTime, NULL);
	SetDlgItemText(IDC_STATIC, m_szContent);
	return TRUE;
}

void CInitDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIMER_JUDGEISOVER:
		if (m_isOver == true)
		{
			KillTimer(TIMER_JUDGEISOVER);
			OnCancel();
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
