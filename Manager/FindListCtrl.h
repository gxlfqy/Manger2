#pragma once

#include "MyListCtrl.h"

struct ListCtrlInfo
{
	CString data;
	CString IDName;
	CString table;
	CString title;
};

struct _FindInfo
{
	CString data;
	CString IDName;
	CString table;
	_FindInfo(){ }
	_FindInfo& operator=(ListCtrlInfo data)
	{
		_FindInfo & temp = *(this);
		temp.data = data.data;
		temp.IDName = data.IDName;
		temp.table = data.table;
		return temp;
	}
	_FindInfo(const ListCtrlInfo & obj)
	{
		data = obj.data;
		IDName = obj.IDName;
		table = obj.table;
	}
	_FindInfo(const _FindInfo & obj)
	{
		data = obj.data;
		IDName = obj.IDName;
		table = obj.table;
	}
};

class CFindListCtrl : public CMyListCtrl<ListCtrlInfo>
{
public:
	std::vector<_FindInfo> GetListInfo();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void OnFindListCtrlDelOption();
public:
	virtual void AddItemToRear(ListCtrlInfo _item);
};