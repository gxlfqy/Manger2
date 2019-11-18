#include "stdafx.h"
#include "ManagerData.h"

CManagerData::CManagerData(CManagerData & obj)
{
	using namespace std;
	vector<CManagerPersonData> list = obj.GetAllData();
	m_dataList.assign(list.begin(), list.end());
}

BOOL CManagerData::HaveMHID(const CString szMHID)
{
	using namespace std;
	vector<CManagerPersonData>::iterator it;
	if (m_dataList.empty())
		return FALSE;
	for (it = m_dataList.begin(); it != m_dataList.end(); ++it)
	{
		if (szMHID == it->GetMHID())
			return TRUE;
	}
	return FALSE;
}

BOOL CManagerData::GetManagerPersonData(const CString szIDName, CManagerPersonData &outPersonData)
{
	using namespace std;
	vector<CManagerPersonData>::iterator it;
	if (m_dataList.empty())
		return FALSE;
	for (it = m_dataList.begin(); it != m_dataList.end(); ++it)
	{
		if (szIDName == it->GetMHID())
		{
			outPersonData = *it;
			return TRUE;
		}
	}
	return FALSE;
}

void CManagerData::SetManagerPersonData(const CString szMHID, const CString szIDName, const CString szData)
{
	using namespace std;
	CManagerPersonData temp;
	temp.SetData(szIDName, szData);
	vector<CManagerPersonData>::iterator personIt;
	if (m_dataList.empty() || !HaveMHID(szMHID))
	{
		m_dataList.push_back(temp);
	}
	else
	{
		for (personIt = m_dataList.begin(); personIt != m_dataList.end(); ++personIt)
		{
			if (szMHID == personIt->GetMHID())
			{
				personIt->SetData(szIDName, szData);
				break;
			}
		}
	}
}

void CManagerData::SetManagerPersonData(CManagerPersonData personData)
{
	CManagerPersonData temp = personData;
	const CString szMHID = personData.GetMHID();
	std::vector<CManagerPersonData>::iterator personIt;
	if (m_dataList.empty() || !HaveMHID(szMHID))
		m_dataList.push_back(temp);
	else
	{
		for (personIt = m_dataList.begin(); personIt != m_dataList.end(); ++personIt)
		{
			if (szMHID == personIt->GetMHID())
			{
				personIt = m_dataList.erase(personIt);
				m_dataList.insert(personIt, personData);
				break;
			}
		}
	}
}

void CManagerData::SetManagerPersonData(const CString szMHID, DataBaseTable data)
{
	std::vector<CManagerPersonData>::iterator personIt;
	CManagerPersonData temp;
	if (m_dataList.empty() || !HaveMHID(szMHID))
		m_dataList.push_back(temp);
	else
	{
		GetManagerPersonData(szMHID, temp);
		temp.SetData(data);
		SetManagerPersonData(temp);
	}
}

void CManagerData::DeleteManagerPersonData(const CString szMHID)
{
	using namespace std;
	vector<CManagerPersonData>::iterator it;
	for (it = m_dataList.begin(); it != m_dataList.end(); ++it)
	{
		if (szMHID == it->GetMHID())
		{
			it = m_dataList.erase(it);
			return;
		}
	}
}

bool CManagerData::SelectManagerPersonData(std::vector<_FindInfo> FindInfoList, CManagerData & outManagerData)
{
	using namespace std;
	vector<_FindInfo>::iterator FindInfoListIt;
	vector<CManagerPersonData>::iterator ManagerDataListIt;
	ManagerData temp;
	bool isFound = false;
	outManagerData.Clear();
	if (this->m_dataList.empty())
		return false;
	for (ManagerDataListIt = this->m_dataList.begin(); ManagerDataListIt != this->m_dataList.end(); ++ManagerDataListIt)
	{
		isFound = true;
		for (FindInfoListIt = FindInfoList.begin(); FindInfoListIt != FindInfoList.end(); ++FindInfoListIt)
		{
			ManagerDataListIt->GetData(FindInfoListIt->IDName, temp);
			if (FindInfoListIt->data != temp.data)
			{
				isFound = false;
				break;
			}
		}
		if (isFound)
			outManagerData.AddManagerPersonData(*ManagerDataListIt);
	}
	return !outManagerData.Empty();
}

std::vector<PersonBaseData> CManagerData::GetBaseDataList()
{
	using namespace std;
	vector<PersonBaseData> list;
	vector<CManagerPersonData>::iterator it;
	PersonBaseData term;
	for (it = m_dataList.begin(); it != m_dataList.end(); ++it)
	{
		term = it->GetBaseInfo();
		list.push_back(term);
	}
	return list;
}

std::vector<CString> CManagerData::GetMHIDList()
{
	using namespace std;
	vector<CString> list;
	vector<CManagerPersonData>::iterator it;
	for (it = m_dataList.begin(); it != m_dataList.end(); ++it)
		list.push_back(it->GetMHID());
	return list;
}

std::vector<CManagerPersonData>& CManagerData::operator=(std::vector<CManagerPersonData>& obj)
{
	m_dataList.clear();
	m_dataList.assign(obj.begin(), obj.end());
	return m_dataList;
}

CManagerData& CManagerData::operator=(CManagerData& obj)
{
	using namespace std;
	vector<CManagerPersonData> list = obj.GetAllData();
	m_dataList.clear();
	m_dataList.assign(list.begin(), list.end());
	return *this;
}
