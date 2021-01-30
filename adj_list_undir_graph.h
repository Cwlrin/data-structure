#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"							// ��������
#include "adj_list_graph_vex_node.h"			// �ڽӱ�����ͼ��������ģ��
#include "lk_queue.h"							// ������

// ����ͼ���ڽӱ���ģ��
template <class ElemType>
class AdjListUndirGraph
{
protected:
// �ڽӱ�����ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	AdjListGraphVexNode<ElemType> *vexTable;	// �����
	mutable bool *tag;							// ָ���־�����ָ��				

// ��������ģ��
	void DestroyHelp();							// ��������ͼ,�ͷ�����ͼ���õĿռ�
	int IndexHelp(const LinkList<int> *la, int v) const;
		//��λ����v���ڽ������е�λ��
	void DFS(int v, void (*visit)(const ElemType &e)) const;// �Ӷ���v�������������������ͼ
	void BFS(int v, void (*visit)(const ElemType &)) const;	// �ӵڶ���v�������й����������ͼ

public:
// �����������ͷ�������ģ�弰���ر���ϵͳĬ�Ϸ�������ģ��:
	AdjListUndirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);
		// ���춥������Ϊes[],�������ΪvertexNum,infinit��ʾ�����,����Ϊ0������ͼ
	AdjListUndirGraph(int vertexNum = DEFAULT_SIZE);
		// ���춥�����ΪvertexNum,infinit��ʾ�����,����Ϊ0������ͼ
	~AdjListUndirGraph();						// ��������ģ��
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// ��ͼ����������ȱ���
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// ��ͼ���й�����ȱ���
	bool GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	bool SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	ElemType GetInfility() const;				// ���������			 
	int GetVexNum() const;						// ���ض������			 
	int GetEdgeNum() const;						// ���ر�������			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	bool GetTag(int v) const;				// ���ض���v�ı�־		 
	void SetTag(int v, bool val) const;	// ���ö���v�ı�־Ϊval		 
	AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy);	// ���ƹ��캯��ģ��
	AdjListUndirGraph<ElemType> &operator =(const AdjListUndirGraph<ElemType> &copy); // ���ظ�ֵ�����
};

template <class ElemType>
void Display(const AdjListUndirGraph<ElemType> &g, bool showVexElem);	// ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void Display(const AdjListUndirGraph<ElemType> &g);						// ��ʾ�ڽӾ�������ͼ

// ����ͼ���ڽӱ���ģ���ʵ�ֲ���
template <class ElemType>
void AdjListUndirGraph<ElemType>::DFS(int v, void (*visit)(const ElemType &e)) const
// ��ʼ����������ͼ
// ����������Ӷ���v�������������������ͼ
{	
	SetTag(v, true);						// �����ʱ�־
	ElemType e;								// ��ʱ����
	GetElem(v, e);							// ����v������Ԫ��
	(*visit)(e);							// ���ʶ���v������Ԫ��
	for (int w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType>
void AdjListUndirGraph<ElemType>::DFSTraverse(void (*visit)(const ElemType &e)) const
// ��ʼ����������ͼ
// �����������ͼ����������ȱ���
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

template <class ElemType>
void AdjListUndirGraph<ElemType>::BFS(int v, void (*visit)(const ElemType &)) const
// ��ʼ����������ͼ
// ����������ӵڶ���v�������й����������ͼ
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

template <class ElemType>
void AdjListUndirGraph<ElemType>::BFSTraverse(void (*visit)(const ElemType &)) const
// ��ʼ����������ͼ
// �����������ͼ���й�����ȱ���
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

template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(ElemType es[], int vertexNum)
// ������������춥����ΪnumVex,��������Ϊes[],�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new bool[vexNum];						// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = false;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����������
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(int vertexNum)
// ������������춥����ΪnumVex,�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new bool[vexNum];						// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = false;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
}

template <class ElemType>
void AdjListUndirGraph<ElemType>::DestroyHelp()
// �����������������ͼ,�ͷ�����ͼ���õĿռ�
{
	delete []tag;								// �ͷű�־
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ�����
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// �ͷ��ڽӱ�
}

template <class ElemType>
AdjListUndirGraph<ElemType>::~AdjListUndirGraph()
// ����������ͷ��ڽӱ�����ͼ��ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType>
bool AdjListUndirGraph<ElemType>::GetElem(int v, ElemType &e) const
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

template <class ElemType>
bool AdjListUndirGraph<ElemType>::SetElem(int v, const ElemType &e)
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

template <class ElemType>
int AdjListUndirGraph<ElemType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType>
int AdjListUndirGraph<ElemType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType>
int AdjListUndirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";// �׳��쳣

	if (vexTable[v].adjLink == NULL)
	{	// ���ڽ��������ڽӵ�
		return -1; 
	}
	else
	{	// �ǿ��ڽ����������ڽӵ�
		int adjVex;
		vexTable[v].adjLink->GetElem(1, adjVex);
		return adjVex;
	}
}

template <class ElemType>
int AdjListUndirGraph<ElemType>::IndexHelp(const LinkList<int> *la, int v) const
// �����������λ����v���ڽ������е�λ��
{
	int curPos, adjVex;
	curPos = la->GetCurPosition();

	la->GetElem(curPos, adjVex);					// ȡ���ڽӵ���Ϣ
	if (adjVex == v) return curPos;					// vΪ��������ĵ�ǰλ�ô� 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// ѭ������
		la->GetElem(curPos, adjVex);				// ȡ�ñ���Ϣ
		if (adjVex == v) break;						// ��λ�ɹ�
	}
	
	return curPos;									// curPos = la.Length() + 1 ��ʧ��
}

template <class ElemType>
int AdjListUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣
	
	if (vexTable[v1].adjLink == NULL) return -1;			// �ڽ�����vexTable[v1].adjListΪ��,����-1

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos < vexTable[v1].adjLink->Length())
	{	// ������1���ڽӵ�
		int adjVex;
		vexTable[v1].adjLink->GetElem(curPos + 1, adjVex);	// ȡ�����
		return adjVex;
	}
	else
	{	// ��������һ���ڽӵ�
		return -1;
	}
}

template <class ElemType>
void AdjListUndirGraph<ElemType>::InsertEdge(int v1, int v2)
// ������������붥��Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣

	// ����<v1, v2>
	if (vexTable[v1].adjLink == NULL)
	{	// ������
		vexTable[v1].adjLink = new LinkList<int>;
	}
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);			// ȡ��v2���ڽ������е�λ��
	if (curPos > vexTable[v1].adjLink->Length())
	{	// �����ڱ�<v1, v2>
		vexTable[v1].adjLink->Insert(curPos, v2);				// �����
		edgeNum++;											// ��������1
	}
	
	// ����<v2, v1>
	if (vexTable[v2].adjLink == NULL)
	{	// ������
		vexTable[v2].adjLink = new LinkList<int>;
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);				// ȡ��v1���ڽ������е�λ��
	if (curPos > vexTable[v2].adjLink->Length())
	{	// �����ڱ�<v1, v2>
		vexTable[v2].adjLink->Insert(curPos, v1);				// �����
	}
}

template <class ElemType>
void AdjListUndirGraph<ElemType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";		// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";		// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";				// �׳��쳣

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, v2);		// ɾ��<v1, v2>
 		edgeNum--;										// �����Լ�1
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);		// ȡ��v1���ڽ������е�λ��
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// ���ڱ�<v2, v1>
		vexTable[v2].adjLink->Delete(curPos, v1);		// ɾ��<v2, v1>
	}
}

template <class ElemType>
bool AdjListUndirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";			// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjListUndirGraph<ElemType>::SetTag(int v, bool val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";			// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjListUndirGraph<ElemType>::AdjListUndirGraph(const AdjListUndirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy����������ͼ���ڽӾ���copy�������ƹ��캯��ģ��
{
	int curPos;									// ��ʱ����
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	tag = new bool[vexNum];				// ���ɱ�־����
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ���Ʊ�־����
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// �����ڽ�����
		vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
		vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType>
AdjListUndirGraph<ElemType> &AdjListUndirGraph<ElemType>::operator =(const AdjListUndirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy��ֵ����ǰ����ͼ���ڽӾ��󡪡����ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp();								// �ͷŵ�ǰ����ͼռ�ÿռ�

		int curPos;									// ��ʱ����
		vexNum = copy.vexNum;						// ���ƶ�����
		edgeNum = copy.edgeNum;						// ���Ʊ���

		tag = new bool[vexNum];						// ���ɱ�־����
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// ���Ʊ�־����
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// �����ڽ�����
			vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
			vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType>
void Display(const AdjListUndirGraph<ElemType> &g, bool showVexElem)
// �������: ��ʾ�ڽӾ�������ͼ
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";							// ��ʾ�����
		if (showVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;										// ����Ԫ��
			g.GetElem(v, e);								// ȡ��Ԫ��ֵ
			cout << e << "  ";								// ��ʾ����Ԫ��
		}

		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->" << u; 
		}
		cout << endl; 
	}
}

template <class ElemType>
void Display(const AdjListUndirGraph<ElemType> &g)
// �������: ��ʾ�ڽӾ�������ͼ
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";							// ��ʾ�����
		ElemType e;											// ����Ԫ��
		g.GetElem(v, e);									// ȡ��Ԫ��ֵ
		cout << e << "  ";									// ��ʾ����Ԫ��

		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->" << u; 
		}
		cout << endl; 
	}
}

#endif
