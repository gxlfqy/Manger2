#pragma once
#include "stdafx.h"
#include <assert.h>

template <class T>
class CMyList
{
protected:
	typedef struct _node{
		T data;
		_node * prev = nullptr;
		_node * next = nullptr;
		_node()
		{
		}
		_node(T _d) :data(_d)
		{
		}
	}node, *list;
	list m_head;
public:
	CMyList() :m_head(nullptr)
	{
	}
	~CMyList();
	CMyList(const CMyList<T> & o)
	{
		T * pt = o.Next(CMyList<T>::NextAtHead);
		while (pt)
		{
			AddRear(*pt);
			pt = o.Next();
		}
	}
	void operator=(const CMyList<T> & o)
	{
		T * pt = o.Next(CMyList<T>::NextAtHead);
		if (m_head != nullptr)
		{
			delete m_head;
			m_head = nullptr;
		}
		while (pt)
		{
			AddRear(*pt);
			pt = o.Next();
		}
	}
	void operator+=(const CMyList<T> & o)
	{
		T * pt = o.Next(CMyList<T>::NextAtHead);
		while (pt)
		{
			AddRear(*pt);
			pt = o.Next();
		}
	}
public:
	void AddRear();
	void AddRear(T _d);
	enum enext { NextAtHead, NextAtRecord };
	T* Next(enext o = NextAtRecord)const;
	T* GetHead();
	void DelAllNode()
	{
		if (nullptr == m_head)
			return;
		node * pt = m_head;
		node * prev = m_head;
		while (pt->next)
		{
			if (nullptr != pt->prev)
			{
				pt->prev->next = nullptr;
				delete pt->prev;
				pt->prev = nullptr;
			}
			pt = pt->next;
		}
		pt->prev = nullptr;
		delete pt;
		m_head = nullptr;
	}
	void DelNode(unsigned int index)
	{
		if (m_head == nullptr)
			return;
		node * p = m_head;
		unsigned list_len = GetLength();
		assert(index < list_len);
		if (index >= list_len)
			exit(1);

		if (index == 0)
		{
			m_head = m_head->next ? m_head->next : nullptr;
			delete p;
		}
		else if (index == list_len - 1)
		{
			for (unsigned int i = 0; i < index; ++i)
				p = p->next;
			node * prev = p->prev;
			prev->next = nullptr;
			delete p;
		}
		else
		{
			for (unsigned int i = 0; i < index; ++i)
				p = p->next;
			node * prev = p->prev;
			node * next = p->next;
			prev->next = next;
			next->prev = prev;
			delete p;
		}
	}
	unsigned int GetLength();

};

template <class T>
CMyList<T>::~CMyList()
{
	DelAllNode();
}

template <class T>
void CMyList<T>::AddRear()
{
	node * pNew = new node;
	if (pNew == nullptr)
		exit(1);
	if (m_head == nullptr)
		m_head = pNew;
	else
	{
		node * pTail = m_head;
		while (pTail->next)
			pTail = pTail->next;
		pTail->next = pNew;
		pNew->prev = pt;
	}
}


template <class T>
void CMyList<T>::AddRear(T _d)
{
	node * pNew = new node(_d);
	if (pNew == nullptr)
		exit(1);
	if (m_head == nullptr)
		m_head = pNew;
	else
	{
		node * pTail = m_head;
		while (pTail->next)
			pTail = pTail->next;
		pTail->next = pNew;
		pNew->prev = pTail;
	}
}

template <class T>
T* CMyList<T>::Next(enext o)const
{
	static node * p = nullptr;
	if (m_head == nullptr)
	{
		p = nullptr;
		return nullptr;
	}
	if (o == NextAtHead)
		p = m_head;
	else if (o != NextAtHead && o != NextAtRecord)
		return nullptr;

	if (o == NextAtRecord)
	{
		if (p == nullptr)
			p = m_head;
		else
		{
			p = p->next;
			if (p == nullptr)
				return nullptr;
		}
	}
	return &(p->data);
}

template <class T>
T* CMyList<T>::GetHead()
{
	return &(m_head->data);
}

template <class T>
unsigned int CMyList<T>::GetLength()
{
	node * p = m_head;
	if (m_head == nullptr)
		return 0;
	int n = 0;
	while (p)
	{
		p = p->next;
		n++;
	}
	return n;
}