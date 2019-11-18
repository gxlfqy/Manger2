/************************************************************************/
/* INSTRUCTION: 封装ADO数据库相关操作
DETAILS: 只能在MFC下使用，因此使用了MFC的字符串类
尝试进行了深度封装，但是很多选项(如存储过程)被屏蔽了，适合小型项目使用。
NOTE: ADO数据库访问并不是线程安全的，多个线程公用一个Connection需要线程同步，推荐方法
是每个线程用一个单独的Connection，因此这里没有写成单例模式
*/
/************************************************************************/
#pragma once

#include <comdef.h>
#include <list>
#include <set>
#include <string>
#include <boost\lexical_cast.hpp>

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class AdoRecordReader;
class CAdoController
{
public:

	CAdoController(void)
	{
		AfxOleInit();
	}
	~CAdoController();

	enum DatabaseProviderEnum
	{
		Access2000,
		ODBC,
		Oracle,
		SqlServer,
	};

	bool init();
	//连接数据库
	bool Connect(const std::string connectstring);
	bool Connect(DatabaseProviderEnum database, std::string dataSource,
		std::string ip, std::string username, std::string psw);

	//是否连接成功
	bool IsConnected()const
	{
		return (bool)m_pConnection->State;
	}

	//非SELECT命令，返回影响的行数
	int ExecuteNonQuery(const std::string&  command);

	//SELECT命令，返回封装的_RecordSetPtr
	AdoRecordReader ExecuteReader(const std::string& command);

	//TODO：存储过程，待实现
	//_RecordsetPtr ExecuteStoreProceduce(const std::string& storeProceduceName);

private:
	std::string connectStringBuilder(DatabaseProviderEnum database,
		std::string &ip, std::string dataSource,
		std::string username, std::string psw);

	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
};

/*
*    _RecordSetPtr相关函数封装，只读实现，不考虑ADO离线层
*/
class AdoRecordReader
{
public:
	explicit AdoRecordReader(_RecordsetPtr ptr) :
		m_recordSetPtr(ptr)
	{

	}
	//使其引用计数+1
	AdoRecordReader(const AdoRecordReader& lhs)
	{
		m_recordSetPtr = lhs.m_recordSetPtr->Clone(adLockOptimistic);
	}

	//减少引用计数
	~AdoRecordReader()
	{
		if (m_recordSetPtr->State)
		{
			m_recordSetPtr->Close();
			m_recordSetPtr.Release();
		}
	}

	//移动至下一条记录
	bool MoveNext()
	{
		HRESULT hr;
		hr = m_recordSetPtr->MoveNext();

		if (!SUCCEEDED(hr))
		{
			return false;
		}
		if (m_recordSetPtr->adoEOF)
		{
			return false;
		}
		return true;
	}
	//移动到第一条记录
	void MoveFirst()
	{
		m_recordSetPtr->MoveFirst();
	}
	//重载下标访问操作符（索引和列名）,注意这里下标访问也是只读的
	_variant_t operator[](const size_t index)const;
	_variant_t operator[](const std::string key)const;

	//强类型get函数，使用模板来进行强制类型转换
	template<typename T>
	T get(const size_t index)const
	{
		return boost::lexical_cast<T>(this->operator[](index));
	}
	template<typename T>
	T get(const std::string key)const
	{
		return boost::lexical_cast<T>(this->operator[](key));
	}

	//字符串特化
	template<>
	std::string get<std::string>(const size_t index)const
	{
		return std::string((char *)(_bstr_t)(this->operator[](index)));
	}

	template<>
	std::string get<std::string>(const std::string key)const
	{
		return std::string((char *)(_bstr_t)(this->operator[](key)));
	}

	//行数
	int RecordCount()
	{
		return m_recordSetPtr->RecordCount;
	}
	//列数
	int FieldCount()
	{
		return m_recordSetPtr->Fields->Count;
	}
private:
	_RecordsetPtr m_recordSetPtr;
};