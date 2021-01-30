#ifndef __CRO_NODE_H__
#define __CRO_NODE_H__

#include "triple.h"						// ��Ԫ����ģ��

// ʮ��������Ԫ������ģ��
template<class ElemType>
struct CLkTriNode
{
// ���ݳ�Ա:
	Triple<ElemType> triElem;				// ��Ԫ��
	CLkTriNode<ElemType> *right, *down;		// ����Ԫ�������б����б�ĺ��ָ���Ա

// ���캯��ģ��:
	CLkTriNode();							// �޲����Ĺ��캯��ģ��
	CLkTriNode(const Triple<ElemType> &e,	// ��֪��Ԫ���ָ���Ա�������
		CLkTriNode<ElemType> *rLink = NULL, CLkTriNode<ElemType> *dLink = NULL);	
};

// ʮ��������Ԫ������ģ���ʵ�ֲ���
template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode()
// �������������ָ���ԱΪ�յĽ��
{
	right = NULL;						// ��ָ���ԱΪ��
	down = NULL;						// ��ָ���ԱΪ��
}

template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode(const Triple<ElemType> &e,
		CLkTriNode<ElemType> *rLink, CLkTriNode<ElemType> *dLink)
// �����������֪��Ԫ���ָ���Ա�������
{
	triElem.row = e.row;						// ��Ԫ��
	triElem.col = e.col;						// ��Ԫ��
	triElem.value = e.value;						// ��Ԫ��
	right = rLink;						// ��ָ���Ա
	down = dLink;						// ��ָ���Ա
}

#endif
