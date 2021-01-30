#ifndef __SQ_BIN_TREE_NODE_H__
#define __SQ_BIN_TREE_NODE_H__

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType {EMPTY_NODE, USED_NODE};
#endif

// 顺序存储二叉树结点类模板
template <class ElemType>
struct SqBinTreeNode 
{
// 数据成员:
	ElemType data;				// 数据成员
	SqBinTreeNodeTagType tag;	// 结点使用标志

// 构造函数模板:
	SqBinTreeNode();						// 无参数的构造函数模板
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE);	
		// 已知数据成员和使用标志建立结构
};

// 顺序存储二叉树结点类模板的实现部分
template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode()
// 操作结果：构造指针成员为空的结点
{
   tag = EMPTY_NODE;			// 标一个空结点
}

template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg)
// 操作结果：构造一个数据成员为item和标志成员为tg的结点
{
   data = item;					// 数据成员
   tag = tg;					// 标志成员
}

#endif
