#ifndef __PARENT_TREE_NODE_H__
#define __PARENT_TREE_NODE_H__

// 双法表示树结点类模板
template <class ElemType>
struct ParentTreeNode 
{
// 数据成员:
	ElemType data;									// 数据成员
	int parent;										// 双亲位置成员

// 构造函数模板:
	ParentTreeNode();								// 无参数的构造函数模板
	ParentTreeNode(ElemType item, int pt = -1);		// 已知数据成员值和双亲位置建立结点
};

// 双法表示树结点类模板的实现部分
template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode()
// 操作结果：构造双亲成员为-1的结点
{
	parent = -1;
}

template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode(ElemType item, int pt)
// 操作结果：构造一个数据成员为item和双亲成员为pt的结点
{
	data = item;
	parent = pt;
}

#endif
