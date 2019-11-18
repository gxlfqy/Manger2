#pragma once 
#include "MyListCtrl.h"
#include "ManagerData.h"


class CPatientDirectoryListCtrl : public CMyListCtrl<PersonBaseData>
{
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void OnPatientDirectoryDelInfo();
	CPatientDirectoryListCtrl(CManagerData & data):m_data(data){
	}
public:
	friend class CPatientDirectoryDlg;
	CManagerData & m_data;
	std::vector<PersonBaseData> GetListInfo();
	virtual void AddItemToRear(PersonBaseData _item);
	void operator=(std::vector<PersonBaseData> data)
	{
		DeleteAllItems();
		if (data.empty())
			return;
		std::vector<PersonBaseData>::iterator it;
		for (it = data.begin(); it != data.end(); ++it)
			AddItemToRear(*it);
	}
};
