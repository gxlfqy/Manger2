#pragma once
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class ADO
{
public:
	ADO();
	~ADO();
	_ConnectionPtr m_pConnection;	// Êý¾Ý¿â
	_RecordsetPtr m_pRecordset;		// ÃüÁî
	_CommandPtr m_pCommand;			// ¼ÇÂ¼
	void OnInitADOConn();
	void ExitConnect();
	_RecordsetPtr ADO::Select(CString sql);
	BOOL ADO::Execute(CString sql);
};