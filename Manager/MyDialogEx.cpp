#include "stdafx.h"
#include <imm.h>
#include "MyDialogEx.h"


CMyDialogEx::CMyDialogEx() 
	:CDialogEx()
{
}


CMyDialogEx::CMyDialogEx(UINT nIDTemplate, CWnd *pParent /*= NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{

}

CMyDialogEx::CMyDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd /*= NULL*/)
	: CDialogEx(lpszTemplateName, pParentWnd)
{

}

CMyDialogEx::~CMyDialogEx()
{
}

void CMyDialogEx::OnlyAgreeNo(int nID)
{
	static CString record;
	wchar_t c;
	int i, nLen;
	CString temp;
	CEdit * pEdit = (CEdit*)GetDlgItem(nID);
	pEdit->GetWindowText(temp);
	nLen = temp.GetLength();
	for (i = 0; i < nLen; ++i)
	{
		c = temp.GetAt(i);
		if (256 < c|| !isdigit(c) && !isalpha(c))
		{
			nLen = record.GetLength();
			pEdit->SetWindowText(record);
			pEdit->SetSel(nLen, nLen, TRUE);
			return;
		}
	}
	record = temp;
}

void CMyDialogEx::OnlyAgreeDecimal(int nID)
{
	CString temp;
	static CString record;
	GetDlgItemText(nID, temp);
	int temp_len = temp.GetLength();
	wchar_t c;
	int n;
	bool hasDecimal = false;
	CString changed;
	for (int i = 0; i < temp_len; ++i)
	{
		c = temp.GetAt(i);
		if (hasDecimal == true)
		{
			if (c == L'.')
			{
				SetDlgItemText(nID, record);
				((CEdit *)GetDlgItem(nID))->SetSel(record.GetLength(), record.GetLength(), TRUE);
				return;
			}
		}
		else
		{
			if (c == L'.')
				hasDecimal = true;
		}
		n = int(c);
		if (n > 256 || !isdigit(c) && c != L'.')
		{
			SetDlgItemText(nID, record);
			((CEdit *)GetDlgItem(nID))->SetSel(record.GetLength(), record.GetLength(), TRUE);
			return;
		}
	}
	record = temp;
}

void CMyDialogEx::BanInputMethod(int nID, bool o /*=true*/)
{
	HWND hWnd = NULL;
	HIMC hImc = NULL;
	if (!o)
		return;

	hWnd = GetDlgItem(nID)->m_hWnd;
	if (hWnd && IsWindow(hWnd))
	{
		hImc = ImmGetContext(hWnd);
		if (hImc) {
			ImmAssociateContext(hWnd, NULL);
		}
		ImmReleaseContext(hWnd, hImc);
		::SetFocus(hWnd);
	}
}

void CMyDialogEx::DecimalCompletion(int nID)
{
	CString temp;
	GetDlgItem(nID)->GetWindowText(temp);
	wchar_t head, rear;
	int len = temp.GetLength();
	if (len == 0)
		return;
	head = temp.GetAt(0);
	rear = temp.GetAt(len - 1);
	CString changed;
	if (head == L'.')
	{
		changed = L"0" + temp;
		SetDlgItemText(nID, changed);
		((CEdit *)GetDlgItem(nID))->SetSel(temp.GetLength(), temp.GetLength(), TRUE);
		temp = changed;
	}
	if (rear == L'.')
	{
		temp += L"00";
		SetDlgItemText(nID, temp);
		((CEdit *)GetDlgItem(nID))->SetSel(temp.GetLength(), temp.GetLength(), TRUE);
	}
}

void CMyDialogEx::PaintGreenBackground()
{
#ifdef _GREEN_BG_
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(199, 237, 204));   //����Ϊ��ɫ����
#else
	CPaintDC dc(this); // device context for painting
#endif
}

// �߿��ػ�
// void CMyDialogEx::DrawBorder(CDC *pDC, COLORREF color)
// {
// 	if (m_hWnd)
// 	{
// 		//RGB(89, 163, 179)
// 		CBrush Brush(color);
// 		CBrush* pOldBrush = pDC->SelectObject(&Brush);
// 		CRect rtWnd;
// 		GetWindowRect(&rtWnd);
// 		CPoint point;
// 		//��䶥�����
// 		point.x = rtWnd.Width();
// 		point.y = GetSystemMetrics(SM_CYFRAME) + 1;
// 		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
// 		//��������
// 		point.x = GetSystemMetrics(SM_CXFRAME);
// 		point.y = rtWnd.Height();
// 		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
// 		//���ײ����
// 		point.x = rtWnd.Width();
// 		point.y = GetSystemMetrics(SM_CYFRAME) + 1;
// 		pDC->PatBlt(0, rtWnd.Height() - point.y, point.x, point.y, PATCOPY);
// 		//����Ҳ���
// 		point.x = GetSystemMetrics(SM_CXFRAME);
// 		point.y = rtWnd.Height();
// 		pDC->PatBlt(rtWnd.Width() - point.x, 0, point.x, point.y, PATCOPY);
// 	}
// }

void CMyDialogEx::DrawBorder(UINT message, COLORREF color)
{
	if (message == WM_MOVE || message == WM_PAINT || message == WM_NCPAINT || message == WM_NCACTIVATE || message == WM_NOTIFY)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC && m_hWnd)
		{
			CBrush Brush(color);
			CBrush* pOldBrush = pWinDC->SelectObject(&Brush);
			CRect rtWnd;
			GetWindowRect(&rtWnd);
			CPoint point;
			//��䶥�����
			point.x = rtWnd.Width();
			point.y = GetSystemMetrics(SM_CYFRAME) + 1;
			pWinDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
			//��������
			point.x = GetSystemMetrics(SM_CXFRAME);
			point.y = rtWnd.Height();
			pWinDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
			//���ײ����
			point.x = rtWnd.Width();
			point.y = GetSystemMetrics(SM_CYFRAME) + 1;
			pWinDC->PatBlt(0, rtWnd.Height() - point.y, point.x, point.y, PATCOPY);
			//����Ҳ���
			point.x = GetSystemMetrics(SM_CXFRAME);
			point.y = rtWnd.Height();
			pWinDC->PatBlt(rtWnd.Width() - point.x, 0, point.x, point.y, PATCOPY);
		}
		ReleaseDC(pWinDC);
	}
}

LRESULT CMyDialogEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef _GREEN_BAR_
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);

	if (!::IsWindow(m_hWnd))
		return lrst;

	DrawBorder(message, RGB(89, 163, 179));
	return lrst;
#else
	return CDialog::DefWindowProc(message, wParam, lParam);
#endif // _GREEN_BAR_
}

//�ú�������ȱ�ݵ�,���ܽ��ж��ε���
//�Ľ��ķ�ʽ�ǽ� �ؼ��� TD_Position ��Ϣ��������,�ɵ����ĺ����Զ�Ӧ�� ID��ŵĿؼ����л�ȡ
//ѧϰEasySize�Ĵ���ģʽ,���Լ��Ĵ�������ͨ�ú���
//�����ؼ����� CheckLayout �� AreaLayout (���̲���, ���򻮷�)

/*
TD_Position ����� �����ؼ����� �ػ���һ��λ����Ϣ,�� CheckLayout ��ǰ�� RestoreGroup ���㷨�����ȶ�
����� RestoreGroup һ�����ֿؼ��� ����Ư��.
TD_Position ����¼���ǿؼ��Ļ���(�Կؼ������϶�����Ϊ�ؼ��Ļ���),�ڳ�ʼ�����е� ���ݱ���(˼·����jpgͼƬ��ѹ���㷨)
*/

/*
CheckLayout ˼��:�ؼ������Ӵ���������.���̴�С�����仯,���ӵĴ�С���ᷢ���ı�,������������������ԭ��������������иı�.
			��ԭ���������м������,�����̷Ŵ�����������м�.�ɶ��������ɵ�ͼ��Ҳͬ��.

AreaLayout	˼��: ��ԭ���ı����Ŵ��㷨�м���߽������.�൱����һ����һ�����Ϊ�������ֵ��⼸������֮������ı�������,����̬�������仯���㷨
			������ Group �ؼ����Ű�
			Ϊʲô��ֱ��ʹ�� RestoreGroup �㷨:
			1.	�ؼ������꾭������Ķ�����Ż���ɿؼ������Ư��
			2.	������ķŴ����ʱ, Group�ؼ��ʹ����Ե�ľ���ἱ������, ʹ�ؼ��Ĳ���������ɢ

���������Ż�����:
	1.	���㷨�е�static������������,ʹ�㷨�ܽ��ж��ε���.
	2.	�Կؼ��Ĳ��ֳ��Լ���Ϊ Map�ؼ���ʽ �򻯵��÷�ʽ
	3.	����µ��Ű淽ʽ ��ʽ����, �ؼ����� �� ����Ű�

����AreaLayout��ʵ�ֵĹ��ܹ��ڸ���, ���Բ��� �����Ŵ�� EasySize ��ʵ��
*/

void CMyDialogEx::CheckerboardLayout(const int ExID[] /*= nullptr*/, BOOL isAll /*= TRUE*/, int)
{
	using namespace std;
	struct SCtrlInfo
	{
		int id;
		double x;
		double y;
	};
	static vector<SCtrlInfo> CtrlPositionList;
	vector<SCtrlInfo>::iterator it;
	SCtrlInfo temp;
	static POINT oldWindow = { 0L, 0L };
	POINT WidthHeight;
	POINT CtrlWH;
	CRect rect;
	CWnd * pWnd;
	HWND  hwndChild;
	int nID;
	int i;
	bool isExID;
	GetClientRect(&rect);
	WidthHeight.x = rect.right - rect.left;
	WidthHeight.y = rect.bottom - rect.top;
	if (CtrlPositionList.empty())
	{
		hwndChild = ::GetWindow(this->m_hWnd, GW_CHILD);
		if (hwndChild == NULL)
		{
			oldWindow = WidthHeight;
			return;
		}
		while (hwndChild)
		{
			nID = ::GetDlgCtrlID(hwndChild);
			temp.id = nID;
			pWnd = GetDlgItem(nID);
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->GetWindowRect(rect);
			else
				return;
			ScreenToClient(rect);
			temp.x = rect.left / double(oldWindow.x);
			temp.y = rect.top / double(oldWindow.y);
			CtrlPositionList.push_back(temp);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
	}
	for (it = CtrlPositionList.begin(); it != CtrlPositionList.end(); ++it)
	{
		if (nullptr != ExID)
		{
			isExID = false;
			i = 0;
			while (NULL != *(ExID + i))
			{
				if (*(ExID + i) == it->id)
				{
					isExID = true;
					break;
				}
				++i;
			}
		}
		else
			isExID = false;
		if (isAll ? !isExID : isExID)
		{
			pWnd = GetDlgItem(it->id);
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->GetWindowRect(rect);
			else
				continue;
			ScreenToClient(rect);
			CtrlWH.x = rect.right - rect.left;
			CtrlWH.y = rect.bottom - rect.top;
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->MoveWindow(LONG(WidthHeight.x * it->x), LONG(WidthHeight.y * it->y), CtrlWH.x, CtrlWH.y, FALSE);
			else
				continue;
		}
	}
	Invalidate(); UpdateWindow();
}

void CMyDialogEx::CheckerboardLayout(std::vector<SCtrlTDPosition> & CtrlTDPositionList)
{
	std::vector<SCtrlTDPosition>::iterator it;
	POINT WidthHeight, CtrlWH;
	CRect rect;
	CWnd * pWnd;
	GetClientRect(&rect);
	WidthHeight.x = rect.right - rect.left;
	WidthHeight.y = rect.bottom - rect.top;
	for (it = CtrlTDPositionList.begin(); it != CtrlTDPositionList.end(); ++it)
	{
		pWnd = GetDlgItem(it->id);
		if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
			pWnd->GetWindowRect(rect);
		else
			continue;
		ScreenToClient(rect);
		CtrlWH.x = rect.right - rect.left;
		CtrlWH.y = rect.bottom - rect.top;
		if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
			pWnd->MoveWindow(LONG(WidthHeight.x * it->x), LONG(WidthHeight.y * it->y), CtrlWH.x, CtrlWH.y, FALSE);
		else
			continue;
	}
	Invalidate(); UpdateWindow();
}

void CMyDialogEx::RegionLayout(POINT oldWH, std::vector<SCtrlTDPosition> & CtrlTDPositionList)
{
	std::vector<SCtrlTDPosition>::iterator it;
	POINT WidthHeight, CtrlWH;
	CRect rect;
	CWnd * pWnd;
	float WH[2] = { 0.00 };
	GetClientRect(&rect);
	WidthHeight.x = rect.right - rect.left;
	WidthHeight.y = rect.bottom - rect.top;
	WH[0] = (float)WidthHeight.x / oldWH.x;
	WH[1] = (float)WidthHeight.y / oldWH.y;
	if (!CtrlTDPositionList.empty())
	{
		for (it = CtrlTDPositionList.begin(); it != CtrlTDPositionList.end(); ++it)
		{
			pWnd = GetDlgItem(it->id);
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->GetWindowRect(rect);
			else
				continue;
			ScreenToClient(rect);
			CtrlWH.x = rect.right - rect.left;
			CtrlWH.y = rect.bottom - rect.top;
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->MoveWindow(LONG(WidthHeight.x * it->x), LONG(WidthHeight.y * it->y), int(CtrlWH.x * WH[0]), int(CtrlWH.y * WH[1]), FALSE);
			else
				continue;
		}
	}
	Invalidate(); UpdateWindow();
}

std::vector<CMyDialogEx::SCtrlTDPosition> CMyDialogEx::GetCtrlTDPosition(const int ExID[] /*= nullptr*/, BOOL isAll /*= TRUE*/)
{
	POINT WidthHeight = { 0L, 0L };
	ASSERT(isAll || nullptr != ExID);
	std::vector<SCtrlTDPosition> CtrlDPositionList;
	CRect rect;
	GetClientRect(&rect);
	WidthHeight.x = rect.right - rect.left;
	WidthHeight.y = rect.bottom - rect.top;
	HWND hwndChild;
	int nID;
	CWnd * pWnd;
	SCtrlTDPosition temp;
	int i;
	bool isExID;
	hwndChild = ::GetWindow(this->m_hWnd, GW_CHILD);
	if (hwndChild == NULL)
		goto End;
	if (isAll)
	{
		while (hwndChild)
		{
			nID = ::GetDlgCtrlID(hwndChild);
			isExID = false;
			if (nullptr != ExID)
			{
				i = 0;
				while (NULL != *(ExID + i))
				{
					if (*(ExID + i) == nID)
					{
						isExID = true;
						break;
					}
					++i;
				}
			}
			if (!isExID)
			{
				temp.id = nID;
				pWnd = GetDlgItem(nID);
				if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
					pWnd->GetWindowRect(rect);
				else
					continue;
				ScreenToClient(rect);
				temp.x = rect.left / double(WidthHeight.x);
				temp.y = rect.top / double(WidthHeight.y);
				CtrlDPositionList.push_back(temp);
			}
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
	}
	else
	{
		i = 0;
		while (NULL != *(ExID + i))
		{
			nID = *(ExID + i);
			temp.id = nID;
			pWnd = GetDlgItem(nID);
			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
				pWnd->GetWindowRect(rect);
			else
				continue;
			ScreenToClient(rect);
			temp.x = rect.left / double(WidthHeight.x);
			temp.y = rect.top / double(WidthHeight.y);
			CtrlDPositionList.push_back(temp);
			++i;
		}
	}
End:
	return CtrlDPositionList;
}

void CMyDialogEx::OnCtrlInfo(WPARAM wParam, LPARAM lParam)
{

}

CMyDialogEx::CtrlInfo* CMyDialogEx::GetCtrlInfo()
{
	static const CtrlInfo ctrlsInfo[] = {
		{}
	};
	return (CtrlInfo*)ctrlsInfo;
}


BOOL CMyDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int i = 0, n;
	CtrlInfo * ctrlsInfo = GetCtrlInfo();
	CtrlInfo * p = ctrlsInfo + i;
	while (NULL == p->CtrlName)
	{
		p = ctrlsInfo + i;
		switch (p->CtrlName)
		{
		case ControlType::Edit:
			if (p->attribute & EDITINPUTNO || p->attribute & EDITINPUTDECIMAL)
				BanInputMethod(p->ctrlID);
			else if (p->attribute & EDITINPUTNUMBER)
				GetDlgItem(p->ctrlID)->ModifyStyle(0, ES_NUMBER);
			//Edit Text
			if (NULL != (n = (p->attribute >> 1) % 256))
				((CEdit*)GetDlgItem(p->ctrlID))->LimitText(n);
			break;
		default:
			break;
		}
		++i;
	}
	return TRUE;
}
