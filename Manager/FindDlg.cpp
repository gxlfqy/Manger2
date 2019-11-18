// FindDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFindDlg �Ի���

IMPLEMENT_DYNAMIC(CFindDlg, CDialogEx)

CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
: CMyDialogEx(CFindDlg::IDD, pParent)
{
}

CFindDlg::~CFindDlg()
{
}

//��ʼ��ɸѡ������ʾ�ؼ� (ListBox)[CFindListCtrl]
void CFindDlg::InitFoundList()
{
	std::vector<CMyListCtrl<ListCtrlInfo>::listColsInfo> colsInfo;
	CMyListCtrl<ListCtrlInfo>::listColsInfo term;
	term.data = L"ɸѡ����";
	term.nLong = 180;
	colsInfo.push_back(term);
	term.data = L"��ֵ";
	term.nLong = 234;
	colsInfo.push_back(term);
	m_FoundListCtrl.Init(colsInfo);
}

//��ʼ��ɸѡ����ѡ��ؼ� (MFCButton)[CMyMFCMenuButton]
void CFindDlg::InitOptionsMenu()
{
	CBinaryTree<_menuInfo> &menuInfoBTree = m_OptionsMenuCtrl.m_menuInfobTree;
	menuInfoBTree.Root();
	void * menuInfoBTree_mark = nullptr;
	_menuInfo term;
	int i = 0;
	int m_ControlInfo_len = m_ControlInfo.size();
	tag_ef_connect temp;
	for (i = 0; i < 10; ++i)
	{
		term.title = g_DataType.TableName[i];
		term.nID = i;
		menuInfoBTree.Set(term);
		menuInfoBTree_mark = menuInfoBTree.GetMark();
		menuInfoBTree.Right();
		int time = 0;
		for (int j = 0; j < m_ControlInfo_len; ++j)
		{
			temp = m_ControlInfo.at(j);
			if (temp.nTable == i)
			{
				if (time != 0)
					menuInfoBTree.Left();
				term.nID = temp.ctrlID;
				term.title = temp.title;
				menuInfoBTree.Set(term);
				time++;
			}
		}
		menuInfoBTree.GotoMark(menuInfoBTree_mark);
		if (i != 9)
			menuInfoBTree.Left();
	}
	menuInfoBTree.Root();
	m_OptionsMenuCtrl.CreateDynamicMenu();
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCMENU1, m_OptionsMenuCtrl);
	DDX_Control(pDX, IDC_MFCMENU2, m_MFCMenu2Ctrl);
	DDX_Control(pDX, IDC_FOUND_LIST, m_FoundListCtrl);
}

BEGIN_MESSAGE_MAP(CFindDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCMENU1, &CFindDlg::OnBnClickedMfcmenu1)
	ON_BN_CLICKED(IDC_ADDOPTION, &CFindDlg::OnBnClickedAddoption)
	ON_BN_CLICKED(IDC_MFCMENU2, &CFindDlg::OnBnClickedMfcmenu2)
	ON_BN_CLICKED(IDOK, &CFindDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_BIM_EDIT, &CFindDlg::OnEnChangeBimEdit)
	ON_EN_CHANGE(IDC_DECIMAL_EDIT, &CFindDlg::OnEnChangeDecimalEdit)
	ON_EN_KILLFOCUS(IDC_DECIMAL_EDIT, &CFindDlg::OnEnKillfocusDecimalEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CFindDlg ��Ϣ�������

BOOL CFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	EasyStaticCtrlConnect &StaticCtrlInfo = EasyStaticCtrlConnect::GetInstance();
	m_ControlInfo = StaticCtrlInfo.GetData();
	InitOptionsMenu();
	InitFoundList();
	BanInputMethod(IDC_BIM_EDIT);
	BanInputMethod(IDC_DECIMAL_EDIT);
	InitFoundList();
	return TRUE;
}

//���ɸѡ����ѡ��ؼ�ʱ����Ϣӳ�亯�� (MFCButton)[CMyMFCMenuButton]
//���ܣ��ı�ɸѡ����ѡ��ؼ��ı��⣬��ʾ��Ӧ�� Edit�ؼ���ComboBox�ؼ� ��DateTimePicker �ؼ� �� MFCButtom�ؼ�
void CFindDlg::OnBnClickedMfcmenu1()
{
	int MenuRet = m_OptionsMenuCtrl.m_nMenuResult;
	if (MenuRet == 0)
		return;
	int nCountor = m_ControlInfo.size();
	int i;
	for (i = 0; i < nCountor; ++i)
	{
		if (MenuRet == m_ControlInfo.at(i).ctrlID)
		{
			SetDlgItemText(IDC_MFCMENU1, m_ControlInfo.at(i).title);
			goto Next;
		}
	}
	ASSERT(0);
	return;
Next:
	GetDlgItem(IDC_MFCMENU2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TIME1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BIM_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NUMBER_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DECIMAL_EDIT)->ShowWindow(SW_HIDE);
	int j;
	//Reset the content of the control
	((CComboBox *)GetDlgItem(IDC_COMBO))->ResetContent();
	SetDlgItemText(IDC_EDIT1, L"");
	SetDlgItemText(IDC_BIM_EDIT, L"");
	SetDlgItemText(IDC_NUMBER_EDIT, L"");
	SetDlgItemText(IDC_DECIMAL_EDIT, L"");
	m_MFCMenu2Ctrl.SetWindowText(L"");
	//Show the control in the order
	int ControlInfo_i_MenuInfo_len = 0;
	int term_attr = 0;
	switch (m_ControlInfo.at(i).ctrlName)
	{
	case ControlType::Edit:
		term_attr = m_ControlInfo.at(i).attr;
		if (term_attr & ES_ONLYINPUTNO)
			GetDlgItem(IDC_BIM_EDIT)->ShowWindow(SW_SHOW);
		else if (term_attr & ES_NUMBER)
			GetDlgItem(IDC_NUMBER_EDIT)->ShowWindow(SW_SHOW);
		else if (term_attr & ES_ONLYINPUTDECIMAL)
			GetDlgItem(IDC_DECIMAL_EDIT)->ShowWindow(SW_SHOW);
		else
			GetDlgItem(IDC_EDIT)->ShowWindow(SW_SHOW);
		break;
	case ControlType::ComboBox:
		ControlInfo_i_MenuInfo_len = m_ControlInfo.at(i).MenuInfo.size();
		for (j = 0; j < ControlInfo_i_MenuInfo_len; ++j)
			((CComboBox *)GetDlgItem(IDC_COMBO))->InsertString(j, m_ControlInfo.at(i).MenuInfo.at(j));
		GetDlgItem(IDC_COMBO)->ShowWindow(SW_SHOW);
		break;
	case ControlType::DateTimePicker:
		GetDlgItem(IDC_TIME1)->ShowWindow(SW_SHOW);
		break;
	case ControlType::MFCMenuButtonControl:
		GetDlgItem(IDC_MFCMENU2)->ShowWindow(SW_SHOW);
		m_MFCMenu2Ctrl.m_hMenu = m_ControlInfo.at(i).hMenu;
		break;
	}
	return;
}

//��� MFCMenuButton(��ɸѡ����ѡ��ؼ�) �ؼ�ʱ����Ϣӳ�亯�� (MFCButton)[CMyMFCMenuButton]
//���ܣ��� MFCButton �ؼ�ѡ���ѡ����������ʾ�� MFCButton �� captain ��
void CFindDlg::OnBnClickedMfcmenu2()
{
	if (m_MFCMenu2Ctrl.m_nMenuResult != 0)
	{
		int nID = m_OptionsMenuCtrl.m_nMenuResult;
		int m_ControlInfo_len = m_ControlInfo.size();
		tag_ef_connect term;
		CString data;
		for (int i = 0; i < m_ControlInfo_len; ++i)
		{
			term = m_ControlInfo.at(i);
			if (nID == term.ctrlID)
			{
				data = term.MFCMenuInfo->GetTreeString(m_MFCMenu2Ctrl.m_nMenuResult, L"-");
				m_MFCMenu2Ctrl.SetWindowText(data);
			}
		}
	}
}

//������������Button��Ӧ����Ϣӳ�亯��
//���ܣ�ͨ��
void CFindDlg::OnBnClickedAddoption()
{
	CString option;
	tag_dataType TableInfo;
	int m_FoundListCtrl_Length = m_FoundListCtrl.GetItemCount();
	int nID = m_OptionsMenuCtrl.m_nMenuResult;
	if (nID == 0)
		return;
	int m_ControlInfo_len = m_ControlInfo.size();
	tag_ef_connect term;
	ListCtrlInfo find_term;
	for (int i = 0; i < m_ControlInfo_len; ++i)
	{
		term = m_ControlInfo.at(i);
		if (nID == term.ctrlID)
		{
			find_term.title = TableInfo.TableName[term.nTable] + L"-" + term.title;
			int ControlInfo_i_MenuInfo_len = 0;
			int term_attr = 0;
			CString data;
			switch (term.ctrlName)
			{
			case ControlType::Edit:
				term_attr = term.attr;
				if (term_attr & ES_ONLYINPUTNO)
					GetDlgItem(IDC_BIM_EDIT)->GetWindowText(data);
				else if (term_attr & ES_NUMBER)
					GetDlgItem(IDC_NUMBER_EDIT)->GetWindowText(data);
				else if (term_attr & ES_ONLYINPUTDECIMAL)
					GetDlgItem(IDC_DECIMAL_EDIT)->GetWindowText(data);
				else
					GetDlgItem(IDC_EDIT)->GetWindowText(data);
				break;
			case ControlType::ComboBox:
				GetDlgItem(IDC_COMBO)->GetWindowText(data);
				break;
			case ControlType::DateTimePicker:
				GetDlgItem(IDC_TIME1)->GetWindowText(data);
				break;
			case ControlType::MFCMenuButtonControl:
				GetDlgItem(IDC_MFCMENU2)->GetWindowText(data);
				break;
			}
			find_term.data = data;
			find_term.IDName = term.IDName;
			find_term.table = TableInfo[term.nTable];
			m_FoundListCtrl.AddItemToRear(find_term);
			break;
		}
	}
}
