#ifndef __ADJ_MATRIX_DIR_GRAPH_H__
#define __ADJ_MATRIX_DIR_GRAPH_H__

#include "lk_queue.h"							// ������

// ����ͼ���ڽӾ�����ģ��
template <class ElemType>
class AdjMatrixDirGraph 
{
protected:
// �ڽӾ�������ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	int **Matrix;								// �ڽӾ���
	ElemType *elems;							// ����Ԫ��
	mutable bool *tag;							// ָ���־�����ָ��

// ��������ģ��
	void DestroyHelp();							// ��������ͼ,�ͷ�����ͼռ�õĿռ�
	void DFS(int v, void (*visit)(const ElemType &e)) const;	// �Ӷ���v�������������������ͼ
	void BFS(int v, void (*visit)(const ElemType &)) const;	// �ӵڶ���v�������й����������ͼ

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);	
		// ��������Ԫ��es[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);	
		// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjMatrixDirGraph();						// ��������ģ��
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// ��ͼ����������ȱ���
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// ��ͼ���й�����ȱ���
	bool GetElem(int v, ElemType &e) const;		// �󶥵��Ԫ��	
	bool SetElem(int v, const ElemType &e);		// ���ö����Ԫ��ֵ
	int GetVexNum() const;						// ���ض������			 
	int GetEdgeNum() const;						// ���ر�������			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	bool GetTag(int v) const;					// ���ض���v�ı�־		 
	void SetTag(int v, bool val) const;			// ���ö���v�ı�־Ϊval		 
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy);	// ���ƹ��캯��ģ��
	AdjMatrixDirGraph<ElemType> &operator =(const AdjMatrixDirGraph<ElemType> &copy); 
		// ���ظ�ֵ�����
}; 

template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool DisplayVexElem);// ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g);						// ��ʾ�ڽӾ�������ͼ


// ����ͼ���ڽӾ�����ģ���ʵ�ֲ���
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFS(int v, void (*visit)(const ElemType &e)) const
// ��ʼ����������ͼ
// ����������Ӷ���v�������������������ͼ
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

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFSTraverse(void (*visit)(const ElemType &e)) const
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
void AdjMatrixDirGraph<ElemType>::BFS(int v, void (*visit)(const ElemType &)) const
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
void AdjMatrixDirGraph<ElemType>::BFSTraverse(void (*visit)(const ElemType &)) const
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
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType es[], int vertexNum)
// �����������������Ԫ��es[],�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0) throw "�����������Ϊ��!";// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	elems = new ElemType[vexNum];				// ���ɶ���Ԫ�ر�����
	
	int u, v;									// ��ʱ���� 
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ������Ԫ��
		elems[v] = es[v];
	}

	tag = new bool[vexNum];						// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = false;
	}

	Matrix = (int **)new int *[vexNum];			// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum)
// ������������춥�����ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw "�����������Ϊ��!";// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	elems = new ElemType[vexNum];				// ���ɶ���Ԫ�ر�����

	int u, v;									// ��ʱ���� 
	tag = new bool[vexNum];						// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = false;
	}

	Matrix = (int **)new int *[vexNum];			// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyHelp()
// �����������������ͼ,�ͷ�����ͼռ�õĿռ�
{
	delete []elems;								// �ͷ�Ԫ��
	delete []tag;								// �ͷű�־

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;							// �ͷ��ڽӾ���
}

template <class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph()
// ����������ͷŶ�����ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::GetElem(int v, ElemType &e) const
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

template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::SetElem(int v, const ElemType &e)
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

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";		// �׳��쳣

	for (int cur = 0; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v][cur] != 0) return cur;
	}

	return -1;										// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
int AdjMatrixDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����1���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣

	for (int cur = v2 + 1; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v1][cur] != 0) return cur;
	}

	return -1;									// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::InsertEdge(int v1, int v2)
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣

	if (Matrix[v1][v2] == 0)
	{	// ԭ����ͼ�ޱ�<v1, v2>,������������1
		edgeNum++;
	}
	Matrix[v1][v2] = 1;					// �޸�<v1, v2>��Ӧ���ڽӾ���Ԫ��ֵ
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";	// �׳��쳣
	if (v1 == v2) throw "v1���ܵ���v2!";			// �׳��쳣

	if (Matrix[v1][v2] != 0)
	{	// ԭ����ͼ���ڱ�<v1, v2>,ɾ��������Լ�1
		edgeNum--;
	}
	Matrix[v1][v2] = 0;					// �޸�<v1, v2>��Ӧ���ڽӾ���Ԫ��ֵ
}

template <class ElemType>
bool AdjMatrixDirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";		// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetTag(int v, bool val) const 
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";		// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy����������ͼ���ڽӾ���copy�������ƹ��캯��ģ��
{
	int iPos, jPos;								// ��ʱ����
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	elems = new ElemType[vexNum];				// ���ɶ�����������
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���ƶ�����������
		elems[iPos] = copy.elems[iPos];
	}

	tag = new bool[vexNum];						// ���ɱ�־����
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���Ʊ�־����
		tag[iPos] = copy.tag[iPos];
	}

	Matrix = (int **)new int *[vexNum];			// �����ڽӾ���
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new int[vexNum];	
	}  

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (jPos = 0; jPos < vexNum; jPos++)
		{	// �����ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
		}
	}
}

template <class ElemType>
AdjMatrixDirGraph<ElemType> &AdjMatrixDirGraph<ElemType>::operator =(const AdjMatrixDirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy��ֵ����ǰ����ͼ���ڽӾ��󡪡����ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp();							// �ͷŵ�ǰ����ͼռ�ÿռ�

		int iPos, jPos;							// ��ʱ����
		vexNum = copy.vexNum;					// ���ƶ�����
		edgeNum = copy.edgeNum;					// ���Ʊ���

		elems = new ElemType[vexNum];			// ���ɶ�����������
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���ƶ�����������
			elems[iPos] = copy.elems[iPos];
		}

		tag = new bool[vexNum];					// ���ɱ�־����
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���Ʊ�־����
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (int **)new int*[vexNum];		// �����ڽӾ���
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// �����ڽӾ������
			Matrix[iPos] = new int[vexNum];	
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

template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g, bool DisplayVexElem)
// �������: ��ʾ�ڽӾ�������ͼ
{
	int **Matrix;								// �ڽӾ���
	Matrix = (int **)new int *[g.GetVexNum()];	// �����ڽӾ���
	int iPos, jPos;								// ��ʱ���� 

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new int[g.GetVexNum()];	
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{
		for (jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = 0;
		}
	}

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��������ͼ��v���ڽӵ�
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// uΪv���ڽӵ�
			Matrix[v][u] = 1;
		}
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// ��ʾ��
		if (DisplayVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;					// ����Ԫ��
			g.GetElem(iPos, e);			// ȡ��Ԫ��ֵ
			cout << e;					// ��ʾԪ��ֵ
		}

		for (jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// ��ʾԪ��
 			cout << "\t" << Matrix[iPos][jPos];
		}
		cout << endl;					// ���� 
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;					// �ͷ��ڽӾ���
}

template <class ElemType>
void Display(const AdjMatrixDirGraph<ElemType> &g)
// �������: ��ʾ�ڽӾ�������ͼ
{
	int **Matrix;									// �ڽӾ���
	Matrix = (int **)new int *[g.GetVexNum()];		// �����ڽӾ���
	int iPos, jPos;									// ��ʱ���� 

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new int[g.GetVexNum()];	
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{
		for (jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = 0;
		}
	}

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��������ͼ��v���ڽӵ�
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// uΪv���ڽӵ�
			Matrix[v][u] = 1;
		}
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// ��ʾ��
		ElemType e;						// ����Ԫ��
		g.GetElem(iPos, e);				// ȡ��Ԫ��ֵ
		cout << e;						// ��ʾԪ��ֵ

		for (jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// ��ʾԪ��
 			cout << "\t" << Matrix[iPos][jPos];
		}
		cout << endl;					// ���� 
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;					// �ͷ��ڽӾ���
}

#endif
