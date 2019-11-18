#pragma once
#include "Manager.h"
#include "ManagerADO.h"
#include "afxlinkctrl.h"
#include "afxcmn.h"

//数据库连接参数输入对话框
class CInputDataBaseInfoDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CInputDataBaseInfoDlg)
	
public:
	CInputDataBaseInfoDlg(CWnd* pParent = NULL);
	virtual ~CInputDataBaseInfoDlg() {
	}

	enum { IDD = IDD_INPUTDATABASEINFO_DLG };
	
	enum EnDBState {
		Local = 0, Remote
	};
	static const wchar_t * m_caption[2];
	static const wchar_t * m_sysLinkCaption[2];

protected:
	SDBConnectPragma m_data;
	CString & m_szName;
	CString & m_szIP;
	CString & m_szUserName;
	CString & m_szPass;
	EnDBState m_enState;

	virtual void DoDataExchange(CDataExchange* pDX);
	void MoveNextContorl();

public:
	UINT_PTR DoModal(EnDBState o = Remote) {
		m_enState = o;
		return CDialogEx::DoModal();
	}
	SDBConnectPragma GetDataBaseInfo() const {
		return m_data;
	}

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDatabaselink();
	virtual void OnOK() {
		OnBnClickedDatabaselink();
	}
	virtual void OnCancel() {
		CDialogEx::OnCancel();
	}
	afx_msg void OnPaint() {
		PaintGreenBackground();
	}
	bool IsValidIP(CString szIP);
public:
	afx_msg void OnNMClickSyslink(NMHDR *pNMHDR, LRESULT *pResult);
	CLinkCtrl m_LinkCtrl;
};
