
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Manager.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
/*
void CManagerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�Ի��������
	// 	SCROLLINFO scrollinfo;
	// 	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 	int unit = 6;
	// 	switch (nSBCode)
	// 	{
	// 	case SB_LINEUP:          //Scroll one line up
	// 		scrollinfo.nPos -= 1;
	// 		if (scrollinfo.nPos<scrollinfo.nMin)
	// 		{
	// 			scrollinfo.nPos = scrollinfo.nMin;
	// 			break;
	// 		}
	// 		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 		ScrollWindow(0, unit);
	// 		break;
	// 	case SB_LINEDOWN:           //Scroll one line down
	// 		scrollinfo.nPos += 1;
	// 		if (scrollinfo.nPos + scrollinfo.nPage>scrollinfo.nMax)  //�˴�һ��Ҫע����ϻ���ĳ��ȣ������ж�
	// 		{
	// 			scrollinfo.nPos = scrollinfo.nMax;
	// 			break;
	// 		}
	// 		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 		ScrollWindow(0, -unit);
	// 		break;
	// 	case SB_PAGEUP:            //Scroll one page up.
	// 		scrollinfo.nPos -= 5;
	// 		if (scrollinfo.nPos <= scrollinfo.nMin)
	// 		{
	// 			scrollinfo.nPos = scrollinfo.nMin;
	// 			break;
	// 		}
	// 		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 		ScrollWindow(0, unit * 5);
	// 		break;
	// 	case SB_PAGEDOWN:        //Scroll one page down        
	// 		scrollinfo.nPos += 5;
	// 		if (scrollinfo.nPos + scrollinfo.nPage >= scrollinfo.nMax)  //�˴�һ��Ҫע����ϻ���ĳ��ȣ������ж�
	// 		{
	// 			scrollinfo.nPos = scrollinfo.nMax;
	// 			break;
	// 		}
	// 		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 		ScrollWindow(0, -unit * 5);
	// 		break;
	// 	case SB_ENDSCROLL:      //End scroll     
	// 		break;
	// 	case SB_THUMBPOSITION:  //Scroll to the absolute position. The current position is provided in nPos
	// 		break;
	// 	case SB_THUMBTRACK:                  //Drag scroll box to specified position. The current position is provided in nPos
	// 		ScrollWindow(0, (scrollinfo.nPos - nPos)*unit);
	// 		scrollinfo.nPos = nPos;
	// 		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
	// 		break;
	// 	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
*/

/*
BOOL CManagerDlg::OnEraseBkgnd(CDC* pDC)
{
// 	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//˫����
// 	CRect rc;
// 	CDC dcMem;
// 	GetClientRect(&rc);
// 	CBitmap bmp; //�ڴ��г�����ʱͼ���λͼ
//
//
// 	dcMem.CreateCompatibleDC(pDC); //��������DC���������ڴ�DC
// 	//��������λͼ(������pDC���������򻭳���ͼ�α�ɺ�ɫ)
// 	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
// 	CBitmap *pOldBit = dcMem.SelectObject(&bmp);
// 	//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
// 	dcMem.FillSolidRect(rc, RGB(255, 255, 255));
//
// 	//��ͼ�������Ҫ��ͼ�Ĵ��룬������dcMem����������pDC
//
// 	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
//
// 	//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
// 	//��ͼ��ɺ������
// 	dcMem.DeleteDC();		//ɾ��DC
// 	bmp.DeleteObject();		//ɾ��λͼ
// 	return true;
// 	//����һ��Ҫ��return true��������Զ����ɵģ�����û��࣬�ѻ������ĸ��ǣ���ʲ     ô���Ҳû����
//
return CDialogEx::OnEraseBkgnd(pDC);
}
void CManagerDlg::initScrollbar()
{
SCROLLINFO scrollinfo;
GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
scrollinfo.nPage = 10;    //���û����С
scrollinfo.nMax = 75;     //���ù����������λ��0--75
SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
}
*/


/*
BOOL CheckStrIsIp(CString strIpAddress)
{
BOOL bLegal = TRUE; int nNumberCount = 0; int nDocCount = 0; CString strSub; CString strIP[4]; USHORT usDoc = _T('.'); CString str = strIpAddress;
for (int i = 0; i < str.GetLength(); i++) {
WCHAR C = str.GetAt(i);
USHORT P = C;
if ((P >= 48 && P <= 57) || P == usDoc)
{
if (nNumberCount == 0)//�����ͷ����. �ǷǷ���
{
}
else //ǰ���Ѿ���������
{
if (P == usDoc)
{
if (P == usDoc)
{
}
else //������
{
}
nNumberCount++; strSub = C; bLegal = FALSE; break;
}
}
}
}
}
*/

/*
inline int ToInteger(CString szStr)
{
	int n = -1;
	swscanf_s(szStr, L"%d", &n);
	return n;
}*/

/*
void CManagerDlg::RestoreGroup()
{
static int nCounter = 0;
POINT Newp;
CRect recta;
GetClientRect(&recta);
float fsp[2];
Newp.x = recta.right - recta.left;
Newp.y = recta.bottom - recta.top;
if (old.x == 0 && old.y == 0)
{
nCounter = 0;
return;
}
fsp[0] = (float)Newp.x / old.x;
fsp[1] = (float)Newp.y / old.y;
static const int ExID[] = {
IDC_BASEINFO_STATIC, IDC_CTCHECK_STATIC, IDC_PNR_STATIC,
IDC_OLD_STATIC, IDC_CHEST_EXAMINATION_STATIC, IDC_SURGERY_STATIC,
IDC_PATHOLOGY_RESULTS_STATIC, IDC_PATHOLOGY_ADENOCARCINOMA_STATIC,
IDC_PATHOLOGY_ISOI_STATIC, IDC_PATHOLOGY_FOUNDIFNO_STATIC,
IDC_IMMUNOHISTOCHEMISTRY_STATIC, IDC_GENETIC_TESTING_STATIC,
IDC_FOLLOW_UP_RECORDS_STATIC
};
static CMyList<SCtrlInfo> list;
if (nCounter == 0)
{
SCtrlInfo info;
int woc;
CRect Rect;
CWnd * pWnd = nullptr;
HWND  hwndChild = ::GetWindow(this->m_hWnd, GW_CHILD);  //�г����пؼ�
if (hwndChild == NULL)
return;
while (hwndChild)
{
woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
info.nID = woc;
pWnd = GetDlgItem(woc);
if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
pWnd->GetWindowRect(Rect);
ScreenToClient(Rect);
info.rect = Rect;
list.AddRear(info);
hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
}
nCounter++;
}
SCtrlInfo * info = list.Next();
if (info == nullptr)
exit(1);
int i;
bool isExID = false;
LONG height;
LONG width;
do
{
int nID = info->nID;
isExID = false;
for (i = 0; i < 13; ++i)
{
if (nID == ExID[i])
{
isExID = true;
break;
}
}
height = info->rect.bottom - info->rect.top;
width = info->rect.right - info->rect.left;
info->rect.left = LONG(info->rect.left * fsp[0]);
info->rect.top = LONG(info->rect.top * fsp[1]);
if (isExID)
{
info->rect.right = LONG(info->rect.right * fsp[0]);
info->rect.bottom = LONG(info->rect.bottom * fsp[1]);
}
else
{
info->rect.right = info->rect.left + width;
info->rect.bottom = info->rect.top + height;
}
info = list.Next();
} while (info);
CWnd * pWnd = nullptr;
while (info = list.Next())
{
pWnd = GetDlgItem(info->nID);
if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
pWnd->MoveWindow(info->rect.left, info->rect.top, info->rect.right - info->rect.left, info->rect.bottom - info->rect.top, FALSE);
}
old = Newp;
Invalidate(); UpdateWindow();
}*/


//�������ڻ����
//Checkerboard Layout(can't support much times zoom)
// void CManagerDlg::RestoreGroup()
// {
// 	using namespace std;
// 	static vector<SCtrlInfo> CtrlPositionList;
// 	vector<SCtrlInfo>::iterator it;
// 	SCtrlInfo temp;
// 	static POINT oldWindow;
// 	static const int ExID[] = {
// 		IDC_BASEINFO_STATIC, IDC_CTCHECK_STATIC, IDC_PNR_STATIC,
// 		IDC_OLD_STATIC, IDC_CHEST_EXAMINATION_STATIC, IDC_SURGERY_STATIC,
// 		IDC_PATHOLOGY_RESULTS_STATIC, IDC_PATHOLOGY_ISOI_STATIC,
// 		IDC_PATHOLOGY_FOUNDIFNO_STATIC, IDC_IMMUNOHISTOCHEMISTRY_STATIC,
// 		IDC_GENETIC_TESTING_STATIC, IDC_FOLLOW_UP_RECORDS_STATIC
// 	};
// 	POINT WidthHeight;
// 	float fsp[2];
// 	CRect rect;
// 	CWnd * pWnd;
// 	HWND  hwndChild;
// 	int nID;
// 	bool isExID;
// 	int nIndex;
// 	POINT error_correction;
// 	GetClientRect(&rect);
// 	WidthHeight.x = rect.right - rect.left;
// 	WidthHeight.y = rect.bottom - rect.top;
// 	0 == oldWindow.x || 0 == oldWindow.y ? oldWindow.x = WidthHeight.x, oldWindow.y = WidthHeight.y : 1;
// 	fsp[0] = (float)WidthHeight.x / oldWindow.x;
// 	fsp[1] = (float)WidthHeight.y / oldWindow.y;
// 	error_correction.x = int(fsp[0]) == 1 ? 1 : -1;
// 	error_correction.y = int(fsp[1]) == 1 ? 1 : -1;
// 	oldWindow = WidthHeight;
// 	if (CtrlPositionList.empty())
// 	{
// 		hwndChild = ::GetWindow(this->m_hWnd, GW_CHILD);  //�г����пؼ� 
// 		if (hwndChild == NULL)
// 			return;
// 		while (hwndChild)
// 		{
// 			nID = ::GetDlgCtrlID(hwndChild);//ȡ��ID
// 			temp.nID = nID;
// 			pWnd = GetDlgItem(nID);
// 			if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
// 				pWnd->GetWindowRect(rect);
// 			ScreenToClient(rect);
// 			temp.rect = rect;
// 			CtrlPositionList.push_back(temp);
// 			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
// 		}
// 	}
// 	nIndex = 0;
// 	for (it = CtrlPositionList.begin(); it != CtrlPositionList.end(); ++it, ++nIndex)
// 	{
// 		isExID = false;
// 		for (int nID : ExID)
// 		{
// 			if (nID == it->nID)
// 			{
// 				isExID = true;
// 				break;
// 			}
// 		}
// 		WidthHeight.x = it->rect.right - it->rect.left;
// 		WidthHeight.y = it->rect.bottom - it->rect.top;
// 		temp.nID = it->nID;
// 		temp.rect.left = LONG(it->rect.left * fsp[0]) + error_correction.x;
// 		temp.rect.top = LONG(it->rect.top * fsp[1]) + error_correction.y;
// 		if (isExID)
// 		{
// 			WidthHeight.x *= LONG(WidthHeight.x * fsp[0]);
// 			WidthHeight.y *= LONG(WidthHeight.y * fsp[1]);
// 		}
// 		temp.rect.right = temp.rect.left + WidthHeight.x;
// 		temp.rect.bottom = temp.rect.top + WidthHeight.y;
// 		it = CtrlPositionList.erase(it);
// 		CtrlPositionList.insert(it, temp);
// 		it = CtrlPositionList.begin() + nIndex;
// 		pWnd = GetDlgItem(temp.nID);
// 		if (pWnd != nullptr && IsWindow(pWnd->m_hWnd))
// 			pWnd->MoveWindow(temp.rect.left, temp.rect.top, temp.rect.right - temp.rect.left, temp.rect.bottom - temp.rect.top, FALSE);
// 	}
// 	Invalidate(); UpdateWindow();
// }