#include "stdafx.h"
#include "DynamicMenu.h"
#include <stack>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDynamicMenu::CDynamicMenu() :m_hDMenu(NULL)
{
}


CDynamicMenu::~CDynamicMenu()
{
}

void CDynamicMenu::CreateDynamicMenu()
{
	HMENU hMenu = buildMenu();
	m_hDMenu = hMenu;
}

CString CDynamicMenu::GetTreeString(int o, CString connect)const
{
	static std::stack<int> data;
	CBinaryTree<_menuInfo> menuInfobTree = m_menuInfobTree;
	CString ret = L"";
	const _menuInfo * temp = nullptr;
	int term = 0;
	while (o)
	{
		term = o % 256;
		data.push(term);
		o >>= 8;
	}
	int a = 0;
	int i = 0;
	void * mark = menuInfobTree.GetMark();
	if (data.empty())
		goto End;
	int n = 0;
	while (true)
	{
		a = data.top() - 1;
		data.pop();
		for (i = 0; i < a; ++i)
		{
			if (menuInfobTree.hasLeft())
				menuInfobTree.Left();
			else
			{
				ret = L"";
				goto End;
			}
		}
		if (data.empty() || data.top() == 0)
			break;
		if (menuInfobTree.hasRight())
		{
			temp = menuInfobTree.Get();
			if (n++ > 0)
				ret += connect;
			ret += temp->title;
			menuInfobTree.Right();
			
		}
		else
		{
			ret = L"";
			goto End;
		}
	}
	temp = menuInfobTree.Get();
	if (menuInfobTree.hasUp())
		ret += connect;
	ret += temp->title;
End:
	menuInfobTree.GotoMark(mark);

	return ret;
}

HMENU CDynamicMenu::buildMenu()
{
	CMenu * pMenu = new CMenu;
		pMenu->CreatePopupMenu();
	void * mark = m_menuInfobTree.GetMark();
	const _menuInfo * temp;
	while (!m_menuInfobTree.isEmpty())
	{
		if (m_menuInfobTree.hasRight())
		{
			temp = m_menuInfobTree.Get();
			m_menuInfobTree.Right();
			pMenu->AppendMenu(MF_POPUP, (UINT)buildMenu(), temp->title);
			m_menuInfobTree.Up();
			if (m_menuInfobTree.hasLeft())
				m_menuInfobTree.Left();
			else
				break;
		}
		else
		{
			temp = m_menuInfobTree.Get();
			pMenu->AppendMenu(MF_STRING, temp->nID, temp->title);
			if (m_menuInfobTree.hasLeft())
				m_menuInfobTree.Left();
			else
				break;
		}
	}
	m_menuInfobTree.GotoMark(mark);
	return pMenu->m_hMenu;
}

void SetMenuInfoBTree(_menuInfo temp, CBinaryTree<_menuInfo> * pMenuInfo)
{
	static std::stack<int> data;
	int nID = temp.nID;
	int term = 0;
	while (nID)
	{
		term = nID % 256;
		data.push(term);
		nID >>= 8;
	}
	int a = 0;
	int i = 0;
	void * mark = pMenuInfo->GetMark();
	while (!data.empty())
	{
		a = data.top() - 1;
		data.pop();
		for (i = 0; i < a; ++i)
			pMenuInfo->Left();
		if (data.empty() || data.top() == 0)
			break;
		pMenuInfo->Right();
	}
	pMenuInfo->Set(temp);
	pMenuInfo->GotoMark(mark);
}