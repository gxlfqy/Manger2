#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "MyList.h"
#include <vector>

template<typename T>
class CMyListCtrl :
	public CListCtrl
{
public:
	struct listColsInfo
	{
		CString data;
		int nLong = 0;
		listColsInfo(){ }
		listColsInfo(CString str, int n)
		{
			data = str;
			nLong = n;
		}
	};
public:
	void Init(std::vector<listColsInfo> colsInfo)
	{
		DWORD Style = GetExtendedStyle();
		Style |= LVS_EX_FULLROWSELECT;
		Style |= LVS_EX_GRIDLINES;
		SetExtendedStyle(Style);
		int list_len = colsInfo.size();
		listColsInfo term;
		for (int i = 0; i < list_len; ++i)
		{
			term = colsInfo.at(i);
			InsertColumn(i, term.data, LVCFMT_LEFT, term.nLong);
		}
	}
	CMyList<T> m_dataList;
	virtual void AddItemToRear(T _item) = 0;
	virtual void DeleteAllItems()
	{
		CListCtrl::DeleteAllItems();
		m_dataList.DelAllNode();
	}
	virtual void DeleteItem(int nSel)
	{
		CListCtrl::DeleteItem(nSel);
		m_dataList.DelNode(nSel);
	}
	void operator=(std::vector<T> list)
	{
		int i, nLen = list.size();
		for (i = 0; i < nLen; ++i)
			AddItemToRear(list.at(i));
	}
	CMyList<T> GetListInfo()
	{
		return m_dataList;
	}
	void operator=(CMyListCtrl<T> ListCtrl)
	{
		CMyList<T> ListInfo = ListCtrl.GetListInfo();
		m_dataList = ListInfo;
		UpdateListCtrl();
	}
	void UpdateListCtrl()
	{
		CMyList<T> ListInfo = m_dataList;
		DeleteAllItems();
		T * pt = ListInfo.Next(CMyList<T>::NextAtHead);
		while (pt)
		{
			AddItemToRear(*pt);
			pt = ListInfo.Next();
		}
	}
};
