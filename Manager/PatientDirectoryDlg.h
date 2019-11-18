#pragma once
#include "Manager.h"
#include "ManagerData.h"
#include "FindDlg.h"
#include "InitDlg.h"
#include "PatientDirectoryListCtrl.h"

// CPatientDirectoryDlg 对话框

class CPatientDirectoryDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CPatientDirectoryDlg)
	DECLARE_SHORTKEY(CPatientDirectoryDlg)
public:
	CPatientDirectoryDlg(CWnd* pParent = NULL);
	virtual ~CPatientDirectoryDlg();

	enum { IDD = IDD_PATIENT_DIRECTORY_DLG };
protected:
	void InitListCtrl();
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	//
	afx_msg void OnPatientdirectoryAddinfo();
	afx_msg void OnConditionQueryMenu();
	afx_msg void OnPartConditionQueryMenu();
	afx_msg void OnOutputDataid();
	afx_msg void OnLinkdatabase();
	afx_msg void OnShowalldata();
	//
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedUpdata();
	afx_msg void OnPaint() {
		PaintGreenBackground();
	}
	virtual void OnCancel() {
		CDialogEx::OnCancel();
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg) {
		SHORTKEY_PreTranslateMessage(pMsg);
		return CMyDialogEx::PreTranslateMessage(pMsg);
	}
public:
	CPatientDirectoryListCtrl m_listCtrl;
	CManagerData m_data;
	enum STATE
	{
		modeALL = 0,
		modeAtMHID,
		modeAtFindInfo,
		modeAtMHIDFindInfo
	};
	enum STATE m_state;
	std::vector<_FindInfo> m_DataBaseFindInfo;		/* 数据库查询条件信息 */
	std::vector<CString> m_DataBaseMHID;			/* 要显示的病历ID */

protected:
	void GetNewManagerDataAtDatabase();
	void SetManagerDataToDailog();

public:
	UINT_PTR Unfold();
	UINT_PTR Unfold(std::vector<CString> MHIDlist);
	UINT_PTR Unfold(std::vector<_FindInfo> selectList);
	UINT_PTR Unfold(std::vector<CString> MHIDlist, std::vector<_FindInfo> selectList);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
