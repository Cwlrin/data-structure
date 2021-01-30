#ifndef __ADJ_MATRIX_DIR_GRAPH_H__
#define __ADJ_MATRIX_DIR_GRAPH_H__

#include "lk_queue.h"							// ������

// ���������ڽӾ�����ģ��
template <class ElemType, class WeightType>
class AdjMatrixDirNetwork
{
protected:
// �ڽӾ�������ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	WeightType **Matrix;						// �ڽӾ���
	ElemType *elems;							// ��������
	mutable bool *tag;							// ָ���־�����ָ��
	WeightType infinity;						// �����

// ��������ģ��:
	void DestroyHelp();							// ����������,�ͷ�������ռ�õĿռ�
	void DFS(int v, void (*visit)(const ElemType &e)) const;// �Ӷ���v���������������������
	void BFS(int v, void (*visit)(const ElemType &)) const;	// �ӵڶ���v�������й������������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjMatrixDirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);	
		// ��������Ԫ��es[],�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
	AdjMatrixDirNetwork(int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = DEFAULT_INFINITY);	
		// ���춥�����ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
	~AdjMatrixDirNetwork();						// ��������ģ��
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
	bool GetTag(int v) const;			// ���ض���v�ı�־		 
	void SetTag(int v, bool val) const;	// ���ö���v�ı�־Ϊval		 
	AdjMatrixDirNetwork(const AdjMatrixDirNetwork<ElemType, WeightType> &copy);	
		// ���ƹ��캯��ģ��
	AdjMatrixDirNetwork<ElemType, WeightType> &operator =
		(const AdjMatrixDirNetwork<ElemType, WeightType> &copy); // ���ظ�ֵ�����
};

template <class ElemType, class WeightType>
void Display(const AdjMatrixDirNetwork<ElemType, WeightType> &g, bool showVexElem);// ��ʾ�ڽӾ���������
template <class ElemType, class WeightType>
void Display(const AdjMatrixDirNetwork<ElemType, WeightType> &g);					// ��ʾ�ڽӾ���������


// ���������ڽӾ�����ģ���ʵ�ֲ���
template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
// ��ʼ������������
// ����������Ӷ���v���������������������
{	
	SetTag(v, true);						// �����ʱ�־
	ElemType e;								// ��ʱ����
	GetElem(v, e);							// ����v������Ԫ��
	visit(e);								// ���ʶ���v������Ԫ��
	for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
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
void AdjMatrixDirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
// ��ʼ������������
// ����������ӵڶ���v�������й������������
{	
	SetTag(v, true);						// �����ʱ�־
	ElemType e;								// ��ʱ����
	GetElem(v, e);							// ����v������Ԫ��
	visit(e);								// ���ʶ���v������Ԫ��
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
				visit(e);					// ���ʶ���w������Ԫ��
				q.InQueue(w);				// w���
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
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
AdjMatrixDirNetwork<ElemType, WeightType>::AdjMatrixDirNetwork(ElemType es[], int vertexNum, WeightType infinit)
// ������������춥������Ϊes[],�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";	// �׳��쳣

	infinity = infinit;								// �����
	vexNum = vertexNum;								// ������ΪvertexNum
	edgeNum = 0;									// ����Ϊ0

	elems = new ElemType[vexNum];				// ���ɶ������ݱ�����
	
	int u, v;									// ��ʱ���� 
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		elems[v] = es[v];
	}

	tag = new bool[vexNum];					// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = false;
	}

	Matrix = (WeightType **)new WeightType *[vexNum];// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new WeightType[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = infinity;
		}
	}
}

template <class ElemType, class WeightType>
AdjMatrixDirNetwork<ElemType, WeightType>::AdjMatrixDirNetwork(int vertexNum, WeightType infinit)
// ������������춥�����ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";	// �׳��쳣

	infinity = infinit;								// �����
	vexNum = vertexNum;								// ������ΪvertexNum
	edgeNum = 0;									// ����Ϊ0

	elems = new ElemType[vexNum];					// ���ɶ������ݱ�����
	
	int u, v;										// ��ʱ���� 
	tag = new bool[vexNum];					// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = false;
	}

	Matrix = (WeightType **)new WeightType *[vexNum];// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new WeightType[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = infinity;
		}
	}
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::DestroyHelp()
// �������������������,�ͷ�������ռ�õĿռ�
{
	delete []elems;										// �ͷŶ�������
	delete []tag;										// �ͷű�־

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;									// �ͷ��ڽӾ���
}

template <class ElemType, class WeightType>
AdjMatrixDirNetwork<ElemType, WeightType>::~AdjMatrixDirNetwork()
// ����������ͷŶ�����ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType, class WeightType>
bool AdjMatrixDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;	// Ԫ�ز�����
	}
	else
	{	// v�Ϸ�
		e = elems[v];		// ������v��Ԫ��ֵ����e
		return true;	// Ԫ�ش���
	}
}	

template <class ElemType, class WeightType>
bool AdjMatrixDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	true, ���򷵻�false
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return false;	// λ�ô�
	}
	else
	{	// v�Ϸ�
		elems[v] = e;		// ����Ԫ��
		return true;		// �ɹ�
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixDirNetwork<ElemType, WeightType>::GetInfinity() const
// ������������������
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixDirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixDirNetwork<ElemType, WeightType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjMatrixDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";		// �׳��쳣

	for (int cur = 0; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v][cur] != infinity) return cur;
	}

	return -1;										// ����-1��ʾ���ڽӵ�
}

template <class ElemType, class WeightType>
int AdjMatrixDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����1���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣

	for (int cur = v2 + 1; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v1][cur] != infinity) return cur;
	}

	return -1;												// ����-1��ʾ���ڽӵ�
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣
	if (w == infinity) throw "w����Ϊ�޿մ�!";				// �׳��쳣

	if (Matrix[v1][v2] == infinity)
	{	// ԭ�������ޱ�<v1, v2>,������������1
		edgeNum++;
	}
	Matrix[v1][v2] = w;										// �޸ıߵ�Ȩֵ
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣

	if (Matrix[v1][v2] != infinity)
	{	// ԭ���������ڱ�<v1, v2>,ɾ��������Լ�1
		edgeNum--;
	}
	Matrix[v1][v2] = infinity;								// �޸ıߵ�Ȩֵ
}

template <class ElemType, class WeightType>
WeightType AdjMatrixDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣

	return Matrix[v1][v2];
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";			// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";			// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";					// �׳��쳣
	if (w == infinity) throw "w����Ϊ�޿մ�!";				// �׳��쳣

	Matrix[v1][v2] = w;									// �޸ıߵ�Ȩֵ
}

template <class ElemType, class WeightType>
bool AdjMatrixDirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";			// �׳��쳣

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixDirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const 
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";			// �׳��쳣

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixDirNetwork<ElemType, WeightType>::AdjMatrixDirNetwork(const AdjMatrixDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy���������������ڽӾ���copy�������ƹ��캯��ģ��
{
	int iPos, jPos;								// ��ʱ����
	infinity =copy.infinity;					// ���������
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	elems = new ElemType[vexNum];			// ���ɶ�����������
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���ƶ�����������
		elems[iPos] = copy.elems[iPos];
	}

	tag = new bool[vexNum];				// ���ɱ�־����
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���Ʊ�־����
		tag[iPos] = copy.tag[iPos];
	}

	Matrix = (WeightType **)new WeightType *[vexNum];	// �����ڽӾ���
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new WeightType[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (jPos = 0; jPos < vexNum; jPos++)
		{	// �����ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
		}
	}
}

template <class ElemType, class WeightType>
AdjMatrixDirNetwork<ElemType, WeightType> &AdjMatrixDirNetwork<ElemType, WeightType>::operator =(const AdjMatrixDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy��ֵ����ǰ���������ڽӾ��󡪡����ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp();						// �ͷŵ�ǰ������ռ�ÿռ�
		int iPos, jPos;						// ��ʱ����
		infinity =copy.infinity;			// ���������
		vexNum = copy.vexNum;				// ���ƶ�����
		edgeNum = copy.edgeNum;				// ���Ʊ���

		elems = new ElemType[vexNum];	// ���ɶ�����������
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���ƶ�����������
			elems[iPos] = copy.elems[iPos];
		}

		tag = new bool[vexNum];		// ���ɱ�־����
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���Ʊ�־����
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (WeightType **)new WeightType*[vexNum];// �����ڽӾ���
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// �����ڽӾ������
			Matrix[iPos] = new WeightType[vexNum];	
		}

		for (iPos = 0; iPos < vexNum; iPos++)
		{
			for (jPos = 0; jPos < vexNum; jPos++)
			{	// �����ڽӾ���Ԫ�ظ�ֵ
				Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
			}
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjMatrixDirNetwork<ElemType, WeightType> &net, bool showVexElem)
// �������: ��ʾ�ڽӾ���������
{
	WeightType infinity = net.GetInfinity();		// �����

	for (int iPos = 0; iPos < net.GetVexNum(); iPos++)
	{	// ��ʾ��
		if (showVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;								// ����Ԫ��
			net.GetElem(iPos, e);					// ȡ��Ԫ��ֵ
			cout << e;								// ��ʾԪ��
		}

		for (int jPos = 0; jPos < net.GetVexNum(); jPos++)
		{	// ��ʾԪ��
			if (net.GetWeight(iPos, jPos) == infinity)
			{	// ��ʾ�����
				cout << "\t" << "��";
			}
			else
			{	// ��ʾһ��Ȩֵ
				cout << "\t" << net.GetWeight(iPos, jPos);
			}
		}
		cout << endl;								// ���� 
	}
}

template <class ElemType, class WeightType>
void Display(const AdjMatrixDirNetwork<ElemType, WeightType> &net)
// �������: ��ʾ�ڽӾ���������
{
	WeightType infinity = net.GetInfinity();		// �����

	for (int iPos = 0; iPos < net.GetVexNum(); iPos++)
	{	// ��ʾ��
		ElemType e;									// ����Ԫ��
		net.GetElem(iPos, e);						// ȡ��Ԫ��ֵ
		cout << e;									// ��ʾԪ��

		for (int jPos = 0; jPos < net.GetVexNum(); jPos++)
		{	// ��ʾԪ��
			if (net.GetWeight(iPos, jPos) == infinity)
			{	// ��ʾ�����
				cout << "\t" << "��";
			}
			else
			{	// ��ʾһ��Ȩֵ
				cout << "\t" << net.GetWeight(iPos, jPos);
			}
		}
		cout << endl;								// ���� 
	}
}

#endif
