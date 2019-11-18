#include "AdoController.h"
#include <iostream>
#include <stdexcept>
#include <boost\algorithm\string.hpp>

CAdoController::~CAdoController(void)
{
	if (m_pConnection->State)
	{
		m_pConnection->Close();
	}
	m_pCommand.Release();
	m_pRecordset.Release();
	m_pConnection.Release();
}

bool CAdoController::init()
{
	HRESULT hr;

	hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (!SUCCEEDED(hr))
	{
		return false;
	}

	hr = m_pCommand.CreateInstance("ADODB.Command");
	if (!SUCCEEDED(hr))
	{
		return false;
	}

	hr = m_pRecordset.CreateInstance("ADODB.Recordset");
	if (!SUCCEEDED(hr))
	{
		return false;
	}

	return true;
}

bool CAdoController::Connect(DatabaseProviderEnum database, std::string dataSource,
	std::string ip, std::string username, std::string psw)
{
	if (m_pConnection->State)
	{
		m_pConnection->Close();
	}
	std::string connectstring = connectStringBuilder(database, ip, dataSource, username, psw);
	return Connect(connectstring);
}

bool CAdoController::Connect(const std::string connectstring)
{
	HRESULT hr;
	try
	{
		hr = m_pConnection->Open(_bstr_t(connectstring.c_str()), "", "", adModeUnknown);
		if (!SUCCEEDED(hr))
		{
			throw std::exception();
		}
		return true;
	}
	catch (_com_error e)
	{
		std::cerr << "连接数据库失败！" << std::endl
			<< e.Description() << std::endl;
		return false;
	}
}

std::string CAdoController::connectStringBuilder(DatabaseProviderEnum database,
	std::string &ip, std::string dataSource,
	std::string username, std::string psw)
{
	std::string connectstring;
	switch (database)
	{
	case CAdoController::Access2000:
		connectstring += "Provider=Microsoft.Jet.OLEDB.4.0;DataSource=";
		if (ip.length() != 0)
		{
			connectstring += "\\\\" + ip + "\\" + dataSource + ";";
		}
		else
		{
			connectstring += dataSource + ";";
		}
		connectstring += username + ";";
		connectstring += psw + ";";
		break;
	case CAdoController::ODBC:
		//FIXIT: 远程连接字符串待添加
		connectstring += "Provider=MADASQL;DSN=" + dataSource + ";UID=" +
			username + ";PWD=" + psw + ";";
		break;
	case CAdoController::Oracle:
		//FIXIT: 远程连接字符串待添加
		connectstring += "Provider=MSDAORA;DataSource=" + dataSource + ";User ID=" +
			username + ";Password=" + psw + ";";
		break;
	case CAdoController::SqlServer:
		if (username != "")
		{
			connectstring += "Provider=SQLOLEDB;DataSource=" + ip + ";Initial Catalog=" +
				dataSource + ";UserID=" + username + ";Password=" + psw + ";";
		}
		else
		{
			connectstring += "Provider=SQLOLEDB;DataSource=.;Initial Catalog=" +
				dataSource + ";Integrated Security=SSPI;";
		}
		break;
	default:
		break;
	}
	return connectstring;
}

int CAdoController::ExecuteNonQuery(const std::string& command)
{
	if (boost::istarts_with(command, "select"))
	{
		throw std::exception("SELECT command queried, you should use ExecuteReader Instead!");
		return 0;
	}
	if (!m_pConnection->State)
	{
		throw std::exception("数据库连接尚未打开");
		return 0;
	}
	_variant_t effectLineCount = 0;
	m_pConnection->Execute(_bstr_t(command.c_str()), &effectLineCount, adCmdText);

	return (int)effectLineCount;
}

//执行查询命令，注意这里会抛出异常
AdoRecordReader CAdoController::ExecuteReader(const std::string& command)
{
	if (!boost::istarts_with(command, "select"))
	{
		throw std::exception("Non SELECT command executed, you should user ExecuteNonQuery instead");
	}
	if (!m_pConnection->State)
	{
		std::cerr << "数据库连接尚未打开" << std::endl;
		throw std::exception("数据库未打开");
	}

	_variant_t conn = _variant_t((IDispatch *)m_pConnection, true);

	try
	{
		if (m_pRecordset->State)
		{
			m_pRecordset->Close();
		}
		m_pRecordset->Open(_variant_t(command.c_str()), conn, adOpenStatic,
			adLockOptimistic, adCmdText);
		return AdoRecordReader(m_pRecordset);
	}
	catch (_com_error e)
	{
		std::cerr << e.Description() << std::endl;
		throw std::exception("查询出现错误");
	}
}

_variant_t AdoRecordReader::operator[](const size_t index) const
{
	try
	{
		return m_recordSetPtr->GetCollect(_variant_t((long)index));
	}
	catch (_com_error e)
	{
		std::cerr << e.Description() << std::endl;
		return NULL;
	}
}

_variant_t AdoRecordReader::operator[](const std::string key) const
{
	try
	{
		return m_recordSetPtr->GetCollect(_variant_t(key.c_str()));
	}
	catch (_com_error e)
	{
		std::cerr << e.Description() << std::endl;
		return NULL;
	}
}