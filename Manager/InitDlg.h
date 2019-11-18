#pragma once
#include "stdafx.h"
#include "Manager.h"

// CInitDlg 对话框

class CInitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitDlg)

public:
	CInitDlg(CWnd* pParent = NULL);
	virtual ~CInitDlg(){ }

// 对话框数据
	enum { IDD = IDD_INIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel() {
		m_nShowTimer = 2;
		CDialogEx::OnCancel();
	}
	virtual void OnOK() {
		m_nShowTimer = 2;
		CDialogEx::OnOK();
	}
protected:
	bool m_isOver;
	unsigned int m_nUpdateTime;
	CString m_szContent;
	bool m_isShow;
	int m_nShowTimer;
	friend class CBlockDlg;

public:
	afx_msg void OnNcPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void CloseWindow() {
		m_isOver = true;
	}
	virtual INT_PTR DoModal() {
		BOOL bRet;
		m_isOver = false;
		m_nUpdateTime = 500U;
		m_szContent = L"数据变更中...";
		m_isShow = FALSE;
		bRet = CDialogEx::DoModal();
		return bRet;
	}
};

class CBlockDlg
{
private:
	CBlockDlg() {
	}
public:
	static CInitDlg & GetInstance()
	{
		static CInitDlg dlg;
		return dlg;
	}
	static void Block(unsigned int time = 500U, CString content = L"数据变更中...", bool isShow = false)
	{
		CInitDlg & dlg = GetInstance();
		dlg.m_nUpdateTime = time;
		dlg.m_szContent = content;
		dlg.m_isShow = isShow;
		GetInstance().DoModal();
	}
	static void Block(CString content, unsigned int time = 500U)
	{
		CInitDlg & dlg = GetInstance();
		dlg.m_nUpdateTime = time;
		dlg.m_szContent = content;
		dlg.m_isShow = TRUE;
		GetInstance().DoModal();
	}
	static void Unblock()
	{
		CInitDlg & dlg = CBlockDlg::GetInstance();
		dlg.CloseWindow();
	}
};