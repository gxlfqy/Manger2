/************************************************************************/
/* INSTRUCTION: ��װADO���ݿ���ز���
DETAILS: ֻ����MFC��ʹ�ã����ʹ����MFC���ַ�����
���Խ�������ȷ�װ�����Ǻܶ�ѡ��(��洢����)�������ˣ��ʺ�С����Ŀʹ�á�
NOTE: ADO���ݿ���ʲ������̰߳�ȫ�ģ�����̹߳���һ��Connection��Ҫ�߳�ͬ�����Ƽ�����
��ÿ���߳���һ��������Connection���������û��д�ɵ���ģʽ
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
	//�������ݿ�
	bool Connect(const std::string connectstring);
	bool Connect(DatabaseProviderEnum database, std::string dataSource,
		std::string ip, std::string username, std::string psw);

	//�Ƿ����ӳɹ�
	bool IsConnected()const
	{
		return (bool)m_pConnection->State;
	}

	//��SELECT�������Ӱ�������
	int ExecuteNonQuery(const std::string&  command);

	//SELECT������ط�װ��_RecordSetPtr
	AdoRecordReader ExecuteReader(const std::string& command);

	//TODO���洢���̣���ʵ��
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
*    _RecordSetPtr��غ�����װ��ֻ��ʵ�֣�������ADO���߲�
*/
class AdoRecordReader
{
public:
	explicit AdoRecordReader(_RecordsetPtr ptr) :
		m_recordSetPtr(ptr)
	{

	}
	//ʹ�����ü���+1
	AdoRecordReader(const AdoRecordReader& lhs)
	{
		m_recordSetPtr = lhs.m_recordSetPtr->Clone(adLockOptimistic);
	}

	//�������ü���
	~AdoRecordReader()
	{
		if (m_recordSetPtr->State)
		{
			m_recordSetPtr->Close();
			m_recordSetPtr.Release();
		}
	}

	//�ƶ�����һ����¼
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
	//�ƶ�����һ����¼
	void MoveFirst()
	{
		m_recordSetPtr->MoveFirst();
	}
	//�����±���ʲ�������������������,ע�������±����Ҳ��ֻ����
	_variant_t operator[](const size_t index)const;
	_variant_t operator[](const std::string key)const;

	//ǿ����get������ʹ��ģ��������ǿ������ת��
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

	//�ַ����ػ�
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

	//����
	int RecordCount()
	{
		return m_recordSetPtr->RecordCount;
	}
	//����
	int FieldCount()
	{
		return m_recordSetPtr->Fields->Count;
	}
private:
	_RecordsetPtr m_recordSetPtr;
};