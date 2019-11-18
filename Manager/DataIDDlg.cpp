// DataIDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "DataIDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDataIDDlg �Ի���

IMPLEMENT_DYNAMIC(CDataIDDlg, CDialogEx)

CDataIDDlg::CDataIDDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDataIDDlg::IDD, pParent)
{

}

CDataIDDlg::~CDataIDDlg()
{
}

void CDataIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CDataIDDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OUTTXT, &CDataIDDlg::OnBnClickedOuttxt)
	ON_WM_HOTKEY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CDataIDDlg ��Ϣ�������


BOOL CDataIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	EasyStaticCtrlConnect &StaticControlInfo = EasyStaticCtrlConnect::GetInstance();
	__EF__StaticCtrl = StaticControlInfo.GetData();
	::RegisterHotKey(GetSafeHwnd(), IDC_OUTTXT, MOD_ALT, 'O');
	CString IDTitle;
	CString IDName;
	int __EF__StaticCtrl_len = __EF__StaticCtrl.size();
	tag_ef_connect term;
	for (int i = 0; i < 10; ++i)
	{
		if (i != 0)
			m_listCtrl.AddString(L"");
		m_listCtrl.AddString(L"��" + StaticControlInfo.GetTableData().TableName[i]);
		m_listCtrl.AddString(StaticControlInfo.GetTableData().TableID[i]);
		for (int j = 0; j < __EF__StaticCtrl_len; ++j)
		{
			term = __EF__StaticCtrl.at(j);
			if (term.nTable == i)
			{
				m_listCtrl.AddString(L"IDTitle��" + term.title);
				m_listCtrl.AddString(L"IDName��" + term.IDName);
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDataIDDlg::OnBnClickedOuttxt()
{
	CString str;
	int i, nCount;
	CStdioFile * pFile = nullptr;
	str = setlocale(LC_CTYPE, ("chs"));
	pFile = new CStdioFile(L"out.txt", CFile::modeCreate | CFile::modeWrite);
	nCount = m_listCtrl.GetCount();
	for (i = 0; i < nCount; ++i)
	{
		m_listCtrl.GetText(i, str);
		str += "\n";
		pFile->WriteString(str.GetBuffer());
	}
	pFile->Close();
	delete pFile;
}

void CDataIDDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nHotKeyId)
	{
	case IDC_OUTTXT:
		OnBnClickedOuttxt();
		break;
	default:
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CDataIDDlg::OnOK()
{
}

void CDataIDDlg::OnPaint()
{
#ifdef _GREEN_BG_
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(199, 237, 204));   //����Ϊ��ɫ����
#else
	CPaintDC dc(this); // device context for painting
#endif
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
