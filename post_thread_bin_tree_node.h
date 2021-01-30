#ifndef __POST_THREAD_BIN_TREE_NODE_H__
#define __POST_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};	
	// ָ���־����,CHILD_PTR(0):ָ���ӵ�ָ��,THREAD_PTR(1):ָ��������ָ��
#endif

// �������������������ģ��
template <class ElemType>
struct PostThreadBinTreeNode
{
// ���ݳ�Ա:
	ElemType data;								// ���ݳ�Ա
	PostThreadBinTreeNode<ElemType> *leftChild;	// ����ָ���Ա
	PostThreadBinTreeNode<ElemType> *rightChild;// �Һ���ָ���Ա
	PostThreadBinTreeNode<ElemType> *parent;	// ˫��ָ���Ա
	PointerTagType leftTag, rightTag;			// ���ұ��Ա��Ա

//	���캯��ģ��:
	PostThreadBinTreeNode();					// �޲����Ĺ��캯�� ģ��
	PostThreadBinTreeNode(const ElemType &val,	// ������Ԫ��ֵ,ָ�뼰��־��Ա������
		PostThreadBinTreeNode<ElemType> *lChild = NULL, 
		PostThreadBinTreeNode<ElemType> *rChild = NULL,
		PostThreadBinTreeNode<ElemType> *pt = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// �������������������ģ���ʵ�ֲ���
template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = parent = NULL;		// ָ���ԱΪ��
	leftTag = rightTag = CHILD_PTR;				// ��־��Ա
}

template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode(const ElemType &val, 
		PostThreadBinTreeNode<ElemType> *lChild, 
		PostThreadBinTreeNode<ElemType> *rChild,
		PostThreadBinTreeNode<ElemType> *pt,
		PointerTagType lTag,
		PointerTagType rTag)
// �������������һ�����ݳ�ԱΪval,����ΪlChild,�Һ���ΪrChild�Ľ��,˫��Ϊ
//	pt,���־ΪlTag,�ұ�־ΪrTag�Ľ��
{	
	data = val;									// ����Ԫ��ֵ
	leftChild = lChild;							// ����
	rightChild = rChild;						// �Һ���
	parent = pt;								// ˫��
	leftTag = lTag;								// ���־
	rightTag = rTag;							// �ұ�־
}

#endif

