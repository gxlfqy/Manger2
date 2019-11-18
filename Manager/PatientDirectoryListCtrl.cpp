#include "stdafx.h"
#include "PatientDirectoryListCtrl.h"
#include "InitDlg.h"
#include "ManagerDlg.h"

#define ID_PATIENTDIRECTORY_ADDINFO 32844
#define ID_PATIENTDIRECTORY_DELINFO 32850

BEGIN_MESSAGE_MAP(CPatientDirectoryListCtrl, CMyListCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PATIENTDIRECTORY_DELINFO, &CPatientDirectoryListCtrl::OnPatientDirectoryDelInfo)
END_MESSAGE_MAP()

void CPatientDirectoryListCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu*   pPopup = new CMenu;
	pPopup->CreatePopupMenu();
	pPopup->AppendMenuW(MF_STRING, ID_PATIENTDIRECTORY_DELINFO, L"删除");
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this); //在鼠标当前位置弹出菜单
}

void CPatientDirectoryListCtrl::OnPatientDirectoryDelInfo()
{
	POSITION pos = GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int nSel = GetNextSelectedItem(pos);
	CString MHID = GetItemText(nSel, 0);
	CManagerStringADO::DeleteDataAtMHID(MHID);
	DeleteItem(nSel);
}

void CPatientDirectoryListCtrl::AddItemToRear(PersonBaseData _item)
{
	m_dataList.AddRear(_item);
	int listCtrl_len = GetItemCount();
	InsertItem(listCtrl_len, NULL);
	SetItemText(listCtrl_len, 0, _item.MHID);
	SetItemText(listCtrl_len, 1, _item.name);
	SetItemText(listCtrl_len, 2, _item.sex);
	SetItemText(listCtrl_len, 3, _item.age);
	SetItemText(listCtrl_len, 4, _item.CTNO);
	SetItemText(listCtrl_len, 5, _item.PathologyNO);
}