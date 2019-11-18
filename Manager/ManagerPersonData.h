#pragma once
#include <vector>
#include "EasyStaticCtrlConnect.h"

struct PersonBaseData
{
	CString MHID;
	CString name;
	CString sex;
	CString age;
	CString CTNO;
	CString PathologyNO;
};

class CManagerPersonData
{
protected:
	std::vector<DataBaseTable> m_data;
	void SameMHID();

public:
	CManagerPersonData(){ Reset(); }
	CManagerPersonData(const CManagerPersonData& obj);
	~CManagerPersonData(){ }
	std::vector<DataBaseTable> GetAllData() const{
		return m_data;
	}
	static std::vector<DataBaseTable> GetResetDataBaseTable() {
		EasyStaticCtrlConnect & controlInfo = EasyStaticCtrlConnect::GetInstance();
		return controlInfo.GetDataBaseDataTemplate();
	}
	void Reset() {
		EasyStaticCtrlConnect & controlInfo = EasyStaticCtrlConnect::GetInstance();
		m_data = controlInfo.GetDataBaseDataTemplate();
	}
	CString GetMHID() {
		CString szMHID;
		GetData(L"BASICINFO_MHID", szMHID);
		return szMHID;
	}
	BOOL GetData(const CString szIDName, ManagerData & outData);
	BOOL GetData(const int nCtrlID, ManagerData & outData);
	BOOL GetData(const CString szIDName, CString & outData);
	BOOL SetData(const CString szIDName, const CString data);
	BOOL SetData(const int nCtrlID, const CString data);
	BOOL SetData(DataBaseTable datda);
	BOOL isEmpty();
	static int GetTableNum() {
		EasyStaticCtrlConnect & controlInfo = EasyStaticCtrlConnect::GetInstance();
		return int(controlInfo.GetDataBaseDataTemplate().size());
	}
	PersonBaseData GetBaseInfo();
	std::vector<DataBaseTable>& operator=(std::vector<DataBaseTable>& data);
	void operator=(const CManagerPersonData& obj);

	class ReadIterator
	{
	protected:
		std::vector<ManagerData> m_dataList;
		std::vector<ManagerData>::iterator m_it;

	public:
		ReadIterator()
		{
			using namespace std;
			vector<DataBaseTable>::iterator table;
			vector<ManagerData>::iterator list;
			vector<DataBaseTable> model = EasyStaticCtrlConnect::GetInstance().GetDataBaseDataTemplate();
			for (table = model.begin(); table != model.end(); ++table)
				m_dataList.insert(m_dataList.end(), table->tableData.begin(), table->tableData.end());
			m_it = m_dataList.begin();
		}
		ReadIterator(CManagerPersonData obj)
		{
			using namespace std;
			vector<DataBaseTable>::iterator table;
			vector<ManagerData>::iterator list;
			vector<DataBaseTable> data = obj.GetAllData();
			for (table = data.begin(); table != data.end(); ++table)
				m_dataList.insert(m_dataList.end(), table->tableData.begin(), table->tableData.end());
			m_it = m_dataList.begin();
		}
		void operator=(std::vector<ManagerData>::iterator it) {
			m_it = it;
		}
		std::vector<ManagerData>::iterator Begin() {
			return m_dataList.begin();
		}
		std::vector<ManagerData>::iterator End() {
			return m_dataList.end();
		}
		ReadIterator operator++()
		{
			++m_it;
			return *this;
		}
		static std::vector<CString> GetIDNameList() {
			using namespace std;
			vector<CString> result;
			vector<ManagerData> dataList;
			vector<ManagerData>::iterator it;
			vector<DataBaseTable> model = EasyStaticCtrlConnect::GetInstance().GetDataBaseDataTemplate();
			vector<DataBaseTable>::iterator table;
			for (table = model.begin(); table != model.end(); ++table)
				dataList.insert(dataList.end(), table->tableData.begin(), table->tableData.end());
			for (it = dataList.begin(); it != dataList.end(); ++it)
				result.push_back(it->IDName);
			return result;
		}
		operator ManagerData()const {
			return *m_it;
		}
		operator CString()const {
			return m_it->data;
		}

	};

};
