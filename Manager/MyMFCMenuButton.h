#pragma once
#include "afxmenubutton.h"
#include "DynamicMenu.h"

class CMyMFCMenuButton :
	public CMFCMenuButton, public CDynamicMenu
{
public:
	CMyMFCMenuButton();
	~CMyMFCMenuButton();
	virtual void CreateDynamicMenu();
};
