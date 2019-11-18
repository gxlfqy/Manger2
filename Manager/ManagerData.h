#pragma once
#include "EasyStaticCtrlConnect.h"
//#include "PatientDirectoryListCtrl.h"
#include "ManagerPersonData.h"
#include "FindListCtrl.h"

class CManagerData
{
public:
	CManagerData()
	{
	}
	CManagerData(CManagerData & obj);
protected:
	std::vector<CManagerPersonData> m_dataList;

public:
	BOOL HaveMHID(const CString szMHID);
	void Clear() {
		m_dataList.clear();
	}
	bool Empty() {
		return m_dataList.empty();
	}
	void AddManagerPersonData(CManagerPersonData data) {
		m_dataList.push_back(data);
	}
	BOOL GetManagerPersonData(const CString szMHID, CManagerPersonData &outPersonData);
	void SetManagerPersonData(const CString szMHID, const CString szIDName, const CString szData);
	void SetManagerPersonData(const CString szMHID, DataBaseTable data);
	void SetManagerPersonData(CManagerPersonData personData);
	void DeleteManagerPersonData(const CString szMHID);
	bool SelectManagerPersonData(std::vector<_FindInfo> FindInfoList, CManagerData & outManagerData);
	static int GetInitDataBaseTableNum() {
		return CManagerPersonData::GetTableNum();
	}
	std::vector<PersonBaseData> GetBaseDataList();
	std::vector<CString> GetMHIDList();
	std::vector<CManagerPersonData> GetAllData()
	{
		std::vector<CManagerPersonData> result(m_dataList.begin(), m_dataList.end());
		return result;
	}
	std::vector<CManagerPersonData>& operator=(std::vector<CManagerPersonData>& obj);
	CManagerData& operator=(CManagerData& obj);
};