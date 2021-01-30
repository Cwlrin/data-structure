#ifndef __TRI_LK_BIN_TREE_NODE_H__
#define __TRI_LK_BIN_TREE_NODE_H__

// ������������������ģ��
template <class ElemType>
struct TriLkBinTreeNode
{
// ���ݳ�Ա:
	ElemType data;							// ���ݳ�Ա
	TriLkBinTreeNode<ElemType>  *leftChild;	// ����ָ���Ա
	TriLkBinTreeNode<ElemType>  *rightChild;// �Һ���ָ���Ա
	TriLkBinTreeNode<ElemType>  *parent;	// ˫��ָ���Ա

//	���캯��ģ��:
	TriLkBinTreeNode();						// �޲����Ĺ��캯�� ģ��
	TriLkBinTreeNode(const ElemType &val,	// ������Ԫ��ֵ,ָ�����Һ��Ӽ�˫�׵�ָ�빹����
		TriLkBinTreeNode<ElemType> *lChild = NULL, 
		TriLkBinTreeNode<ElemType> *rChild = NULL,
		TriLkBinTreeNode<ElemType> *pt = NULL);
};

// �����������ģ���ʵ�ֲ���
template <class ElemType>
TriLkBinTreeNode<ElemType>::TriLkBinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = NULL;			// Ҷ������Һ���Ϊ��
}

template <class ElemType>
TriLkBinTreeNode<ElemType>::TriLkBinTreeNode(const ElemType &val, 
	TriLkBinTreeNode<ElemType> *lChild, 
	TriLkBinTreeNode<ElemType> *rChild,
	TriLkBinTreeNode<ElemType> *pt)
// �������������һ�����ݳ�ԱΪval,˫��Ϊpt,����ΪlChild,�Һ���ΪrChild�Ľ��
{	
	data = val;								// ����Ԫ��ֵ
	leftChild = lChild;						// ����
	rightChild = rChild;					// �Һ���
	parent = pt;							// ˫��
}

#endif

