#include "stdafx.h"
#include "InputDataBaseInfoDlg.h"
#include "ManagerADO.h"

#define SYSLINK(str)  L"<a href=\"\">"##str##L"</a>"

const wchar_t * CInputDataBaseInfoDlg::m_caption[2] = {
	L"数据库 - [连接本地数据库]",
	L"数据库 - [连接远程数据库]"
};

const wchar_t * CInputDataBaseInfoDlg::m_sysLinkCaption[2] = {
	L"连接本地数据库",
	L"连接远程数据库"
};

IMPLEMENT_DYNAMIC(CInputDataBaseInfoDlg, CDialogEx)

CInputDataBaseInfoDlg::CInputDataBaseInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialogEx(CInputDataBaseInfoDlg::IDD, pParent)
	, m_szName(m_data.Name)
	, m_szIP(m_data.IP)
	, m_szUserName(m_data.UserName)
	, m_szPass(m_data.Pass)
{
}

void CInputDataBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATABASE_NAME, m_szName);
	DDX_Text(pDX, IDC_DATABASE_IP, m_szIP);
	DDX_Text(pDX, IDC_DATABASE_USERNAME, m_szUserName);
	DDX_Text(pDX, IDC_DATABASE_PASS, m_szPass);
	DDX_Control(pDX, IDC_SYSLINK, m_LinkCtrl);
}

void CInputDataBaseInfoDlg::MoveNextContorl()
{
	CWnd * pWndLinkBn = GetDlgItem(IDC_DATABASE_LINK);
	CWnd * pWnd;
	switch (m_enState)
	{
	case Local:
		GetDlgItem(IDC_DATABASE_NAME)->SetFocus();
		break;
	case Remote:
		pWnd = GetNextDlgTabItem(GetFocus());
		if (pWnd == pWndLinkBn)
			GetDlgItem(IDC_DATABASE_NAME)->SetFocus();
		else
			pWnd->SetFocus();
		break;
	}
}

inline CString ToSysLinkCaption(const CString & caption)
{
	CString result;
	result.Format(L"<a href=\"\">%s</a>", caption);
	return result;
}

BEGIN_MESSAGE_MAP(CInputDataBaseInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DATABASE_LINK, &CInputDataBaseInfoDlg::OnBnClickedDatabaselink)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK, &CInputDataBaseInfoDlg::OnNMClickSyslink)
END_MESSAGE_MAP()

// CInputDataBaseInfoDlg 消息处理程序

BOOL CInputDataBaseInfoDlg::OnInitDialog()
{
	CEdit* pEdit = nullptr;
	static const int nIDs[] = {
		IDC_DATABASE_NAME, IDC_DATABASE_IP, IDC_DATABASE_USERNAME, IDC_DATABASE_PASS
	};
	CDialogEx::OnInitDialog();
	for (int term : nIDs)
		(((CEdit*)GetDlgItem(term)))->LimitText(64);
	switch (m_enState)
	{
	case CInputDataBaseInfoDlg::Local:
		m_LinkCtrl.SetWindowText(ToSysLinkCaption(CInputDataBaseInfoDlg::m_sysLinkCaption[1]));
		BanInputMethod(IDC_DATABASE_IP);
		pEdit = (CEdit*)GetDlgItem(IDC_DATABASE_IP);
		pEdit->SetWindowText(L"127.0.0.1,1433");
		pEdit->SetReadOnly(TRUE);
		break;
	case CInputDataBaseInfoDlg::Remote:
		m_LinkCtrl.SetWindowText(ToSysLinkCaption(CInputDataBaseInfoDlg::m_sysLinkCaption[0]));
		break;
	}
	SetWindowText(CInputDataBaseInfoDlg::m_caption[m_enState]);
	return TRUE;
}

void CInputDataBaseInfoDlg::OnBnClickedDatabaselink()
{
	bool isValid = true;
	UpdateData(TRUE);
	switch (m_enState)
	{
	case Remote:
		isValid = IsValidIP(m_szIP) && !m_szUserName.IsEmpty() ? isValid : false;
		if (!isValid) break;
	case Local:
		isValid = !m_szName.IsEmpty() ? isValid : false;
		break;
	default:
		isValid = false;
		break;
	}
	if (!isValid)
	{
		AfxMessageBox(L"参数不合法");
		return;
	}
	CManagerStringADO::LinkDataBase(this->m_szName, this->m_szIP, this->m_szUserName, this->m_szPass) ? CDialogEx::OnOK() : AfxMessageBox(L"连接失败");
}

//判定是否为有效IP地址
bool CInputDataBaseInfoDlg::IsValidIP(CString szIP)
{
	char ch, next, i = 0, nPartNum = 0;
	short term = 0;
	if (nullptr != wcsstr(szIP.GetBuffer(), L"000") || nullptr != wcsstr(szIP.GetBuffer(), L".00"))
		return false;
	while('\0' != (ch = char(szIP.GetAt(i))))
	{
		next = char(szIP.GetAt(i + 1));
		if ('.' == ch && '.' != next)
			term = 0;
		else if (isdigit(ch))
		{
			term *= 10;
			term += ch - 48;
			if (255 < term)
				return false;
			else if (3 < nPartNum)
				return false;
			else if ('.' == next || '\0' == next)
				++nPartNum;
		}
		else
			return false;
		++i;
	}
	return 4 == nPartNum;
}

void CInputDataBaseInfoDlg::OnNMClickSyslink(NMHDR *pNMHDR, LRESULT *pResult)
{
	CEdit * pIPEdit = (CEdit*)GetDlgItem(IDC_DATABASE_IP);
	switch (m_enState)
	{
	case CInputDataBaseInfoDlg::Local:
		m_enState = CInputDataBaseInfoDlg::Remote;
		m_LinkCtrl.SetWindowText(ToSysLinkCaption(CInputDataBaseInfoDlg::m_sysLinkCaption[0]));
		pIPEdit->SetWindowText(L"");
		pIPEdit->SetReadOnly(FALSE);
		break;
	case CInputDataBaseInfoDlg::Remote:
		m_enState = CInputDataBaseInfoDlg::Local;
		m_LinkCtrl.SetWindowText(ToSysLinkCaption(CInputDataBaseInfoDlg::m_sysLinkCaption[1]));
		pIPEdit->SetWindowText(L"127.0.0.1,1433");
		pIPEdit->SetReadOnly(TRUE);
		break;
	}
	SetWindowText(CInputDataBaseInfoDlg::m_caption[m_enState]);
}

#undef SYSLINK