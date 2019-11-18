#pragma once
#include "Manager.h"
#include "ManagerData.h"
#include "MyMFCMenuButton.h"
#include "afxcmn.h"
#include "FindListCtrl.h"

// CFindDlg 对话框

class CFindDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CFindDlg)

public:
	CFindDlg(CWnd* pParent = NULL);   // 标准构造函数
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
	CFindListCtrl m_FoundListCtrl;					/* 筛选条件显示控件 */
	CMyMFCMenuButton m_OptionsMenuCtrl;				/* 筛选条件选择控件 */
	CMyMFCMenuButton m_MFCMenu2Ctrl;				/* 选项 MFCMenuButton 控件 */

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
