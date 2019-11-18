
// ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerDlg.h"
#include "InitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CManagerDlg 对话框

CREATE_EASYSTATICCTRLCONNECT

CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/, bool isOnlyDialog /*=flase*/)
	: CMyDialogEx(CManagerDlg::IDD, pParent)
	, m_isChange_noSave(false)
	, m_isOnlyDialog(isOnlyDialog)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//Create the ManagerDlg
BOOL CManagerDlg::Create(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
{
	BOOL ret;
	if (pParentWnd != NULL)
		ret = CDialogEx::Create(nIDTemplate, pParentWnd);
	else
		ret = CDialogEx::Create(nIDTemplate);
	ShowWindow(SW_SHOW);
	return ret;
}

//Create the ManagerDlg and hide the dailog
BOOL CManagerDlg::HideCreate(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
{
	BOOL ret;
	if (pParentWnd != NULL)
		ret = CDialogEx::Create(nIDTemplate, pParentWnd);
	else
		ret = CDialogEx::Create(nIDTemplate);
	/*ShowWindow(SW_HIDE);*/
	return ret;
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATHOLOGY_ADENOCARCINOMA, m_ADEMenuBottomCtrl);
	DDX_Control(pDX, IDC_SURGERY_GLAND, m_GLANDMenuBottomCtrl);
}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_HOTKEY()
	//MFCMenuButton
	ON_BN_CLICKED(IDC_PATHOLOGY_ADENOCARCINOMA, &CManagerDlg::OnBnClickedPathologyMfcmenubutton)
	ON_BN_CLICKED(IDC_SURGERY_GLAND, &CManagerDlg::OnBnClickedSurgeryGland)
	//Edit Input No
	ON_EN_CHANGE(IDC_CTCHECK_CTNO, &CManagerDlg::OnEnChangeCtcheckCtno)
	ON_EN_CHANGE(IDC_PATHOLOGY_NO, &CManagerDlg::OnEnChangePathologyNo)
	ON_EN_CHANGE(IDC_FOLLOW_UP_RECORDS_CT_NO, &CManagerDlg::OnEnChangeFollowUpRecordsCtNo)
	//DateTimeChange
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SURGERY_DATE, &CManagerDlg::OnDtnDatetimechange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CTCHECK_CTDATE, &CManagerDlg::OnDtnDatetimechange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_PATHOLOGY_DATE, &CManagerDlg::OnDtnDatetimechange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_FOLLOW_UP_RECORDS_DATE, &CManagerDlg::OnDtnDatetimechange)
	//Edit Decimal
	ON_EN_CHANGE(IDC_CTCHECK_SCANNING_SLICE, &CManagerDlg::OnEnChangeCtcheckScanningSlice)
	ON_EN_KILLFOCUS(IDC_CTCHECK_SCANNING_SLICE, &CManagerDlg::OnEnKillfocusCtcheckScanningSlice)
	ON_EN_CHANGE(IDC_PNR_MAJOR_AXIS, &CManagerDlg::OnEnChangePnrMajorAxis)
	ON_EN_KILLFOCUS(IDC_PNR_MAJOR_AXIS, &CManagerDlg::OnEnKillfocusPnrMajorAxis)
	ON_EN_CHANGE(IDC_PNR_MINOR_AXIS, &CManagerDlg::OnEnChangePnrMinorAxis)
	ON_EN_KILLFOCUS(IDC_PNR_MINOR_AXIS, &CManagerDlg::OnEnKillfocusPnrMinorAxis)
	ON_EN_CHANGE(IDC_PNR_SIZE, &CManagerDlg::OnEnChangePnrSize)
	ON_EN_KILLFOCUS(IDC_PNR_SIZE, &CManagerDlg::OnEnKillfocusPnrSize)
	ON_EN_CHANGE(IDC_PATHOLOGY_SIZE, &CManagerDlg::OnEnChangePathologySize)
	ON_EN_KILLFOCUS(IDC_PATHOLOGY_SIZE, &CManagerDlg::OnEnKillfocusPathologySize)
	ON_EN_CHANGE(IDC_PATHOLOGY_MAJOR_AXIS, &CManagerDlg::OnEnChangePathologyMajorAxis)
	ON_EN_KILLFOCUS(IDC_PATHOLOGY_MAJOR_AXIS, &CManagerDlg::OnEnKillfocusPathologyMajorAxis)
	//
	ON_BN_CLICKED(IDC_SAVEDATA, &CManagerDlg::OnBnClickedSavedata)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_EASYSTATICCTRLCONNECT_MAP(CManagerDlg)
	//Basic Info Static 
	ESCC_CONNECT(IDC_NAME_STATIC, IDC_BASICINFO_NAME, ControlType::Edit, ES_LIMIT256)
	ESCC_CONNECT(IDC_SEX_STATIC, IDC_BASICINFO_SEX,  ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_AGE_STATIC, IDC_BASICINFO_AGE, ControlType::Edit, (ES_NUMBER | ES_LIMIT16))
	ESCC_CONNECT(IDC_SMOKEYEAR_STATIC, IDC_BASICINFO_SMOKEYEAR,  ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_SMOKENUM_STATIC, IDC_BASICINFO_SMOKENUM, ControlType::Edit, (ES_NUMBER | ES_LIMIT64))
	ESCC_CONNECT(IDC_SYMPTOM_STATIC, IDC_BASICINFO_SYMPTOM, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_COUGH_STATIC, IDC_BASICINFO_COUGH, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_HEMOPTYSIS_STATIC, IDC_BASICINFO_HEMOPTYSIS, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_FHOC_STATIC, IDC_BASICINFO_FHOC, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_FHOLC_STATIC, IDC_BASICINFO_FHOLC, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_OMTH_STATIC, IDC_BASICINFO_OMTH, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_EMPHYSEMA1_STATIC, IDC_BASICINFO_EMPHYSEMA1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_TUBERCULOSIS_STATIC, IDC_BASICINFO_TUBERCULOSIS, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_SILICOSIS_STATIC, IDC_BASICINFO_SILICOSIS, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_HBP_STATIC, IDC_BASICINFO_HBP, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CARDIOPATHY_STATIC, IDC_BASICINFO_CARDIOPATHY, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CEREBROVASCULAR_DISEASE_STATIC, IDC_BASICINFO_CEREBROVASCULAR_DISEASE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_DIABETES_STATIC, IDC_BASICINFO_DIABETES, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_NEPHROPATHY_STATIC, IDC_BASICINFO_NEPHROPATHY, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_OSMH_STATIC, IDC_BASICINFO_OSMH, ControlType::Edit, ES_LIMIT256)
	//CT check Static
	ESCC_CONNECT(IDC_CTNO_STATIC, IDC_CTCHECK_CTNO, ControlType::Edit, (ES_ONLYINPUTNO | ES_LIMIT64))
	ESCC_CONNECT(IDC_CTDATE_STATIC, IDC_CTCHECK_CTDATE, ControlType::DateTimePicker, 0)
	ESCC_CONNECT(IDC_CTRAISE_STATIC, IDC_CTCHECK_CTRAISE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_MACHINENAME_STATIC, IDC_CTCHECK_MACHINENAME, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_SCANNING_SLICE_STATIC, IDC_CTCHECK_SCANNING_SLICE, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	//PNR Static
	ESCC_CONNECT(IDC_MAJOR_AXIS_STATIC, IDC_PNR_MAJOR_AXIS, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	ESCC_CONNECT(IDC_MINOR_AXIS_STATIC, IDC_PNR_MINOR_AXIS, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	ESCC_CONNECT(IDC_SIZE_STATIC, IDC_PNR_SIZE, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	ESCC_CONNECT(IDC_DENSITY_STATIC, IDC_PNR_DENSITY, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_SHAPE_STATIC, IDC_PNR_SHAPE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PART_STATIC, IDC_PNR_PART, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PERIACINAR_EMPHYSEMA_STATIC, IDC_PNR_PERIACINAR_EMPHYSEMA, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_MULTIPLE_NODES_STATIC, IDC_PNR_MULTIPLE_NODES, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PLEURAL_CONTACT_STATIC, IDC_PNR_PLEURAL_CONTACT, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_RAG_STATIC, IDC_PNR_RAG, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_LEAFLET_STATIC, IDC_PNR_LEAFLET, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PRE_STATIC, IDC_PNR_PRE, ControlType::Edit, ES_LIMIT256)
	//OLD Static 
	ESCC_CONNECT(IDC_EMPHYSEMA2_STATIC, IDC_OLD_EMPHYSEMA2, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IPF_STATIC, IDC_OLD_IPF, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_BRONCHIECTASIA_STATIC, IDC_OLD_BRONCHIECTASIA, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_OPTUBE_STATIC, IDC_OLD_OPTUBE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CAOFTHEP_STATIC, IDC_OLD_CAOFTHEP, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PLEURAL_EFFUSION_STATIC, IDC_OLD_PLEURAL_EFFUSION, ControlType::ComboBox, 0)
	//EXCHECK Static 
	ESCC_CONNECT(IDC_BTMWE_STATIC, IDC_EXCHECK_BTMWE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PFE_STATIC, IDC_EXCHECK_PFE, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_EX1_STATIC, IDC_EXCHECK_EX1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CEA1_STATIC, IDC_EXCHECK_CEA1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CA1991_STATIC, IDC_EXCHECK_CA1991, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_CYFRA21_1_1_STATIC, IDC_EXCHECK_CYFRA21_1_1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_NSE_1_STATIC, IDC_EXCHECK_NSE_1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PET_CT_1_STATIC, IDC_EXCHECK_PET_CT_1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_EX2_STATIC, IDC_EXCHECK_EX2, ControlType::Edit, ES_LIMIT256)
	ESCC_CONNECT(IDC_LYMPH_GLAND_STATIC, IDC_EXCHECK_LYMPH_GLAND, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_TRANSFER_STATIC, IDC_EXCHECK_TRANSFER, ControlType::ComboBox, 0)
	//SURGERY Static
	ESCC_CONNECT(IDC_SURGERY_DATE_STATIC, IDC_SURGERY_DATE, ControlType::DateTimePicker, 0)
	ESCC_CONNECT(IDC_SURGERY_TIME_STATIC, IDC_SURGERY_TIME, ControlType::Edit, (ES_NUMBER | ES_LIMIT16))
	ESCC_CONNECT(IDC_SURGERY_NAME_STATIC, IDC_SURGERY_NAME, ControlType::ComboBox, 0)
	ESCC_CONNECT_MFCMENU(IDC_LYMPH_GLAND_2_STATIC, IDC_SURGERY_GLAND, ControlType::MFCMenuButtonControl, m_GLANDMenuBottomCtrl, 0)
	//PATHOLOGY Static
	ESCC_CONNECT(IDC_PATHOLOGY_NO_STATIC, IDC_PATHOLOGY_NO, ControlType::Edit, (ES_ONLYINPUTNO | ES_LIMIT64))
	ESCC_CONNECT(IDC_PATHOLOGY_DATE_STATIC, IDC_PATHOLOGY_DATE, ControlType::DateTimePicker, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_PART_STATIC, IDC_PATHOLOGY_PART, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_SIZE_STATIC, IDC_PATHOLOGY_SIZE, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	ESCC_CONNECT(IDC_PATHOLOGY_MAJOR_AXIS_STATIC, IDC_PATHOLOGY_MAJOR_AXIS, ControlType::Edit, (ES_ONLYINPUTDECIMAL | ES_LIMIT64))
	ESCC_CONNECT(IDC_PATHOLOGY_TYPES_STATIC, IDC_PATHOLOGY_TYPES, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_TDOP_STATIC, IDC_PATHOLOGY_TDOP, ControlType::ComboBox, 0)
	//
	ESCC_CONNECT(IDC_PATHOLOGY_BIM_STATIC, IDC_PATHOLOGY_BIM, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_VCE_STATIC, IDC_PATHOLOGY_VCE, ControlType::ComboBox, 0)
	ESCC_CONNECT_MFCMENU(IDC_PATHOLOGY_ADENOCARCINOMA_STATIC, IDC_PATHOLOGY_ADENOCARCINOMA, ControlType::MFCMenuButtonControl, m_ADEMenuBottomCtrl, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_VLD_STATIC, IDC_PATHOLOGY_VLD, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_LIGAMENT_STATIC, IDC_PATHOLOGY_LIGAMENT, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_NERVE_STATIC, IDC_PATHOLOGY_NERVE, ControlType::ComboBox, 0)
	//
	ESCC_CONNECT(IDC_PATHOLOGY_EMPHYSEMA_STATIC, IDC_PATHOLOGY_EMPHYSEMA, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_PIF_STATIC, IDC_PATHOLOGY_PIF, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_LNM_STATIC, IDC_PATHOLOGY_LNM, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_INFLAMMATION_STATIC, IDC_PATHOLOGY_INFLAMMATION, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_PATHOLOGY_INFO1_STATIC, IDC_PATHOLOGY_INFO1, ControlType::Edit, ES_LIMIT256)
	ESCC_CONNECT(IDC_PATHOLOGY_PATHOLOGICAL_STAGE_STATIC, IDC_PATHOLOGY_PATHOLOGICAL_STAGE, ControlType::Edit, ES_LIMIT256)
	//IMMUNOHISTOCHEMISTRY Static
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_EGFR_STATIC, IDC_IMMUNOHISTOCHEMISTRY_EGFR, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_CK7_STATIC, IDC_IMMUNOHISTOCHEMISTRY_CK7, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_TTF_1_STATIC, IDC_IMMUNOHISTOCHEMISTRY_TTF_1, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_CEA_STATIC, IDC_IMMUNOHISTOCHEMISTRY_CEA, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_VIM_STATIC, IDC_IMMUNOHISTOCHEMISTRY_VIM, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_CD34_STATIC, IDC_IMMUNOHISTOCHEMISTRY_CD34, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_KI67_STATIC, IDC_IMMUNOHISTOCHEMISTRY_KI67, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_NASPIN_A_STATIC, IDC_IMMUNOHISTOCHEMISTRY_NASPIN_A, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_IMMUNOHISTOCHEMISTRY_P63_STATIC, IDC_IMMUNOHISTOCHEMISTRY_P63, ControlType::ComboBox, 0)
	//GENETIC_TESTING Static
	ESCC_CONNECT(IDC_GENETIC_TESTING_1_STATIC, IDC_GENETIC_TESTING, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_GENETIC_TESTING_BML4_ALK_STATIC, IDC_GENETIC_TESTING_BML4_ALK, ControlType::ComboBox, 0)
	//FOLLOW_UP_RECORDS Static
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_CT_NO_STATIC, IDC_FOLLOW_UP_RECORDS_CT_NO, ControlType::Edit, (ES_ONLYINPUTNO | ES_LIMIT64))
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_DATE_STATIC, IDC_FOLLOW_UP_RECORDS_DATE, ControlType::DateTimePicker, 0)
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_TIME_STATIC, IDC_FOLLOW_UP_RECORDS_TIME, ControlType::Edit, (ES_NUMBER | ES_LIMIT16))
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_SITUATION_STATIC, IDC_FOLLOW_UP_RECORDS_SITUATION, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_AFTERTREATMENT_STATIC, IDC_FOLLOW_UP_RECORDS_AFTERTREATMENT, ControlType::ComboBox, 0)
	ESCC_CONNECT(IDC_FOLLOW_UP_RECORDS_CHEMOTHERAPY_STATIC, IDC_FOLLOW_UP_RECORDS_CHEMOTHERAPY, ControlType::ComboBox, 0)
	//MHID Static
	ESCC_CONNECT(IDC_BASICINFO_MHID_STATIC, IDC_BASICINFO_MHID, ControlType::Edit, (ES_NUMBER | ES_LIMIT64))
END_EASYSTATICCTRLCONNECT_MAP

BEGIN_SHORTKEYINFO_MAP(CManagerDlg)
	ON_SHORTKEY(VK_CONTROL, SHORTKEY_LETTER('S'), &CManagerDlg::OnBnClickedSavedata)
	ON_SHORTKEY(VK_CONTROL, VK_BACK, &CManagerDlg::ResetFouceControl)
END_SHORTKEYINFO_MAP

// CManagerDlg 消息处理程序

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	//Init the MFCButton controls 
	InitADEMenuBottomCtrl();
	InitGLANDMenuBottomCtrl();
	//connect the static and control
	CONNECTSTATICCTRL
	//Ban the Edit controls Input Method
	static const int BIMIDs[] = {
		IDC_CTCHECK_CTNO, IDC_PATHOLOGY_NO, IDC_FOLLOW_UP_RECORDS_CT_NO,
		IDC_CTCHECK_SCANNING_SLICE, IDC_PNR_MAJOR_AXIS, IDC_PNR_MINOR_AXIS,
		IDC_PNR_SIZE, IDC_PATHOLOGY_SIZE, IDC_PATHOLOGY_MAJOR_AXIS
	};
	for (int term : BIMIDs)
		BanInputMethod(term);
	//Reset the PersonData
	m_personData.Reset();
	SetManagerPersonDataToDialog();
	//Get Ctrl TD-Position
	static const int GroupCtrlIDs[] = {
		IDC_BASEINFO_STATIC, IDC_CTCHECK_STATIC, IDC_PNR_STATIC,
		IDC_OLD_STATIC, IDC_CHEST_EXAMINATION_STATIC, IDC_SURGERY_STATIC,
		IDC_PATHOLOGY_RESULTS_STATIC, IDC_PATHOLOGY_ISOI_STATIC,
		IDC_PATHOLOGY_FOUNDIFNO_STATIC, IDC_IMMUNOHISTOCHEMISTRY_STATIC,
		IDC_GENETIC_TESTING_STATIC, IDC_FOLLOW_UP_RECORDS_STATIC, NULL
	};
	m_CheckerboardLayoutList = GetCtrlTDPosition(GroupCtrlIDs, TRUE);
	m_RegionLayoutList = GetCtrlTDPosition(GroupCtrlIDs, FALSE);
	//Reset the save singal
	m_isChange_noSave = false;
	return TRUE;
}

void CManagerDlg::OnPaint()
{
	PaintGreenBackground();
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	static POINT oldWH = { 0L, 0L };
	static const int GroupCtrlIDs[] = {
		IDC_BASEINFO_STATIC, IDC_CTCHECK_STATIC, IDC_PNR_STATIC,
		IDC_OLD_STATIC, IDC_CHEST_EXAMINATION_STATIC, IDC_SURGERY_STATIC,
		IDC_PATHOLOGY_RESULTS_STATIC, IDC_PATHOLOGY_ISOI_STATIC,
		IDC_PATHOLOGY_FOUNDIFNO_STATIC, IDC_IMMUNOHISTOCHEMISTRY_STATIC,
		IDC_GENETIC_TESTING_STATIC, IDC_FOLLOW_UP_RECORDS_STATIC, NULL
	};
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		/*RestoreGroup();*/
		CheckerboardLayout(m_CheckerboardLayoutList);
		RegionLayout(oldWH, m_RegionLayoutList);
		UPDATECONTROLPOSITION;	//Update the position of the static 
		GetWindowWH(oldWH);
	}
}

void CManagerDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);
	static int nCounter = 0;
	static int width = 0, height = 0;
	if (nCounter == 0)
	{
		width = pRect->right - pRect->left;
		height = pRect->bottom - pRect->top;
		nCounter++;
	}
	EASYSIZE_MINSIZE(width, height, fwSide, pRect);
}

BOOL CManagerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//listen the Edit and ComboBox control 
	UINT_PTR id = 0;
	if (HIWORD(wParam) & EN_CHANGE)
	{
		id = LOWORD(wParam);
		if (id != 0)
			UpdateDialogData(id);
	}
	if (HIWORD(wParam) & CBN_EDITCHANGE)
	{
		id = LOWORD(wParam);
		if (id != 0)
			UpdateDialogData(id);
	}
	return CDialogEx::OnCommand(wParam, lParam);
}

//Update the personData of the DatePicker control 
void CManagerDlg::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
	UpdateDialogData(pNMHDR->idFrom);
}

//MFCButton of GLAND 
void CManagerDlg::OnBnClickedSurgeryGland()
{
	if (m_GLANDMenuBottomCtrl.m_nMenuResult != 0)
	{
		m_isChange_noSave = true;
		CString temp = m_GLANDMenuBottomCtrl.GetTreeString(m_GLANDMenuBottomCtrl.m_nMenuResult, L"-");
		m_GLANDMenuBottomCtrl.SetWindowText(temp);
		UpdateDialogData(IDC_SURGERY_GLAND);
	}
}

//MFCButton of ADE
void CManagerDlg::OnBnClickedPathologyMfcmenubutton()
{
	if (m_ADEMenuBottomCtrl.m_nMenuResult != 0)
	{
		m_isChange_noSave = true;
		CString temp = m_ADEMenuBottomCtrl.GetTreeString(m_ADEMenuBottomCtrl.m_nMenuResult, L"-");
		SetDlgItemText(IDC_MFCMENUINFO, temp);
		UpdateDialogData(IDC_PATHOLOGY_ADENOCARCINOMA);
	}
}

//Sent the PersonData to the database
void CManagerDlg::OnBnClickedSavedata()
{
	CString temp;
	GetDlgItem(IDC_BASICINFO_MHID)->GetWindowText(temp);
	if (L"" == temp)
	{
		MessageBox(L"病历ID不得为空", L"消息", MB_TOPMOST);
		return;
	}
	if (modeAdd == m_managerDlgState && CManagerStringADO::IsHava(temp))
	{
		if (MessageBox(L"数据库中已存在该病历ID的数据，是否将其覆盖？", L"消息", MB_TOPMOST | MB_YESNO) == IDNO)
			return;
	}
	m_isChange_noSave = !CManagerStringADO::SentManagerPersonDataToDataBase(m_personData);
	UpdateDialogData();
	if (m_isChange_noSave)
		MessageBox(L"数据保存失败", L"消息", MB_TOPMOST);
}

void CManagerDlg::OnCancel()
{
	if (false == m_isChange_noSave)
	{
		CloseWindow();
		return;
	}
	switch (MessageBox(L"你所输入的数据还没有保存，是否进行保存", L"消息",MB_YESNOCANCEL | MB_TOPMOST))
	{
	case IDYES:
		OnBnClickedSavedata();
		m_isChange_noSave ? MessageBox(L"保存失败!", L"消息", MB_TOPMOST) : CloseWindow();
		break;
	case IDNO:
		CloseWindow();
		break;
	}
}

void CManagerDlg::InitGLANDMenuBottomCtrl()
{
	EC_CDynamicMenu_InitDynamicMenu(m_GLANDMenuBottomCtrl);
	EC_CDynamicMenu_SetMenuInfo(0100, "活检");
	EC_CDynamicMenu_SetMenuInfo(0101, "阳性");
	EC_CDynamicMenu_SetMenuInfo(0102, "阴性");
	EC_CDynamicMenu_SetMenuInfo(0200, "清扫");
	EC_CDynamicMenu_SetMenuInfo(0201, "阳性");
	EC_CDynamicMenu_SetMenuInfo(0202, "阴性");
	EC_CDynamicMenu_BuildDynamicMenu;
}

void CManagerDlg::InitADEMenuBottomCtrl()
{
	EC_CDynamicMenu_InitDynamicMenu(m_ADEMenuBottomCtrl);
	EC_CDynamicMenu_SetMenuInfo(010000, "浸润前病变");
	EC_CDynamicMenu_SetMenuInfo(010100, "非典型腺瘤样增生");
	EC_CDynamicMenu_SetMenuInfo(010200, "原位腺癌");
	EC_CDynamicMenu_SetMenuInfo(010201, "非黏液性");
	EC_CDynamicMenu_SetMenuInfo(010202, "黏液性");
	EC_CDynamicMenu_SetMenuInfo(010203, "混合性");
	EC_CDynamicMenu_SetMenuInfo(020000, "微浸润腺癌");
	EC_CDynamicMenu_SetMenuInfo(020100, "非黏液性");
	EC_CDynamicMenu_SetMenuInfo(020200, "黏液性");
	EC_CDynamicMenu_SetMenuInfo(020300, "混合性");
	EC_CDynamicMenu_SetMenuInfo(030000, "浸润性腺癌");
	EC_CDynamicMenu_SetMenuInfo(030100, "伏壁生长为主");
	EC_CDynamicMenu_SetMenuInfo(030200, "腺泡为主");
	EC_CDynamicMenu_SetMenuInfo(030300, "乳头状");
	EC_CDynamicMenu_SetMenuInfo(030400, "微小乳头为主");
	EC_CDynamicMenu_SetMenuInfo(030500, "实体为主伴粘液蛋白分泌");
	EC_CDynamicMenu_SetMenuInfo(040000, "浸润性变异");
	EC_CDynamicMenu_SetMenuInfo(040100, "黏液性");
	EC_CDynamicMenu_SetMenuInfo(040200, "胶质样");
	EC_CDynamicMenu_SetMenuInfo(040300, "胎儿型");
	EC_CDynamicMenu_SetMenuInfo(040400, "肠腺癌");
	EC_CDynamicMenu_BuildDynamicMenu;
}

void CManagerDlg::SetManagerPersonDataToDialog(const ManagerData data)
{
	tag_ef_connect controlInfo;
	CString content;
	CDateTimeCtrl* pDateTime;
	CTime theTime;
	int nYear, nMonth, nDate;
	EasyStaticCtrlConnect::GetInstance().GetData(data.IDName, controlInfo);
	switch (data.ctrlName)
	{
	case ControlType::Edit:
		SetDlgItemText(data.ctrlID, data.data);
		break;
	case ControlType::ComboBox:
		SetComboBoxText(data.ctrlID, controlInfo.MenuInfo, data.data);
		break;
	// when the data fo Date is L"" means it's CurrentTime
	case ControlType::DateTimePicker:
		if (data.data == L"")
		{
			theTime = CTime::GetCurrentTime();
			pDateTime = (CDateTimeCtrl*)GetDlgItem(data.ctrlID);
			pDateTime->SetTime(&theTime);
			pDateTime->GetWindowText(content);
			m_personData.SetData(data.ctrlID, content);
		}
		else
		{
			swscanf_s(data.data, L"%d%*c%d%*c%d", &nYear, &nMonth, &nDate);
			CTime t(nYear, nMonth, nDate, 0, 0, 0);
			pDateTime = (CDateTimeCtrl*)GetDlgItem(data.ctrlID);
			pDateTime->SetTime(&t);
		}
		break;
	case ControlType::MFCMenuButtonControl:
		if (data.ctrlID == IDC_SURGERY_GLAND)
			SetDlgItemText(data.ctrlID, data.data);
		else if (data.ctrlID == IDC_PATHOLOGY_ADENOCARCINOMA)
			SetDlgItemText(IDC_MFCMENUINFO, data.data);
		break;
	}
}

//Set all the data of m_personData to dialog 
void CManagerDlg::SetManagerPersonDataToDialog()
{
	using namespace std;
	vector<DataBaseTable>::iterator table;
	vector<ManagerData>::iterator list;
	vector<DataBaseTable> data = m_personData.GetAllData();
	m_managerDlgState = m_personData.isEmpty() ? modeAdd : modeEdit;
	for (table = data.begin(); table != data.end(); ++table)
	for (list = table->tableData.begin(); list != table->tableData.end(); ++list)
		SetManagerPersonDataToDialog(*list);
	if (modeEdit == m_managerDlgState)
		((CEdit*)GetDlgItem(IDC_BASICINFO_MHID))->SetReadOnly(TRUE);
	else
		((CEdit*)GetDlgItem(IDC_BASICINFO_MHID))->SetReadOnly(FALSE);
}

void CManagerDlg::ResetComboBox(const int nCtrlID, std::vector<CString> menuInfo)
{
	CComboBox * pComboBox = (CComboBox*)GetDlgItem(nCtrlID);
	std::vector<CString>::iterator it;
	if (nullptr == pComboBox)
		return;
	pComboBox->ResetContent();
	for (it = menuInfo.begin(); it != menuInfo.end(); ++it)
		pComboBox->AddString(*it);
}

//If fail return FALSE 
BOOL CManagerDlg::SetComboBoxText(int nCtrlID, std::vector<CString> menuInfo, const CString data)
{
	CComboBox * pComboBox = (CComboBox*)GetDlgItem(nCtrlID);
	std::vector<CString>::iterator it;
	int nIndex = 0;
	if (L"" == data)
	{
		ResetComboBox(nCtrlID, menuInfo);
		return TRUE;
	}
	for (it = menuInfo.begin(); it != menuInfo.end(); ++it, ++nIndex)
	{
		if (data == *it)
		{
			pComboBox->SetCurSel(nIndex);
			return TRUE;
		}
	}
	return FALSE;
}

//When reseting the control, the personData was also reseted.
void CManagerDlg::ResetFouceControl()
{
	HWND hWnd;
	CWnd * pWnd;
	LONG id;
	tag_ef_connect controlInfo;
	BOOL bRet;
	pWnd = GetFocus();
	if (nullptr == pWnd)
		goto End;
	hWnd = pWnd->m_hWnd;
	if (nullptr == hWnd)
		goto End;
	id = GetWindowLong(hWnd, GWL_ID);
	if (IDC_MFCMENUINFO == id)
	{
		SetDlgItemText(id, L"");
		bRet = TRUE;
		id = IDC_PATHOLOGY_ADENOCARCINOMA;
		goto Success;
	}
	bRet = EasyStaticCtrlConnect::GetInstance().GetData(id, controlInfo);
	if (FALSE == bRet)
		goto End;
	bRet = FALSE;
	switch (controlInfo.ctrlName)
	{
	case ControlType::ComboBox:
		ResetComboBox(id, controlInfo.MenuInfo);
		bRet = TRUE;
		break;
	case ControlType::MFCMenuButtonControl:
		GetDlgItem(id)->SetWindowText(L"");
		bRet = TRUE;
		break;
	case ControlType::Edit:
		GetDlgItem(id)->SetWindowText(L"");
		bRet = TRUE;
		break;
	}
Success:
	bRet ? m_personData.SetData(id, L"") : FALSE;
End:
	return;
}

//return the BOOL of changing data or not 
BOOL CManagerDlg::UpdateManagerPersonData(const int nCtrlID)
{
	ManagerData temp;
	CString content;
	BOOL bRet;
	bRet = m_personData.GetData(nCtrlID, temp);
	if (FALSE == bRet)
		return FALSE;
	GetDlgItem(IDC_PATHOLOGY_ADENOCARCINOMA == nCtrlID ? IDC_MFCMENUINFO : nCtrlID)->GetWindowText(content);
	if (temp.data == content)
		return FALSE;
	else
		m_personData.SetData(nCtrlID, content);
	return TRUE;
}

void CManagerDlg::UpdateDialogData(const int nCtrlID /*=NULL*/)
{
	CString title;
	GetWindowText(title);
	if (NULL != nCtrlID && TRUE == UpdateManagerPersonData(nCtrlID))
		m_isChange_noSave = true;
	title.TrimRight(L" - *");
	if (m_isChange_noSave)
		title += L" - *";
	SetWindowText(title);
}

//Clear the ManagerDlg data and hide the dailog 
void CManagerDlg::CloseWindow()
{
	m_personData.Reset();
	m_isChange_noSave = false;
	int nRet;
	if (m_isOnlyDialog)
	{
		ShowWindow(SW_HIDE);
		CBlockDlg::Unblock();
	}
	else
	{
		nRet = m_isChange_noSave ? IDCANCEL : IDOK;
		EndDialog(nRet);
	}
}
