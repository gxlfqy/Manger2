// PatientDirectoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PatientDirectoryDlg.h"
#include "InputDataBaseInfoDlg.h"
#include "InitDlg.h"
#include "DataIDDlg.h"
#include "FindDlg.h"
#include "ManagerDlg.h"
#include "ManagerADO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPatientDirectoryDlg 对话框

IMPLEMENT_DYNAMIC(CPatientDirectoryDlg, CDialogEx)

CPatientDirectoryDlg::CPatientDirectoryDlg(CWnd* pParent /*=NULL*/)
: CMyDialogEx(CPatientDirectoryDlg::IDD, pParent),
m_listCtrl(m_data)
{
}

CPatientDirectoryDlg::~CPatientDirectoryDlg()
{
}

void CPatientDirectoryDlg::InitListCtrl()
{
	std::vector<CMyListCtrl<PersonBaseData>::listColsInfo> colsInfo;
	static const CMyListCtrl<PersonBaseData>::listColsInfo listInfo[] = {
		{ L"病历ID", 150 }, { L"姓名", 120 }, { L"性别", 50 }, { L"年龄", 60 }, { L"CT号码", 120 }, { L"病理号码", 120 }
	};
	for (CMyListCtrl<PersonBaseData>::listColsInfo term : listInfo)
		colsInfo.push_back(term);

	m_listCtrl.Init(colsInfo);
}

void CPatientDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CPatientDirectoryDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPatientDirectoryDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_UPDATA, &CPatientDirectoryDlg::OnBnClickedUpdata)
	ON_WM_PAINT()
	ON_COMMAND(ID_CONDITION_QUERY_MENU, &CPatientDirectoryDlg::OnConditionQueryMenu)
	ON_COMMAND(ID_OUTPUT_DATAID, &CPatientDirectoryDlg::OnOutputDataid)
	ON_COMMAND(ID_SHOWALLDATA, &CPatientDirectoryDlg::OnShowalldata)
	ON_COMMAND(ID_PATIENTDIRECTORY_ADDINFO, &CPatientDirectoryDlg::OnPatientdirectoryAddinfo)
	ON_COMMAND(ID_LINKLOCALDATABASE, &CPatientDirectoryDlg::OnLinkdatabase)
	ON_COMMAND(ID_PART_CONDITION_QUERY_MENU, &CPatientDirectoryDlg::OnPartConditionQueryMenu)
END_MESSAGE_MAP()

BEGIN_SHORTKEYINFO_MAP(CPatientDirectoryDlg)
	ON_SHORTKEY(NULL, VK_F5, &CPatientDirectoryDlg::OnBnClickedUpdata)
END_SHORTKEYINFO_MAP

// CPatientDirectoryDlg 消息处理程序

BOOL CPatientDirectoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	InvalidateRect(NULL);
#ifndef _DEBUG
	GetMenu()->DeleteMenu(ID_OUTPUT_DATAID, MF_STRING);
#endif
	InitListCtrl();
	GetNewManagerDataAtDatabase();
	SetManagerDataToDailog();
	return TRUE;
}

//菜单-文件-录入病人信息
void CPatientDirectoryDlg::OnPatientdirectoryAddinfo()
{
	CManagerPersonData personData = COnlyMangerDlg::AddInfo(this);
	OnBnClickedUpdata();
}

//菜单-文件-查询信息-筛选条件
void CPatientDirectoryDlg::OnConditionQueryMenu()
{
	CFindDlg dlg;
	std::vector<_FindInfo> FindInfoList;
	UINT_PTR nRet = dlg.DoModal();
	if (nRet == IDOK)
	{
		FindInfoList = dlg.GetFindInfo();
		CPatientDirectoryDlg dlg;
		dlg.Unfold(FindInfoList);
	}
	return;
}

//菜单-文件-查询信息-本地查找
void CPatientDirectoryDlg::OnPartConditionQueryMenu()
{
	CFindDlg dlg;
	std::vector<_FindInfo> FindInfoList;
	UINT_PTR nRet = dlg.DoModal();
	if (nRet == IDOK)
	{
		FindInfoList = dlg.GetFindInfo();
// 		CPatientDirectoryDlg dlg;
// 		dlg.Unfold(m_data.GetMHIDList(), FindInfoList);
		CManagerData result;
		this->m_data.SelectManagerPersonData(FindInfoList, result);
		this->m_data = result;
		SetManagerDataToDailog();
	}
	return;
}

//菜单-文件-生成数据ID
void CPatientDirectoryDlg::OnOutputDataid()
{
	CDataIDDlg dlg;
	dlg.DoModal();
}

//菜单-数据库-连接至数据库
void CPatientDirectoryDlg::OnLinkdatabase()
{
	CInputDataBaseInfoDlg dlg;
	dlg.DoModal(CInputDataBaseInfoDlg::Local);
}

//菜单-病人目录-显示所有病人信息
void CPatientDirectoryDlg::OnShowalldata()
{
	CManagerStringADO::GetDataAtAllData(m_data);
	m_state = modeALL;
	m_listCtrl = m_data.GetBaseDataList();
}

//双击控件 ListCtrl 编辑对应 MHID 的病人信息
void CPatientDirectoryDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();//   返回列表中选中的第一项
	if (!pos)
		return;
	int nSel = m_listCtrl.GetNextSelectedItem(pos);
	CString szMHID = m_listCtrl.GetItemText(nSel, 0);
	CManagerPersonData personData;
	m_data.GetManagerPersonData(szMHID, personData);
	personData = COnlyMangerDlg::ModInfo(personData, this);
	OnBnClickedUpdata();
}

//重新从数据库获取信息
void CPatientDirectoryDlg::OnBnClickedUpdata() 
{
	GetNewManagerDataAtDatabase();
	SetManagerDataToDailog();
}

void CPatientDirectoryDlg::GetNewManagerDataAtDatabase()
{
	using namespace std;
	vector<CString> MHIDDelList;
	vector<CString>::iterator MHIDList_it;
	vector<CString>::iterator m_DataBaseMHID_it;
	switch (m_state)
	{
	case CPatientDirectoryDlg::modeALL:
		CManagerStringADO::GetDataAtAllData(m_data);
		break;
	case CPatientDirectoryDlg::modeAtMHID:
		CManagerStringADO::GetData(m_DataBaseMHID, m_data);
		break;
	case CPatientDirectoryDlg::modeAtFindInfo:
		CManagerStringADO::GetDataAtSelect(m_DataBaseFindInfo, m_data);
		break;
	case CPatientDirectoryDlg::modeAtMHIDFindInfo:
		CManagerStringADO::GetDataAtSelect(m_DataBaseFindInfo, m_data);
		MHIDDelList = m_data.GetMHIDList();
		for (MHIDList_it = MHIDDelList.begin(); MHIDList_it != MHIDDelList.end(); ++MHIDList_it)
		for (m_DataBaseMHID_it = m_DataBaseMHID.begin(); m_DataBaseMHID_it != m_DataBaseMHID.end(); ++m_DataBaseMHID_it)
		if (*MHIDList_it == *m_DataBaseMHID_it)
			MHIDList_it = MHIDDelList.erase(MHIDList_it);
		for (MHIDList_it = MHIDDelList.begin(); MHIDList_it != MHIDDelList.end(); ++MHIDList_it)
			m_data.DeleteManagerPersonData(*MHIDList_it);
		break;
	}
}

void CPatientDirectoryDlg::SetManagerDataToDailog()
{
	m_listCtrl = m_data.GetBaseDataList();
}

UINT_PTR CPatientDirectoryDlg::Unfold()
{
	UINT_PTR ret;
	m_state = modeALL;
	ret = DoModal();
	return ret;
}

UINT_PTR CPatientDirectoryDlg::Unfold(std::vector<CString> MHIDlist)
{
	UINT_PTR ret;
	m_DataBaseMHID = MHIDlist;
	m_state = modeAtMHID;
	ret = DoModal();
	return ret;
}

UINT_PTR CPatientDirectoryDlg::Unfold(std::vector<_FindInfo> selectList)
{
	UINT_PTR ret;
	m_DataBaseFindInfo = selectList;
	m_state = modeAtFindInfo;
	ret = DoModal();
	return ret;
}

UINT_PTR CPatientDirectoryDlg::Unfold(std::vector<CString> MHIDlist, std::vector<_FindInfo> selectList)
{
	UINT_PTR ret;
	m_DataBaseMHID = MHIDlist;
	m_DataBaseFindInfo = selectList;
	m_state = modeAtMHIDFindInfo;
	ret = DoModal();
	return ret;
}


LRESULT CPatientDirectoryDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef _GREEN_BAR_
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);

	if (!::IsWindow(m_hWnd))
		return lrst;

	DrawBorder(message, RGB(89, 163, 179));
	return lrst;
#else
	return CDialog::DefWindowProc(message, wParam, lParam);
#endif // _GREEN_BAR_
}
