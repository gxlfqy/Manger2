#pragma once
#include "afxwin.h"
#include "BinaryTree.h"

struct _menuInfo
{
	CString title;
	int nID = 0;
};

class CDynamicMenu
{
public:
	CBinaryTree<_menuInfo> m_menuInfobTree;
	HMENU m_hDMenu;
public:
	CDynamicMenu();
	~CDynamicMenu();
	virtual void CreateDynamicMenu();
	CString GetTreeString(int nID, CString connect)const;
private:
	HMENU buildMenu();
};

void SetMenuInfoBTree(_menuInfo temp, CBinaryTree<_menuInfo> * pMenuInfo);

#define EC_CDynamicMenu_InitDynamicMenu(dynamicMenu) \
	CDynamicMenu * __EC__DM = &dynamicMenu; \
	CBinaryTree<_menuInfo> * __EC__pMenuInfo = &(__EC__DM->m_menuInfobTree); \
	std::vector<_menuInfo> list; \
	_menuInfo temp

#define EC_CDynamicMenu_SetMenuInfo(i, t) \
	temp.title = L##t; \
	temp.nID = 0x##i; \
	list.push_back(temp)

#define EC_CDynamicMenu_BuildDynamicMenu  \
	int __EC__list_len = list.size(); \
	for (int i = 0; i < __EC__list_len; ++i) { SetMenuInfoBTree(list.at(i), __EC__pMenuInfo); }\
	__EC__DM->CreateDynamicMenu()

