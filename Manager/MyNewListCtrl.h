#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include <vector>

template<typename T>
class CMyListCtrl :
	public CListCtrl
{
public:
	struct listColsInfo
	{
		CString data;
		int nLong = 0;
		int ncoluIndex = 0;
		listColsInfo(){ }
		listColsInfo(CString str, int n)
		{
			data = str;
			nLong = n;
		}
	};
	std::vector<T> m_dataList;


};