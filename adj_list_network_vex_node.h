#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__

#include "adj_list_network_edge.h"			// �ڽӱ�����������ģ��

// �ڽӱ�����������ģ��
template <class ElemType, class WeightType>
class AdjListNetWorkVexNode
{
public:
// ���ݳ�Ա:
	ElemType data;							// ����Ԫ��ֵ
	LinkList<AdjListNetworkEdge<WeightType> > *adjLink;
		// ָ���ڽ������ָ��

// ���캯��ģ��:
	AdjListNetWorkVexNode();				// �޲����Ĺ��캯��ģ��
	AdjListNetWorkVexNode(ElemType item, 
		LinkList<AdjListNetworkEdge<WeightType> > *adj = NULL);
		// ���춥������Ϊitem,ָ���ڽ������ָ��Ϊadj�Ľṹ
};

// �ڽӱ�����������ģ���ʵ�ֲ���
template <class ElemType, class WeightType>
AdjListNetWorkVexNode<ElemType, WeightType>::AdjListNetWorkVexNode()
// �������������һ���ն����㡪���޲ι��캯��
{
	adjLink = NULL;							// ָ���ڽ������ָ��Ϊ��
}

template <class ElemType, class WeightType>
AdjListNetWorkVexNode<ElemType, WeightType>::AdjListNetWorkVexNode(ElemType item, 
	LinkList<AdjListNetworkEdge<WeightType> > *adj)
// �����������������Ϊitem,��Ϊeg�Ķ���
{
	data = item;							// ��������
	adjLink = adj;							// ָ���ڽ������ָ��
}

#endif