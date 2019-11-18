#pragma once

#define AllocItemT(n, v) pitem n; n = new item(v); if(n == nullptr) alloc_fail()
#define AllocItemO(n) pitem n; n = new item(); if(n == nullptr) alloc_fail()
#define pcT const T *
template<typename T>
class CBinaryTree
{
	typedef struct item
	{
		T data;
		item * up = nullptr;
		item * left = nullptr;
		item * right = nullptr;
		item(T _val) :data(_val){ }
		item(){ }
		~item(){ }
		void Reset()
		{
			if (left != nullptr)
			{
				delete left;
				left = nullptr;
				up = nullptr;
			}
			if (right != nullptr)
			{
				delete right;
				right = nullptr;
			}
			up = nullptr;
		}
		void operator=(item _val)
		{
			item * temp = set_item(&_val);
			data = temp->data;
			left = temp->left;
			right = temp->right;
		}
	private:
		item * set_item(item * _val)
		{
			item * temp = new item;
			if (temp == nullptr)
				exit(1);
			static item * record = nullptr;
			temp->up = record;
			record = temp;
			temp->data = _val->data;
			if (_val->right != nullptr)
			{
				temp->right = set_item(_val->right);
			}
			if (_val->left != nullptr)
			{
				temp->left = set_item(_val->left);
			}
			return temp;
		}
	}*pitem;
	item m_root;
	pitem m_p;
	void alloc_fail(){ exit(1); }
	void opera_error(){ exit(1); }
public:
	CBinaryTree() :m_p(&m_root){}
	CBinaryTree(T _val) :m_p(&m_root){ m_p->data = _val; }
	CBinaryTree(const CBinaryTree<T>& obj)
	{
		m_root = obj.m_root;
		m_p = &m_root;
	}
	~CBinaryTree(){ m_p = nullptr; m_root.Reset(); }

	void Set(T _val){ m_p->data = _val; }
	pcT Get()const{ return m_p != nullptr ? &(m_p->data) : nullptr; }
	pcT Left() 
	{
		if (m_p->left == nullptr)
		{
			AllocItemO(temp);
			m_p->left = temp;
			temp->up = m_p;
		}
		m_p = m_p->left;
		return Get();
	}
	pcT Right()
	{
		if (m_p->right == nullptr)
		{
			AllocItemO(temp);
			m_p->right = temp;
			temp->up = m_p;
		}
		m_p = m_p->right;
		return Get();
	}
	pcT Up(){ return m_p = m_p->up, Get(); }
	pcT Root(){ return m_p = &m_root, Get(); }
	void SetLeft(T _val){ AllocItemT(temp, _val); temp->up = m_p, m_p->left = temp; }
	void SetRight(T _val){ AllocItemT(temp, _val); temp->up = m_p, m_p->right = temp; }
	void SetRoot(T _val){ m_root.data = _val; }
	//该节点有左节点
	bool hasLeft()const { return m_p->left != nullptr; }
	//表示该节点有右节点
	bool hasRight()const { return m_p->right != nullptr; }
	//表示该节点有上节点
	bool hasUp()const { return m_p->up != nullptr; }
	//表示该节点为空
	bool isEmpty()const { return m_p == nullptr; }
	void * GetMark()const { return m_p; }
	void GotoMark(void * mark){ m_p = (pitem)mark; }
};

#undef AllocItemT
#undef AllocItemO
#undef pcT