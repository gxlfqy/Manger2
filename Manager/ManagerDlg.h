
// ManagerDlg.h : 头文件
//

#pragma once
#include "Manager.h"
#include "EasySize.h"
#include "MyMFCMenuButton.h"
#include "ManagerPersonData.h"
#include "ManagerADO.h"
#include "InitDlg.h"

//Position 
struct MyRect : public tagRECT
{
	MyRect() { }
	MyRect(const CRect & _s)
	{
		top = _s.top;
		bottom = _s.bottom;
		left = _s.left;
		right = _s.right;
	}
	void operator=(CRect _s)
	{
		top = _s.top;
		bottom = _s.bottom;
		left = _s.left;
		right = _s.right;
	}
};

//Info of control's position 
struct SCtrlInfo
{
	int nID;
	MyRect rect;
};

//ManagerDlg
class CManagerDlg : public CMyDialogEx
{
	DECLARE_SHORTKEY(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = NULL, bool isOnlyDialog = false);

	enum { IDD = IDD_MANAGER_DIALOG };

	enum STATE
	{
		modeAdd = 0,
		modeEdit
	};
	HICON m_hIcon;

protected:
	std::vector<SCtrlTDPosition> m_CheckerboardLayoutList;
	std::vector<SCtrlTDPosition> m_RegionLayoutList;
	CManagerPersonData m_personData;
	STATE m_managerDlgState;
	CMyMFCMenuButton m_ADEMenuBottomCtrl;
	CMyMFCMenuButton m_GLANDMenuBottomCtrl;
	bool m_isChange_noSave;							/* save singal */
	bool m_isOnlyDialog;							/* Only Dialog singal */

public:
	BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	BOOL HideCreate(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	CManagerPersonData GetManagerPersonData() {
		return m_personData;
	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	DECLARE_EASYSTATICCTRLCONNECT_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//当用户拖动最小化窗口时系统调用此函数取得光标显示。
	afx_msg HCURSOR OnQueryDragIcon(){
		return static_cast<HCURSOR>(m_hIcon);
	}
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSurgeryGland();
	afx_msg void OnBnClickedPathologyMfcmenubutton();
	//
	afx_msg void OnEnChangeCtcheckCtno() {
		OnlyAgreeNo(IDC_CTCHECK_CTNO);
	}
	afx_msg void OnEnChangePathologyNo() {
		OnlyAgreeNo(IDC_PATHOLOGY_NO);
	}
	afx_msg void OnEnChangeFollowUpRecordsCtNo() {
		OnlyAgreeNo(IDC_FOLLOW_UP_RECORDS_CT_NO);
	}
	afx_msg void OnEnChangeCtcheckScanningSlice() {
		OnlyAgreeDecimal(IDC_CTCHECK_SCANNING_SLICE);
	}
	afx_msg void OnEnKillfocusCtcheckScanningSlice() {
		DecimalCompletion(IDC_CTCHECK_SCANNING_SLICE);
	}
	afx_msg void OnEnChangePnrMajorAxis() {
		OnlyAgreeDecimal(IDC_PNR_MAJOR_AXIS);
	}
	afx_msg void OnEnKillfocusPnrMajorAxis() {
		DecimalCompletion(IDC_PNR_MAJOR_AXIS);
	}
	afx_msg void OnEnChangePnrMinorAxis() {
		OnlyAgreeDecimal(IDC_PNR_MINOR_AXIS);
	}
	afx_msg void OnEnKillfocusPnrMinorAxis() {
		DecimalCompletion(IDC_PNR_MINOR_AXIS);
	}
	afx_msg void OnEnChangePnrSize() {
		OnlyAgreeDecimal(IDC_PNR_SIZE);
	}
	afx_msg void OnEnKillfocusPnrSize() {
		DecimalCompletion(IDC_PNR_SIZE);
	}
	afx_msg void OnEnChangePathologySize() {
		OnlyAgreeDecimal(IDC_PATHOLOGY_SIZE);
	}
	afx_msg void OnEnKillfocusPathologySize() {
		DecimalCompletion(IDC_PATHOLOGY_SIZE);
	}
	afx_msg void OnEnChangePathologyMajorAxis() {
		OnlyAgreeDecimal(IDC_PATHOLOGY_MAJOR_AXIS);
	}
	afx_msg void OnEnKillfocusPathologyMajorAxis() {
		DecimalCompletion(IDC_PATHOLOGY_MAJOR_AXIS);
	}
	//
	virtual void OnOK() {
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg) {
		if (pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		SHORTKEY_PreTranslateMessage(pMsg);
		return CMyDialogEx::PreTranslateMessage(pMsg);
	}
	afx_msg void OnBnClickedSavedata();
	virtual void OnCancel();

protected:
	
	void InitGLANDMenuBottomCtrl();
	void InitADEMenuBottomCtrl();
	void SetManagerPersonDataToDialog(const ManagerData data);
	void SetManagerPersonDataToDialog();
	void ResetComboBox(const int nCtrlID, std::vector<CString> menuInfo);
	BOOL SetComboBoxText(const int nCtrlID, std::vector<CString> menuInfo, const CString data);
	void ResetFouceControl();
	BOOL UpdateManagerPersonData(const int nCtrlID);
	void UpdateDialogData(const int nCtrlID = NULL);
	void CloseWindow();
	friend class COnlyMangerDlg;

};

class COnlyMangerDlg
{
private:
	COnlyMangerDlg()
	{
	}
public:
	static CManagerDlg& GetManagerDlg()
	{
		static CManagerDlg dlg(NULL, true);
		return dlg;
	}
	static void InitOnlyMangerDlg()
	{
		CManagerDlg & dlg = GetManagerDlg();
		dlg.HideCreate(CManagerDlg::IDD);
	}
	static CManagerPersonData AddInfo(CWnd * pPDWnd = nullptr)
	{
		CManagerPersonData personData;
		return ModInfo(personData, pPDWnd);
	}
	static CManagerPersonData ModInfo(CManagerPersonData personData, CWnd * pPDWnd = nullptr)
	{
		CManagerDlg & dlg = GetManagerDlg();
		dlg.m_personData = personData;
		dlg.SetManagerPersonDataToDialog();
		dlg.m_isChange_noSave = false;
		dlg.ShowWindow(SW_SHOW);
		dlg.UpdateData(TRUE);
#ifdef _TOPMOST_
		dlg.TopMost();
#endif // _TOPMOST_
		CBlockDlg::Block(300);
#ifdef _TOPMOST_
		dlg.NoTopMost();
#endif // _TOPMOST_
		if (nullptr != pPDWnd)
			::SetWindowPos(pPDWnd->GetSafeHwnd(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		return dlg.GetManagerPersonData();
	}
};

//注意 类 CManagerDlg 设计时并没有考虑 使用一个类创建多个窗口，因此用此类创建多个窗口时可以出错
