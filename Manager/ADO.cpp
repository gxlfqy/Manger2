#include "stdafx.h"
#include "ADO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ADO::ADO()
{
}

ADO::~ADO()
{
}


void ADO::OnInitADOConn()
{
	::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");
		_bstr_t strConnect = "Driver=SQL Server;server=127.0.0.1,1433;DATABASE=BASICINFO_MHID";
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}


void ADO::ExitConnect()
{
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	::CoUninitialize();
}

_RecordsetPtr ADO::Select(CString sql)
{
	_bstr_t CommandText(sql);						// ����Ҫִ�е� sql ����ַ���
	m_pRecordset.CreateInstance("ADODB.Recordset"); // ����_RecordsetPtr ʵ��
	m_pRecordset->Open(CommandText,					// �������ݿ��ѯ
		m_pConnection.GetInterfacePtr(),
		adOpenDynamic,
		adLockBatchOptimistic,
		adCmdText);
	return m_pRecordset;
}

BOOL ADO::Execute(CString sql)
{
	_bstr_t CommandText(sql);
	_variant_t RecordsAffected;
	m_pConnection->Execute(CommandText, &RecordsAffected, adCmdText);
	return TRUE;
}
