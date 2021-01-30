#ifndef __CHILD_PARENT_TREE_NODE_H__
#define __CHILD_PARENT_TREE_NODE_H__

#include "lk_list.h"				// ��������

// ����˫����ʾ�������ģ��
template <class ElemType>
struct ChildParentTreeNode 
{
// ���ݳ�Ա:
	ElemType data;					// ���ݳ�Ա
	LinkList<int> childLkList;		// ��������	
	int parent;						// ˫��λ�ó�Ա

// ���캯��ģ��:
	ChildParentTreeNode();			// �޲����Ĺ��캯��ģ��
	ChildParentTreeNode(ElemType item, int pt = -1);// ��֪���ݳ�Աֵ��˫��λ�ý����ṹ
};

// ����˫����ʾ��������ʵ�ֲ���
template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode()
// �������������˫�׳�ԱΪ-1�Ľ��
{
	parent = -1;
}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt)
// �������������һ�����ݳ�ԱΪitem��˫�׳�ԱΪpt�Ľ��
{
	data = item;					// ����Ԫ��ֵ
	parent = pt;					// ˫��
}

#endif
