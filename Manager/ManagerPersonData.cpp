#include "stdafx.h"
#include "ManagerPersonData.h"

void CManagerPersonData::SameMHID()
{
	std::vector<DataBaseTable>::iterator table;
	std::vector<ManagerData>::iterator list;
	const CString szMHID = GetMHID();
	ManagerData temp;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	{
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		{
			if (list->IDName == L"BASICINFO_MHID")
			{
				temp = *list;
				temp.data = szMHID;
				list = table->tableData.erase(list);
				table->tableData.insert(list, temp);
				break;
			}
		}
	}
}

CManagerPersonData::CManagerPersonData(const CManagerPersonData& obj)
{
	using namespace std;
	vector<DataBaseTable> list = obj.GetAllData();
	m_data.assign(list.begin(), list.end());
}

BOOL CManagerPersonData::GetData(const CString szIDName, ManagerData & outData)
{
	std::vector<DataBaseTable>::iterator table;
	std::vector<ManagerData>::iterator list;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	{
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		{
			if (szIDName == list->IDName)
			{
				outData = *list;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CManagerPersonData::GetData(const int nCtrlID, ManagerData & outData)
{
	std::vector<DataBaseTable>::iterator table;
	std::vector<ManagerData>::iterator list;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	{
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		{
			if (nCtrlID == list->ctrlID)
			{
				outData = *list;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CManagerPersonData::GetData(const CString szIDName, CString & outData)
{
	BOOL bRet;
	ManagerData temp;
	bRet = GetData(szIDName, temp);
	if (bRet == TRUE)
	{
		outData = temp.data;
		return FALSE;
	}
	else
		return FALSE;
}

BOOL CManagerPersonData::SetData(const CString szIDName, const CString data)
{
	std::vector<DataBaseTable>::iterator table;
	std::vector<ManagerData>::iterator list;
	ManagerData term;
	int nIndex;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	{
		nIndex = 0;
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list, ++nIndex)
		{
			if (szIDName == list->IDName)
			{
				term = *list;
				term.data = data;
				list = table->tableData.erase(list);
				table->tableData.insert(list, term);
				list = table->tableData.begin() + nIndex;
				if (L"BASICINFO_MHID" == szIDName)
					SameMHID();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CManagerPersonData::SetData(const int nCtrlID, const CString data)
{
	using namespace std;
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	ManagerData term;
	int nIndex;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	{
		nIndex = 0;
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list, ++nIndex)
		{
			if (nCtrlID == list->ctrlID)
			{
				term = *list;
				term.data = data;
				list = table->tableData.erase(list);
				table->tableData.insert(list, term);
				list = table->tableData.begin() + nIndex;
				if (list->IDName == L"BASICINFO_MHID")
					SameMHID();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CManagerPersonData::SetData(DataBaseTable data)
{
	using namespace std;
	vector<ManagerData>::iterator it;
	BOOL bRet = TRUE;
	for (it = data.tableData.begin(); it != data.tableData.end(); ++it)
		bRet = bRet == FALSE || SetData(it->IDName, it->data) == FALSE ? FALSE : TRUE;
	return bRet;
}

BOOL CManagerPersonData::isEmpty()
{
	using namespace std;
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	for (table = m_data.begin(); table != m_data.end(); ++table)
	for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
	if (L"" != list->data)
		return FALSE;
	return TRUE;
}

PersonBaseData CManagerPersonData::GetBaseInfo()
{
	PersonBaseData result;
	GetData(L"BASICINFO_MHID", result.MHID);
	GetData(L"BASICINFO_NAME", result.name);
	GetData(L"BASICINFO_SEX", result.sex);
	GetData(L"BASICINFO_AGE", result.age);
	GetData(L"CTCHECK_CTNO", result.CTNO);
	GetData(L"PATHOLOGY_NO", result.PathologyNO);
	return result;
}

std::vector<DataBaseTable>& CManagerPersonData::operator=(std::vector<DataBaseTable>& data)
{
	using namespace std;
	Reset();
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	for (table = data.begin(); table != data.end(); ++table)
	for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		SetData(list->IDName, list->data);
	return m_data;
}

void CManagerPersonData::operator=(const CManagerPersonData& obj)
{
	using namespace std;
	vector<DataBaseTable> list = obj.GetAllData();
	m_data.clear();
	m_data.assign(list.begin(), list.end());
}
