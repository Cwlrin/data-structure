#ifndef __SQ_BIN_TREE_NODE_H__
#define __SQ_BIN_TREE_NODE_H__

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType {EMPTY_NODE, USED_NODE};
#endif

// ˳��洢�����������ģ��
template <class ElemType>
struct SqBinTreeNode 
{
// ���ݳ�Ա:
	ElemType data;				// ���ݳ�Ա
	SqBinTreeNodeTagType tag;	// ���ʹ�ñ�־

// ���캯��ģ��:
	SqBinTreeNode();						// �޲����Ĺ��캯��ģ��
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE);	
		// ��֪���ݳ�Ա��ʹ�ñ�־�����ṹ
};

// ˳��洢�����������ģ���ʵ�ֲ���
template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode()
// �������������ָ���ԱΪ�յĽ��
{
   tag = EMPTY_NODE;			// ��һ���ս��
}

template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg)
// �������������һ�����ݳ�ԱΪitem�ͱ�־��ԱΪtg�Ľ��
{
   data = item;					// ���ݳ�Ա
   tag = tg;					// ��־��Ա
}

#endif
