#pragma once
#include "stdafx.h"
#include "ManagerData.h"
#include "afxwin.h"

// CDataIDDlg �Ի���

class CDataIDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataIDDlg)

public:
	CDataIDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataIDDlg();

// �Ի�������
	enum { IDD = IDD_DATAID_DLG };
	std::vector<tag_ef_connect> __EF__StaticCtrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_listCtrl;
	afx_msg void OnBnClickedOuttxt();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	virtual void OnOK();
	afx_msg void OnPaint();
};