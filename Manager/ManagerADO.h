#pragma once
#include "ADO.h"
#include "ManagerData.h"
#include "ManagerPersonData.h"
#include "FindListCtrl.h"

//class of the Data for ManagerPerson  

//Connection Parameters of Database 
struct SDBConnectPragma
{
	CString Name;
	CString IP;
	CString UserName;
	CString Pass;
};

class CManagerStringADO :
	protected ADO
{
public:
	enum STATE
	{
		modeAdd = 0,
		modeEdit
	};
	enum FindState
	{
		Find,
		Miss,
		UnFind
	};
	CManagerStringADO() { };
	~CManagerStringADO() { };

protected:
	static CString GetSelectState(std::vector<_FindInfo> FindInfo);

public:
	static bool LinkLocalDataBase(CString szName);
	static bool LinkDataBase(CString szName, CString szIP, CString szUserName, CString szPass);
	static void ExitConnect();
	static CManagerStringADO::FindState GetData(const CString szMHID, CManagerPersonData & outData);
	static CManagerStringADO::FindState GetData(std::vector<CString> szMHIDList, CManagerData & outData);
	static BOOL GetDataAtSelect(std::vector<_FindInfo> FindInfo, CManagerData & outData);
	static CManagerStringADO::FindState GetDataAtAllData(CManagerData &outData);
	static BOOL SentManagerPersonDataToDataBase(CManagerPersonData person);
	static BOOL IsHava(const CString szMHID);
	static void DeleteDataAtMHID(const CString MHID);

};

extern CManagerStringADO g_SQL;
