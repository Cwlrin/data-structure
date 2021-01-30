#ifndef __CHILD_PARENT_TREE_NODE_H__
#define __CHILD_PARENT_TREE_NODE_H__

#include "lk_list.h"				// 线性链表

// 孩子双法表示树结点类模板
template <class ElemType>
struct ChildParentTreeNode 
{
// 数据成员:
	ElemType data;					// 数据成员
	LinkList<int> childLkList;		// 孩子链表	
	int parent;						// 双亲位置成员

// 构造函数模板:
	ChildParentTreeNode();			// 无参数的构造函数模板
	ChildParentTreeNode(ElemType item, int pt = -1);// 已知数据成员值和双亲位置建立结构
};

// 孩子双法表示树结点类的实现部分
template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode()
// 操作结果：构造双亲成员为-1的结点
{
	parent = -1;
}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt)
// 操作结果：构造一个数据成员为item和双亲成员为pt的结点
{
	data = item;					// 数据元素值
	parent = pt;					// 双亲
}

#endif
