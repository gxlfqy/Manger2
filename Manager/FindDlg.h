#pragma once
#include "Manager.h"
#include "ManagerData.h"
#include "MyMFCMenuButton.h"
#include "afxcmn.h"
#include "FindListCtrl.h"

// CFindDlg �Ի���

class CFindDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CFindDlg)

public:
	CFindDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindDlg();

	enum { IDD = IDD_FOUND_DLG };

public:
	std::vector<_FindInfo> GetFindInfo() 
	{
		std::vector<_FindInfo> temp = m_FoundListCtrl.GetListInfo();
		return temp;
	}

protected:
	std::vector<tag_ef_connect> m_ControlInfo;

	void InitFoundList();
	void InitOptionsMenu();

protected:
	CFindListCtrl m_FoundListCtrl;					/* ɸѡ������ʾ�ؼ� */
	CMyMFCMenuButton m_OptionsMenuCtrl;				/* ɸѡ����ѡ��ؼ� */
	CMyMFCMenuButton m_MFCMenu2Ctrl;				/* ѡ�� MFCMenuButton �ؼ� */

	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcmenu1();
	afx_msg void OnBnClickedMfcmenu2();
	afx_msg void OnPaint()
	{
		PaintGreenBackground();
	}
	afx_msg void OnEnChangeBimEdit()
	{
		OnlyAgreeNo(IDC_BIM_EDIT);
	}
	afx_msg void OnEnChangeDecimalEdit()
	{
		OnlyAgreeDecimal(IDC_DECIMAL_EDIT);
	}
	afx_msg void OnEnKillfocusDecimalEdit()
	{
		DecimalCompletion(IDC_DECIMAL_EDIT);
	}
	afx_msg void OnBnClickedAddoption();
	afx_msg void OnBnClickedOk() 
	{
		CDialogEx::OnOK();
	}
	virtual void OnOK() 
	{
	}
};
