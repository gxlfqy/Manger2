#include "stdafx.h"
#include "ManagerADO.h"

CManagerStringADO g_SQL;

CString CManagerStringADO::GetSelectState(std::vector<_FindInfo> FindInfo)
{
	static int nFindInfoLen = FindInfo.size();
	static int nIndex = 0;
	CString szContent;
	CString temp;
	szContent = L"select BASICINFO_MHID from ";
	szContent += FindInfo.at(nIndex).table + L" where ";
	szContent += FindInfo.at(nIndex).IDName + L" = \'" + FindInfo.at(nIndex).data + L"\'";
	if (nIndex < nFindInfoLen - 1)
	{
		nIndex++;
		temp = GetSelectState(FindInfo);
		szContent += L" and BASICINFO_MHID in (" + temp + L")";
	}
	return szContent;
}

bool CManagerStringADO::LinkLocalDataBase(CString szName)
{
	return LinkDataBase(szName, L"127.0.0.1,1433", L"", L"");
}

bool CManagerStringADO::LinkDataBase(CString szName, CString szIP, CString szUserName, CString szPass)
{
	_bstr_t ip = szIP;
	_bstr_t name = szName;
	_bstr_t userName = szUserName;
	_bstr_t pass = szPass;
	::CoInitialize(NULL);
	try
	{
		g_SQL.m_pConnection.CreateInstance("ADODB.Connection");
		CString temp;
		_bstr_t strConnect = "Driver=SQL Server;server=";
		strConnect += ip += ";DATABASE=";
		strConnect += name;
		g_SQL.m_pConnection->Open(strConnect, userName, pass, adModeUnknown);
	}
	catch (_com_error e)
	{
		return false;
	}
	return true;
}

void CManagerStringADO::ExitConnect()
{
	g_SQL.ADO::ExitConnect();
}

CManagerStringADO::FindState CManagerStringADO::GetData(const CString szMHID, CManagerPersonData & outData)
{
	outData.Reset();
	CManagerPersonData result;
	CManagerStringADO::FindState ret = CManagerStringADO::UnFind;
	std::vector<DataBaseTable> temp = outData.GetAllData();
	std::vector<DataBaseTable>::iterator table;
	std::vector<ManagerData>::iterator list;
	CString sql, content;
	_RecordsetPtr RecordSet;
	for (table = temp.begin(); table != temp.end(); ++table)
	{
		sql = L"SELECT * FROM ";
		sql += table->tableIDName + L" WHERE BASICINFO_MHID = \'";
		sql += szMHID + L"\'";
		try{ RecordSet = g_SQL.Select(sql); }
		catch (...)
		{
			ret = CManagerStringADO::Miss;
			continue;
		}
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		{
			try
			{
				content = RecordSet->GetCollect(list->IDName.GetBuffer()); 
				ret = CManagerStringADO::Miss != ret ? CManagerStringADO::Find : CManagerStringADO::Miss;
			}
			catch (...)
			{
				ret = CManagerStringADO::Miss;
				continue;
			}
			result.SetData(list->IDName, content);
		}
	}
	if (CManagerStringADO::UnFind != ret)
		outData = result;
	return ret;
}

CManagerStringADO::FindState CManagerStringADO::GetData(std::vector<CString> szMHIDList, CManagerData & outData)
{
	outData.Clear();
	std::vector<CString>::iterator it;
	CManagerStringADO::FindState ret = CManagerStringADO::UnFind, findResult;
	CManagerPersonData temp;
	CManagerData result;
	for (it = szMHIDList.begin(); it != szMHIDList.end(); ++it)
	{
		switch (findResult = GetData(*it, temp))
		{
		case CManagerStringADO::Find:
			ret = CManagerStringADO::Miss != ret ? CManagerStringADO::Find : CManagerStringADO::Miss;
			break;
		case CManagerStringADO::Miss:
			ret = CManagerStringADO::Miss;
			break;
		case CManagerStringADO::UnFind:
			ret = CManagerStringADO::UnFind != ret ? CManagerStringADO::Miss : CManagerStringADO::UnFind;
			break;
		}
		if (CManagerStringADO::UnFind != findResult)
			result.AddManagerPersonData(temp);
	}
	if (CManagerStringADO::UnFind != ret)
		outData = result;
	return ret;
}

BOOL CManagerStringADO::GetDataAtSelect(std::vector<_FindInfo> FindInfo, CManagerData & outData)
{
	using namespace std;
	outData.Clear();
	CManagerData result;
	CManagerPersonData temp;
	CString content;
	content = GetSelectState(FindInfo);
	_RecordsetPtr RecordSet;
	vector<CString> MHIDList;
	vector<CString>::iterator it;
	try
	{
		RecordSet = g_SQL.Select(content); 
		while (!RecordSet->adoEOF)
		{
			content = RecordSet->GetCollect("BASICINFO_MHID");
			MHIDList.push_back(content);
			RecordSet->MoveNext();
		}
	}
	catch (...)
	{
		return FALSE;
	}
	for (it = MHIDList.begin(); it != MHIDList.end(); ++it)
	{
		if (GetData(*it, temp) != CManagerStringADO::UnFind) {
			result.AddManagerPersonData(temp);
		}
	}
	if (result.Empty())
		return FALSE;
	else
		outData = result;
	return TRUE;
}

CManagerStringADO::FindState CManagerStringADO::GetDataAtAllData(CManagerData &outData)
{
	using namespace std;
	outData.Clear();
	CManagerData result;
	vector<DataBaseTable> model = CManagerPersonData::GetResetDataBaseTable();
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	_RecordsetPtr RecordSet;
	CString szSql = L"SELECT * FROM ";
	CString szMHID;
	DataBaseTable term;
	CManagerStringADO::FindState ret = CManagerStringADO::UnFind;
	for (table = model.begin(); table != model.end(); ++table)
	{
		try
		{
			RecordSet = g_SQL.Select(szSql + table->tableIDName);
			while (!RecordSet->adoEOF)
			{
				szMHID = RecordSet->GetCollect("BASICINFO_MHID");
				if (L"" != szMHID)
				{
					for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
						result.SetManagerPersonData(szMHID, list->IDName, RecordSet->GetCollect(list->IDName.GetBuffer()));
				}
				RecordSet->MoveNext();
			}
			ret = CManagerStringADO::Miss == ret ? CManagerStringADO::Miss : CManagerStringADO::Find;
		}
		catch (...)
		{
			ret = CManagerStringADO::Miss;
			continue;
		}
	}
	if (CManagerStringADO::UnFind != ret)
		outData = result;
	return CManagerStringADO::Find;
}

//return All Save or not 
BOOL CManagerStringADO::SentManagerPersonDataToDataBase(CManagerPersonData person)
{
	using namespace std;
	CString szSql, szCols, szContent;
	CString szMHID = person.GetMHID();
	if (IsHava(szMHID))
		DeleteDataAtMHID(szMHID);
	BOOL bRet = TRUE;
	vector<DataBaseTable> data = person.GetAllData();
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	for (table = data.begin(); table != data.end(); ++table)
	{
		szSql = L"INSERT INTO " + table->tableIDName;
		szCols = L"(";
		szContent = L"values(";
		for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		{
			if (list != table->tableData.begin()) 
				szCols += L",", szContent += L",";
			szCols += list->IDName;
			szContent += L"\'" + list->data + L"\'";
		}
		szCols += L")", szContent += L")";
		szSql += L" " + szCols + L" " + szContent;
		try{ g_SQL.Execute(szSql); }
		catch (...){ bRet = FALSE; }
	}
	return bRet;
}

BOOL CManagerStringADO::IsHava(const CString szMHID)
{
	CString sql;
	_RecordsetPtr RecordSet;
	sql = L"SELECT * FROM BASICINFO  WHERE BASICINFO_MHID = \'";
	sql += szMHID + L"\'";
	try{ RecordSet = g_SQL.Select(sql); }
	catch (...){ }
	if (!RecordSet->adoEOF)
		return TRUE;
	return FALSE;
}

void CManagerStringADO::DeleteDataAtMHID(const CString MHID)
{
	CString szSql;
	std::vector<DataBaseTable> DataBaseTableModel = CManagerPersonData::GetResetDataBaseTable();
	std::vector<DataBaseTable>::reverse_iterator table;
	for (table = DataBaseTableModel.rbegin(); table != DataBaseTableModel.rend(); ++table)
	{
		szSql = L"DELETE FROM " + table->tableIDName + L" WHERE BASICINFO_MHID = ";
		szSql += MHID;
		//If deleting data fail, think the data isn't exist.
		try{ g_SQL.Execute(szSql); }
		catch (...){ continue; }
	}
}
