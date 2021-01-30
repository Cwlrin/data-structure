#ifndef __CHILD_SIBLING_FOREST_NODE_H__
#define __CHILD_SIBLING_FOREST_NODE_H__

// �����ֵܱ�ʾ�������ģ��
template <class ElemType>
struct ChildSiblingTreeNode 
{
// ���ݳ�Ա:
	ElemType data;								// ���ݳ�Ա
	ChildSiblingTreeNode<ElemType> *firstChild;	// ָ���׺���ָ���Ա
	ChildSiblingTreeNode<ElemType> *rightSibling;// ָ�����ֵ�ָ���Ա

// ���캯��ģ��:
	ChildSiblingTreeNode();						// �޲����Ĺ��캯��ģ��
	ChildSiblingTreeNode(ElemType item,			// ��֪���ݳ�Աֵ��ָ���׺��������ֵ�ָ�뽨�����
		ChildSiblingTreeNode<ElemType> *fChild = NULL,
		ChildSiblingTreeNode<ElemType> *rSibling = NULL);	
		
};

// �����ֵܱ�ʾ�������ģ���ʵ�ֲ���
template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode()
// �������������ָ���ԱΪ�յĽ��
{
	firstChild = rightSibling = NULL;			// ָ���׺��Ӽ��ֵܵ�ָ�붼Ϊ��
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType item,			// ��֪���ݳ�Աֵ��˫��λ�ý����ṹ
		ChildSiblingTreeNode<ElemType> *fChild,
		ChildSiblingTreeNode<ElemType> *rSibling)
// �������������һ�����ݳ�ԱΪitem���׺���ΪfChild�����ֵ�ΪrChild�Ľ��
{
	data = item;								// ����
	firstChild = fChild;						// �׺���
	rightSibling = rSibling;					// ���ֵ�
}

#endif
