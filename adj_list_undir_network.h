#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"							// ��������
#include "adj_list_network_edge.h"				// �ڽӱ���������������ģ��
#include "adj_list_network_vex_node.h"			// �ڽӱ�������������
#include "lk_queue.h"							// ������

// ���������ڽӱ���ģ��
template <class ElemType, class WeightType>
class AdjListUndirNetwork
{
protected:
// �ڽӱ�����ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	AdjListNetWorkVexNode<ElemType, WeightType> *vexTable;	// �����
	mutable bool *tag;							// ָ���־�����ָ��				
	WeightType infinity;						// �����

// ��������ģ��
	void DestroyHelp();							// ����������,�ͷ����������õĿռ�
	int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const;
		//��λ����v���ڽ������е�λ��
	void DFS(int v, void (*visit)(const ElemType &e)) const;// �Ӷ���v���������������������
	void BFS(int v, void (*visit)(const ElemType &)) const;	// �ӵڶ���v�������й������������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjListUndirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ���춥������Ϊes[],�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
	AdjListUndirNetwork(int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// ���춥�����ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
	~AdjListUndirNetwork();						// ��������ģ��
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// ��������������ȱ���
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// �������й�����ȱ���
	bool GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	bool SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	WeightType GetInfinity() const;				// ���������			 
	int GetVexNum() const;						// ���ض������			 
	int GetEdgeNum() const;						// ���ر�������			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2, WeightType w);	// ���붥��Ϊv1��v2,ȨΪw�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	WeightType GetWeight(int v1, int v2) const;	// ���ض���Ϊv1��v2�ıߵ�Ȩֵ
	void SetWeight(int v1, int v2, WeightType w);// ���ö���Ϊv1��v2�ıߵ�Ȩֵ
	bool GetTag(int v) const;					// ���ض���v�ı�־		 
	void SetTag(int v, bool val) const;			// ���ö���v�ı�־Ϊval		 
	AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy);	// ���ƹ��캯��ģ��
	AdjListUndirNetwork<ElemType, WeightType> &operator 
		=(const AdjListUndirNetwork<ElemType, WeightType> &copy); // ���ظ�ֵ�����
};

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net, bool showVexElem);	// ��ʾ�ڽӾ���������
template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net);						// ��ʾ�ڽӾ���������

// ���������ڽӱ���ģ���ʵ�ֲ���
template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
// ��ʼ������������
// ����������Ӷ���v���������������������
{	
	SetTag(v, true);						// �����ʱ�־
	ElemType e;								// ��ʱ����
	GetElem(v, e);							// ����v������Ԫ��
	(*visit)(e);							// ���ʶ���v������Ԫ��
	for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
// ��ʼ������������
// �����������������������ȱ���
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// ��ÿ�����������ʱ�־
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴DFS���������������
		if (!GetTag(v))	DFS(v, visit);
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
// ��ʼ������������
// ����������ӵڶ���v�������й������������
{	
	SetTag(v, true);						// �����ʱ�־
	ElemType e;								// ��ʱ����
	GetElem(v, e);							// ����v������Ԫ��
	(*visit)(e);							// ���ʶ���v������Ԫ��
	LinkQueue<int> q;						// �������
	q.InQueue(v);							// v���
	while (!q.Empty())
	{	// ����q�ǿ�, ����ѭ��
		int u, w;							// ��ʱ����
		q.OutQueue(u);						// ����
		for (w = FirstAdjVex(u); w >= 0; w = NextAdjVex(u, w))
		{	// ��u��δ���ʹ����ڽӶ���w���з���
			if (!GetTag(w))
			{	// ��w���з���
				SetTag(w, true);			// �����ʱ�־
				GetElem(w, e);				// ����w������Ԫ��
				(*visit)(e);				// ���ʶ���w������Ԫ��
				q.InQueue(w);				// w���
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
// ��ʼ������������
// ����������������й�����ȱ���
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// ��ÿ�����������ʱ�־
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴BFS���������������
		if (!GetTag(v)) BFS(v , visit); 
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(ElemType es[], int vertexNum, WeightType infinit)
// ������������춥������Ϊes[],�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";// �׳��쳣

	infinity = infinit;							// �����
	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new bool[vexNum];				// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����������
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(int vertexNum, WeightType infinit)
// ������������춥�����ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";// �׳��쳣

	infinity = infinit;							// �����
	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new bool[vexNum];				// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// �����ڽӱ�
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DestroyHelp()
// �������������������,�ͷ����������õĿռ�
{
	delete []tag;								// �ͷű�־
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ�����
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// �ͷ��ڽӱ�
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::~AdjListUndirNetwork()
// ����������ͷ��ڽӱ���������ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;				// Ԫ�ز�����
	}
	else
	{	// v�Ϸ�
		e = vexTable[v].data;		// ������v��Ԫ��ֵ����e
		return true;				// Ԫ�ش���
	}
}	

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;				// λ�ô�
	}
	else
	{	// v�Ϸ�
		vexTable[v].data = e;		// ����Ԫ��
		return true;				// �ɹ�
	}
}


template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetInfinity() const
// ������������������
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";// �׳��쳣

	if (vexTable[v].adjLink == NULL)
	{	// ���ڽ��������ڽӵ�
		return -1; 
	}
	else
	{	// ���ڽ����������ڽӵ�
		AdjListNetworkEdge<WeightType> tmpEdgeNode;
		vexTable[v].adjLink->GetElem(1, tmpEdgeNode);
		return tmpEdgeNode.adjVex;
	}
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const
// �����������λ����v���ڽ������е�λ��
{
	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos; 
	curPos = la->GetCurPosition();

	la->GetElem(curPos, tmpEdgeNode);				// ȡ���ڽӵ���Ϣ
	if (tmpEdgeNode.adjVex == v) return curPos;		// vΪ��������ĵ�ǰλ�ô� 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// ѭ������
		la->GetElem(curPos, tmpEdgeNode);			// ȡ�ñ���Ϣ
		if (tmpEdgeNode.adjVex == v) break;			// ��λ�ɹ�
	}
	
	return curPos;									// curPos = la.Length() + 1 ��ʧ��
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣
	
	if (vexTable[v1].adjLink == NULL) return -1;	// �ڽ�����vexTable[v1].adjLink,������,����-1

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// ȡ��v2���ڽ������е�λ��
	if (curPos < vexTable[v1].adjLink->Length())
	{	// ������1���ڽӵ�
		vexTable[v1].adjLink->GetElem(curPos + 1, tmpEdgeNode);// ȡ�����
		return tmpEdgeNode.adjVex;
	}
	else
	{	// ��������һ���ڽӵ�
		return -1;
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣
	if (w == infinity) throw "w����Ϊ�޿մ�!";		// �׳��쳣

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	// ����<v1, v2>
	if (vexTable[v1].adjLink == NULL)
	{	// ������
		vexTable[v1].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >;
	}
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// ȡ����
		tmpEdgeNode.weight = w;								// ������Ȩֵ
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);	// ���ñ�
	}
	else
	{	// �����ڱ�<v1, v2>
		tmpEdgeNode.adjVex = v2; tmpEdgeNode.weight = w;	// �����
		vexTable[v1].adjLink->Insert(curPos, tmpEdgeNode);	// ����<v1, v2>
		edgeNum++;											// ��������1
	}
	
	// ����<v2, v1>
	if (vexTable[v2].adjLink == NULL)
	{	// ������
		vexTable[v2].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >;
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// ȡ��v1���ڽ������е�λ��
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// ���ڱ�<v2, v1>
		vexTable[v2].adjLink->GetElem(curPos, tmpEdgeNode);	// ȡ����
		tmpEdgeNode.weight = w;								// ������Ȩֵ
		vexTable[v2].adjLink->SetElem(curPos, tmpEdgeNode);	// ���ñ�
	}
	else
	{	// �����ڱ�<v1, v2>
		tmpEdgeNode.adjVex = v1; tmpEdgeNode.weight = w;	// �����
		vexTable[v2].adjLink->Insert(curPos, tmpEdgeNode);	// ����<v2, v1>
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, tmpEdgeNode);	// ɾ��<v1, v2>
 		edgeNum--;											// �����Լ�1
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// ȡ��v1���ڽ������е�λ��
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// ���ڱ�<v2, v1>
		vexTable[v2].adjLink->Delete(curPos, tmpEdgeNode);	// ɾ��<v2, v1>
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// ȡ����
		return tmpEdgeNode.weight;							// ����Ȩֵ
	}
	else
	{	// �����ڱ�<v1, v2>
		return infinity;									// ȨֵΪinfinity��ʾ�߲�����
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣
	if (w == infinity) throw "w����Ϊ�޿մ�!";				// �׳��쳣

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// ȡ����
		tmpEdgeNode.weight = w;								// �޸�<v1, v2>Ȩֵ
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);	// ���ñ�
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// ȡ��v1���ڽ������е�λ��
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// ���ڱ�<v2, v1>
		vexTable[v2].adjLink->GetElem(curPos, tmpEdgeNode);	// ȡ����
		tmpEdgeNode.weight = w;								// �޸�<v2, v1>Ȩֵ
		vexTable[v2].adjLink->SetElem(curPos, tmpEdgeNode);	// ���ñ�
	}
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";				// �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";			// �׳��쳣

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy���������������ڽӾ���copy�������ƹ��캯��ģ��
{
	int curPos;									// ��ʱ����
	infinity =copy.infinity;					// ���������
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	tag = new bool[vexNum];				// ���ɱ�־����
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ���Ʊ�־����
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// �����ڽ�����
		vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
		vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType> &AdjListUndirNetwork<ElemType, WeightType>::operator =(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy��ֵ����ǰ���������ڽӾ��󡪡����ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp();								// �ͷŵ�ǰ������ռ�ÿռ�

		int curPos;									// ��ʱ����
		infinity =copy.infinity;					// ���������
		vexNum = copy.vexNum;						// ���ƶ�����
		edgeNum = copy.edgeNum;						// ���Ʊ���

		tag = new bool[vexNum];						// ���ɱ�־����
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// ���Ʊ�־����
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// �����ڽӱ�
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// �����ڽ�����
			vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
			vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net, bool showVexElem)
// �������: ��ʾ�ڽӾ���������
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";							// ��ʾ�����
		if (showVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;										// ����Ԫ��
			net.GetElem(v, e);								// ȡ��Ԫ��ֵ
			cout << e << "  ";								// ��ʾ����Ԫ��
		}

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")"; 
		}
		cout << endl; 
	}
}

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net)
// �������: ��ʾ�ڽӾ���������
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";							// ��ʾ�����
		ElemType e;											// ����Ԫ��
		net.GetElem(v, e);									// ȡ��Ԫ��ֵ
		cout << e << "  ";									// ��ʾ����Ԫ��

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")"; 
		}
		cout << endl; 
	}
}

#endif
