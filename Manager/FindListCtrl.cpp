#include "stdafx.h"
#include "FindListCtrl.h"

#define ID_FINDOPTION_DEL 32840

BEGIN_MESSAGE_MAP(CFindListCtrl, CMyListCtrl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_FINDOPTION_DEL, &CFindListCtrl::OnFindListCtrlDelOption)
END_MESSAGE_MAP()

std::vector<_FindInfo> CFindListCtrl::GetListInfo()
{
	std::vector<_FindInfo> FindInfoList;
	FindInfoList.clear();
	ListCtrlInfo * p = m_dataList.Next(CMyList<ListCtrlInfo>::NextAtHead);
	_FindInfo temp;
	while (p != nullptr)
	{
		temp.data = p->data;
		temp.IDName = p->IDName;
		temp.table = p->table;
		FindInfoList.push_back(temp);
		p = m_dataList.Next();
	}
	return FindInfoList;
}

void CFindListCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu*   pPopup = new CMenu;
	pPopup->CreatePopupMenu();
	pPopup->AppendMenu(MF_STRING, ID_FINDOPTION_DEL, L"删除条件");
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, this); //在鼠标当前位置弹出菜单
}

void CFindListCtrl::OnFindListCtrlDelOption()
{
	POSITION pos = GetFirstSelectedItemPosition();//   返回列表中选中的第一项
	if (!pos)
		return;
	int nSel = GetNextSelectedItem(pos);
	DeleteItem(nSel);
}


void CFindListCtrl::AddItemToRear(ListCtrlInfo _item)
{
	ListCtrlInfo * p = m_dataList.Next(CMyList<ListCtrlInfo>::NextAtHead);
	int nIndex = -1;
	while (p)
	{
		nIndex++;
		if (p->IDName == _item.IDName)
		{
			p->data = _item.data;
			p->table = _item.table;
			p->title = _item.title;
			SetItemText(nIndex, 0, _item.title);
			SetItemText(nIndex, 1, _item.data);
			return;
		}
		p = m_dataList.Next();
	}
	m_dataList.AddRear(_item);
	int listCtrl_len = GetItemCount();
	InsertItem(listCtrl_len, NULL);
	SetItemText(listCtrl_len, 0, _item.title);
	SetItemText(listCtrl_len, 1, _item.data);
}