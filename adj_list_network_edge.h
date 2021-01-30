#ifndef __ADJ_LIST_NETWORK_EDGE_H__
#define __ADJ_LIST_NETWORK_EDGE_H__

// �ڽӱ�����������ģ��
template <class WeightType>
class AdjListNetworkEdge
{
public:
// ���ݳ�Ա:
	int adjVex;								// �ڽӵ�
	WeightType weight;						// Ȩֵ

// ���캯��ģ��ģ��:
	AdjListNetworkEdge();						// �޲����Ĺ��캯��
	AdjListNetworkEdge(int v, WeightType w);	// �����ڽӵ�Ϊv��ȨΪw���ڽӱ�
};

// �ڽӱ�����������ģ���ʵ�ֲ���
template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge()
// �������������һ�����ڽӱ�߽��ߡ����޲ι��캯��ģ��
{
	adjVex = -1;
}

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge(int v, WeightType w)
// ��������������ڽӵ�Ϊv��ȨΪw���ڽӱ�
{
	adjVex = v;								// �ڽӵ�
	weight = w;								// Ȩ
}

#endif