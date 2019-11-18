#include "CMyTree.h"
#include "assert.h"

_treeNodePtr::~_treeNodePtr()
{
	if (leaf == nullptr)
		return;
	nodeptr * p = nullptr;
	int i = 0;
	while (p = *(leaf + i++))delete p, p = nullptr;
}

_treeNodePtr& _treeNodePtr::operator[](int index)
{
	assert(leaf != nullptr);
	nodeptr * p = nullptr;
	int i = 0;	
	while (p = *(leaf + i++));
	int nLen = i - 1;
	assert(index < nLen);
	p = *(leaf + index);
	return *p;
}