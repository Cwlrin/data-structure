#ifndef __IN_THREAD_BIN_TREE_NODE_H__
#define __IN_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};
	// ָ���־����,CHILD_PTR(0):ָ���ӵ�ָ��,THREAD_PTR(1):ָ��������ָ��
#endif

// ���������������ģ��
template <class ElemType>
struct ThreadBinTreeNode
{
// ���ݳ�Ա:
	ElemType data;							// ���ݳ�Ա
	ThreadBinTreeNode<ElemType> *leftChild;	// ����ָ���Ա
	ThreadBinTreeNode<ElemType> *rightChild;// �Һ���ָ���Ա
	PointerTagType leftTag, rightTag;		// ���ұ�־��Ա

//	���캯��ģ��:
	ThreadBinTreeNode();					// �޲����Ĺ��캯�� ģ��
	ThreadBinTreeNode(const ElemType &val,	// ������Ԫ��ֵ,ָ�뼰��־��Ա������
		ThreadBinTreeNode<ElemType> *lChild = NULL, 
		ThreadBinTreeNode<ElemType> *rChild = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// ���������������ģ���ʵ�ֲ���
template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = NULL;			// ָ���ԱΪ��
	leftTag = rightTag = CHILD_PTR;			// ��־��Ա
}

template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode(const ElemType &val, 
		ThreadBinTreeNode<ElemType> *lChild, 
		ThreadBinTreeNode<ElemType> *rChild,
		PointerTagType lTag,
		PointerTagType rTag)
// �������������һ�����ݳ�ԱΪval,����ΪlChild,�Һ���ΪrChild�Ľ��,���
//	־ΪlTag,�ұ�־ΪrTag�Ľ��
{	
	data = val;								// ����Ԫ��ֵ
	leftChild = lChild;						// ����
	rightChild = rChild;					// �Һ���
	leftTag = lTag;							// ���־
	rightTag = rTag;						// �ұ�־
}

#endif

