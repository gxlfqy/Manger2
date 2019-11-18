#include "stdafx.h"
#include "MyMFCMenuButton.h"


CMyMFCMenuButton::CMyMFCMenuButton()
{
}


CMyMFCMenuButton::~CMyMFCMenuButton()
{
}

void CMyMFCMenuButton::CreateDynamicMenu()
{
	CDynamicMenu::CreateDynamicMenu();
	m_hMenu = m_hDMenu;
}
