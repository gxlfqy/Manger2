#pragma once
#include <iostream>

typedef struct _treeNodePtr
{
	_treeNodePtr ** leaf = nullptr;
	~_treeNodePtr();
	_treeNodePtr& operator[](int index);
}nodeptr;

template<class T>
class CMyTree
{
private:
	typedef struct _treeNode
	{
		nodeptr ptr;
		T data;
		_treeNode(T _data);
	}node;
	template<class T>
	CMyTree::_treeNode<T>::_treeNode(T _data)
	{
		data = _data;
	}
public:

};