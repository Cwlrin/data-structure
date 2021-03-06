#ifndef __CRO_NODE_H__
#define __CRO_NODE_H__

#include "triple.h"						// 三元组类模板

// 十字链表三元组结点类模板
template<class ElemType>
struct CLkTriNode
{
// 数据成员:
	Triple<ElemType> triElem;				// 三元组
	CLkTriNode<ElemType> *right, *down;		// 非零元素所在行表与列表的后继指针成员

// 构造函数模板:
	CLkTriNode();							// 无参数的构造函数模板
	CLkTriNode(const Triple<ElemType> &e,	// 已知三元组和指针成员建立结点
		CLkTriNode<ElemType> *rLink = NULL, CLkTriNode<ElemType> *dLink = NULL);	
};

// 十字链表三元组结点类模板的实现部分
template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode()
// 操作结果：构造指针成员为空的结点
{
	right = NULL;						// 行指针成员为空
	down = NULL;						// 列指针成员为空
}

template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode(const Triple<ElemType> &e,
		CLkTriNode<ElemType> *rLink, CLkTriNode<ElemType> *dLink)
// 操作结果：已知三元组和指针成员建立结点
{
	triElem.row = e.row;						// 三元组
	triElem.col = e.col;						// 三元组
	triElem.value = e.value;						// 三元组
	right = rLink;						// 行指针成员
	down = dLink;						// 列指针成员
}

#endif
