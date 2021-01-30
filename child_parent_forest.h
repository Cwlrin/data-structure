#ifndef __CHILD_PARENT_FOREST_H__
#define __CHILD_PARENT_FOREST_H__

#include "lk_queue.h"												// ������
#include "child_parent_tree_node.h"									// ����˫�ױ�ʾɭ�ֽ��

// ����˫�ױ�ʾɭ����ģ��
template <class ElemType>
class ChildParentForest
{
protected:
//  ɭ�ֵ����ݳ�Ա:
	ChildParentTreeNode<ElemType> *nodes;							// �洢ɭ�ֽ��
	int maxSize;													// ɭ�ֽ�������� 
	int num;														// ����λ�ü������

//	��������ģ��:
	void PreOrderHelp(int r, void (*visit)(const ElemType &)) const;// ���������rΪ��һ�����ĸ���ɭ��
	void InOrderHelp(int r, void (*visit)(const ElemType &)) const;	// ���������rΪ��һ�����ĸ���ɭ��
	void MoveHelp(int from, int to);								// ������from�Ƶ����to
	void DeleteHelp(int r);											// ɾ����rΪ����ɭ��

public:
//  ɭ�ַ������������ر���ϵͳĬ�Ϸ�������:
	ChildParentForest();											// �޲����Ĺ��캯��ģ��
	virtual ~ChildParentForest();									// ��������ģ��
	int GetFirstRoot() const;										// ����ɭ�ֵĵ�һ�����ĸ�
	bool Empty() const;												// �ж�ɭ���Ƿ�Ϊ��
	bool GetElem(int cur, ElemType &e) const;						// ��e���ؽ��Ԫ��ֵ
	bool SetElem(int cur, const ElemType &e);						// �����cur��ֵ��Ϊe
	void PreOrder(void (*visit)(const ElemType &)) const;			// ɭ�ֵ��������
	void InOrder(void (*visit)(const ElemType &)) const;			// ɭ�ֵ��������
	void LevelOrder(void (*visit)(const ElemType &)) const;			// ɭ�ֵĲ�α���
	int NodeCount() const;											// ��ɭ�ֵĽ�����
	int NodeDegree(int cur) const;									// ����cur�Ķ�
	int FirstChild(int cur) const;									// ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;								// ���ؽ��cur�����ֵ�
	int Parent(int cur) const;										// ���ؽ��cur��˫��
	bool InsertChild(int cur, int i, const ElemType &e);	
		// ������Ԫ�ز���Ϊcur�ĵ�i������
	bool DeleteChild(int cur, int i);								// ɾ��cur�ĵ�i������ɭ��
	ChildParentForest(const ElemType &e, int size = DEFAULT_SIZE);
		// ����������Ԫ��eΪ�����������ɵ�ֻ��һ������ɭ��
	ChildParentForest(const ChildParentForest<ElemType> &copy);		// ���ƹ��캯��ģ��
	ChildParentForest(ElemType items[], int parents[], int n, int size = DEFAULT_SIZE);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],������Ϊn��ɭ��
	ChildParentForest<ElemType> &operator=(const ChildParentForest<ElemType>& copy);	
		// ���ظ�ֵ�����
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentForest<ElemType> &f, int r, int level);
	// �������ʾ����ʾɭ�֣�levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentForest<ElemType> &f);
	// �������ʾ����ʾɭ��

// ����˫�ױ�ʾɭ����ģ���ʵ�ֲ���
template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest()
// �������������һ����ɭ��
{
	maxSize = DEFAULT_SIZE;											// ɭ�ֽ��������
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
	num = 0;														// ��ɭ�ֵĽ�����Ϊ0
}

template <class ElemType>
ChildParentForest<ElemType>::~ChildParentForest()
// �������������ɭ��
{
	delete []nodes;													// �ͷŴ洢�ռ�
}

template <class ElemType>
int ChildParentForest<ElemType>::GetFirstRoot() const
// �������������ɭ�ֵĵ�һ�����ĸ�
{
	for (int r = 0; r < num; r++)
	{	// �Ҳ��һ�����ĸ�
		if (Parent(r) == -1) return r;								// posΪ��һ�����ĸ�
	}
	return -1;														// ��ɭ�ָ�Ϊ��
}

template <class ElemType>
bool ChildParentForest<ElemType>::Empty() const
// ����������ж�ɭ���Ƿ�Ϊ��
{
	return num == 0;
}

template <class ElemType>
bool ChildParentForest<ElemType>::GetElem(int cur, ElemType &e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,����false,���򷵻�true
{
	if (cur < 0 || cur >= num)	
	{	// �����ڽ��cur
		return false;											// ����false
	}
	else
	{	// ���ڽ��cur
		e = nodes[cur].data;									// ��e����Ԫ��ֵ
		return true;											// ����true
	}
}

template <class ElemType>
bool ChildParentForest<ElemType>::SetElem(int cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�false,���򷵻�true,�������cur��ֵ����Ϊe
{
	if (cur < 0 || cur >= num)	
	{	// �����ڽ��cur
		return false;												// ����false
	}
	else
	{	// ���ڽ��cur
		nodes[cur].data = e;										// �����cur��ֵ����Ϊe
		return true;												// ����true
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::PreOrderHelp(int r, void (*visit)(const ElemType &)) const
// ��ʼ����: rΪɭ���е�һ�����ĸ�
// �����������ɭ������������ζ�ÿ��Ԫ�ص��ú���(*visit)
{
	if (r >=0 && r < num)
	{	// r��Χ�Ϸ�
		(*visit)(nodes[r].data);									// ���ʵ�һ�����ĸ����
		PreOrderHelp(FirstChild(r), visit);							// ���������һ����������ɭ��
		PreOrderHelp(RightSibling(r), visit);						// ���������ȥ��һ������ʣ��������ɵ�ɭ��
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::PreOrder(void (*visit)(const ElemType &)) const
// ������������������ζ�ɭ�ֵ�ÿ��Ԫ�ص��ú���(*visit)
{
	PreOrderHelp(GetFirstRoot(), visit);							// GetFirstRoot()Ϊ��һ�����ĸ�
}

template <class ElemType>
void ChildParentForest<ElemType>::InOrderHelp(int r, void (*visit)(const ElemType &)) const
// ��ʼ����: rΪɭ���е�һ�����ĸ�
// �����������ɭ������������ζ�ÿ��Ԫ�ص��ú���(*visit)
{
	if (r >=0 && r < num)
	{	// r��Χ�Ϸ�
		InOrderHelp(FirstChild(r), visit);							// ���������һ����������ɭ��
		(*visit)(nodes[r].data);									// ���ʵ�һ�����ĸ����
		InOrderHelp(RightSibling(r), visit);						// ���������ȥ��һ������ʣ��������ɵ�ɭ��
	}
}

template <class ElemType>
void ChildParentForest<ElemType>::InOrder(void (*visit)(const ElemType &)) const
// ������������������ζ�ɭ�ֵ�ÿ��Ԫ�ص��ú���(*visit)
{
	InOrderHelp(GetFirstRoot(), visit);								// GetFirstRoot()Ϊ��һ�����ĸ�
}

template <class ElemType>
void ChildParentForest<ElemType>::LevelOrder(void (*visit)(const ElemType &)) const
// �����������α���ɭ��
{
	for (int cur = 0; cur < num; cur++)
	{	// ����ɭ���и������ĸ����
		if (nodes[cur].parent == -1)				
		{	// �����,��α�����curΪ������
			LinkQueue<int> q;	// ����
			q.InQueue(cur);	// �����������
		
			while (!q.Empty())
			{	// q�ǿ�,˵�����н��δ����
				q.OutQueue(cur);									// ����
				(*visit)(nodes[cur].data);							// ���ʵ�ǰ���
				for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
				{	// ���ν�cur�ĺ�������
					q.InQueue(child);								// �������
				}
			}
		}
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::NodeCount() const
// �������������ɭ�ֵĽ�����
{
	return num;
}

template <class ElemType>
int ChildParentForest<ElemType>::NodeDegree(int cur) const
// ������������ؽ��cur�Ķ�
{
	int d = 0;														// ��ʱ����,���ڶԺ��Ӹ������м���
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
	{	// �Ҳ�cur�ĺ���
		d++;														// �Ժ��Ӹ������м���
	}
	return d;
}

template <class ElemType>
int ChildParentForest<ElemType>::FirstChild(int cur) const
// �����������cur�޺���,�򷵻�-1,���򷵻�ɭ�ֽ��cur�ĵ�һ������,
{
	if (cur < -1 || cur >= num)	
		return -1;													// ���cur������,����-1��ʾ�޺���
	
	if (cur == -1)
	{	//  ���ĸ���˫��Ϊ-1,��ɭ����ÿ�����ĸ�������Ϊ-1�ĺ���
		for (int r = 0; r < num; r++)
		{	// ���ҵ�һ�����ĸ�
			if (Parent(r) == -1) return r;							// rΪ��һ�����ĸ�
		}
	}
	
	if (nodes[cur].childLkList.Empty())
	{	// �޺���
		return -1;
	}
	else
	{
		int child;
		nodes[cur].childLkList.GetElem(1, child);					// ȡ����һ������
		return child;
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::RightSibling(int cur) const
// ���������������cur�����ֵ�,�򷵻�-1,���򷵻�cur�����ֵ�
{
	if (cur < 0 || cur >= num)						
		return -1;													// ���cur������,����-1��ʾ�޺���

	if (nodes[cur].parent == -1)
	{	// curΪ��,��ɭ����ÿ�����ĸ�������Ϊ-1�ĺ���
		for (int pos = cur + 1; pos < num; pos++)
		{	// ����cur�����ֵ�
			if (nodes[cur].parent == nodes[pos].parent) return pos;	// posΪcur�����ֵ�
		}
		return -1;													// ����ʧ��,��ʾ�����ֵ�
	}
	else
	{
		int pt = nodes[cur].parent;									// cur��˫�� 
		for (int pos = 1; pos < nodes[pt].childLkList.Length(); pos++)
		{	// ����cur�ں��������е�λ��
			int child;
			nodes[pt].childLkList.GetElem(pos, child);				// ȡ������
			if (cur == child)
			{	// posΪcur�ں��������е�λ��
				int rightSibling;							
				if (nodes[pt].childLkList.GetElem(pos + 1, rightSibling) == true)
				{	// �������ֵ�
					return rightSibling;							// �������ֵ�
				}
				else
				{	// ���������ֵ�
					return -1;										// ��ʾ�����ֵ�
				}
			}
		}
		return -1;													// ����ʧ��,��ʾ���ֵ�
	}
}

template <class ElemType>
int ChildParentForest<ElemType>::Parent(int cur) const
// �������������ɭ���н��cur��˫��
{
	if (cur < 0 || cur >= num)						
		return -1;													// ���cur������,����-1��ʾ��˫��
	return nodes[cur].parent;
}

template <class ElemType>
void ChildParentForest<ElemType>::MoveHelp(int from, int to)
// ���������������from�Ƶ�to
{
	nodes[to] = nodes[from];										// ��nodes[from]��ֵ��nodes[to]
	for (int pos = 0; pos < num; pos++)
	{	// ����fromΪ˫�׵Ľ���Ϊ��toΪ˫�׵Ľ��
		if (from == nodes[pos].parent) nodes[pos].parent = to;
	}
	nodes[from].childLkList.Clear();								// ���from�ĺ�������
}

template <class ElemType>
bool ChildParentForest<ElemType>::InsertChild(int cur, int i, const ElemType &e)
// ���������������Ԫ�ز���Ϊcur�ĵ�i������,�������ɹ�,�򷵻�true,���򷵻�false
{
	if (num == maxSize) return false;								// ���	
	if (cur < 0 || cur >= num) return false;						// ���cur������
	if (i <= 0 || i > NodeDegree(cur) + 1) return false;			// ����λ�ô�	
	int n, child;													// ��ʱ���� 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// ���ҵ�i�����ӵ�λ��
	num++;															// ����ɹ�,������Լ�1
	if (child != -1)
	{	// ���ڵ�i������,��i�����ӵ�λ��Ϊ����λ��
		for (int pos = num - 2; pos >= child; pos--)
		{	// ��num - 2��child�Ľ�����κ���
			MoveHelp(pos, pos + 1);
		}
		nodes[child].data = e;										// �����child�ĵ�����Ԫ��ֵ��Ϊe
		nodes[child].parent = cur;									// ���child��˫��Ϊcur
		LinkList<int> &cLkList = nodes[cur].childLkList;			// ˫�׵ĺ�������
		cLkList.Insert(i, child);									// ��child������˫�׵ĺ���������
	}
	else
	{	// �����ڵ�i������,�������
		child = num - 1;											// childΪ���λ��
		nodes[child].data = e;										// �����child�ĵ�����Ԫ��ֵ��Ϊe
		nodes[child].parent = cur;									// ���child��˫��Ϊcur
		LinkList<int> &cLkList = nodes[cur].childLkList;			// ˫�׵ĺ�������
		cLkList.Insert(cLkList.Length() + 1, child);				// ��child������˫�׵ĺ���������
	}

	return true;
}

template <class ElemType>
void ChildParentForest<ElemType>::DeleteHelp(int r)
// ���������ɾ����rΪ����ɭ��
{
	if (r >= 0 || r < num)
	{	// r�Ϸ�
		int child = FirstChild(r);									// r���׺���
		while (child != -1)
		{	// ���ں���child
			int nextChild = RightSibling(child);					// r����һ����
			DeleteHelp(child);										// ɾ����child��������
			child = nextChild;										// ��nextChildΪr�ĵ�ǰ����
		}
		nodes[r].parent = -2;										// ˫��Ϊ-2,�ر�ʾ�˽���ѱ�ɾ��
	}
}

template <class ElemType>
bool ChildParentForest<ElemType>::DeleteChild(int cur, int i)
// ���������ɾ��cur�ĵ�i������ɭ��,���ɾ���ɹ�,�򷵻�true,���򷵻�false
{
	if (i <= 0 && i > NodeDegree(cur)) return false;				// ����ʧ��
	int n, child;													// ��ʱ���� 
	for (n = 1, child = FirstChild(cur); n < i; child = RightSibling(child), n++);
		// ���ҵ�i�����ӵ�λ��
	
	DeleteHelp(child);												// ɾ����i����ɭ��
	for (int pos = num - 1; pos >= 0; pos--)
	{	// �����ɾ���Ľ��
		if (Parent(pos) == -2)
		{	// ��ɾ�����
			for (int i = pos + 1; i < num; i++)
			{	// ��pos + 1��num - 1�Ľ������ǰ��
				MoveHelp(i, i - 1);									// ǰ��
			}
			nodes[pos].childLkList.Clear();							// ��պ�������
			num--;													// �����ɾ������,�������Լ�1			
		}
	}
	return true;													// �����ɹ�
}

template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(const ElemType &e, int size)
// �������������������Ԫ��eΪ�����������ɵ�ֻ��һ������ɭ��
{
	maxSize = DEFAULT_SIZE;											// �����������
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
	int root = 0;													// ����λ��
	nodes[root].data = e;											// �����ݳ�Ա���и�ֵ
	nodes[root].parent = -1;										// ����˫��Ϊ-1
	num = 1;														// ������
}

template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(const ChildParentForest<ElemType> &copy)
// �������������֪ɭ�ֹ�����ɭ�֡������ƹ��캯��ģ��
{
	maxSize = copy.maxSize;											// ��������
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�
	for (int pos = 0; pos < copy.num; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = copy.nodes[pos].data;						// ����Ԫ��ֵ
		nodes[pos].parent = copy.nodes[pos].parent;					// ˫��λ��
		nodes[pos].childLkList = copy.nodes[pos].childLkList;		// ��������
	}
	num = copy.num;													// ������
}
  
template <class ElemType>
ChildParentForest<ElemType>::ChildParentForest(ElemType items[], int parents[], int n, int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],������Ϊn��ɭ��
{
	maxSize = size;													// ��������
	if (n > maxSize)	
		throw "������̫��!";										// �׳��쳣
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�

	
	for (int pos = 0; pos < n; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = items[pos];								// ����Ԫ��ֵ
		nodes[pos].parent = parents[pos];							// ˫��λ��
		if (parents[pos] != -1)
		{
			LinkList<int> &cLkList = nodes[parents[pos]].childLkList;	// ˫�׵ĺ�������
			cLkList.Insert(cLkList.Length() + 1, pos);					// ��pos������˫�׵ĺ���������
		}
	}
	num = n;														// ������
}

template <class ElemType>
ChildParentForest<ElemType> &ChildParentForest<ElemType>::operator=(const ChildParentForest<ElemType> &copy)
// �������������֪ɭ��copy���Ƶ���ǰɭ��--���ظ�ֵ�����
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;										// ��������
		delete []nodes;												// �ͷŴ洢�ռ�
		nodes = new ChildParentTreeNode<ElemType>[maxSize];			// ����洢�ռ�
		for (int pos = 0; pos < copy.num; pos++)
		{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
			nodes[pos].data = copy.nodes[pos].data;					// ����Ԫ��ֵ
			nodes[pos].parent = copy.nodes[pos].parent;				// ˫��λ��
			nodes[pos].childLkList = copy.nodes[pos].childLkList;	// ��������
		}
		num = copy.num;												// ������
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildParentForest<ElemType> &f, int r, int level)
// ����������������ʾ����ʾɭ�֣�levelΪ���������������Ĳ����Ϊ1
{
	if (r >= 0 && r < f.NodeCount())
	{	// ���ڽ��r,����ʾr����Ϣ
		cout<<endl;													//��ʾ����	
		for(int i = 0; i< level - 1; i++)
			cout<<" ";												//ȷ���ڵ�level����ʾ���
		ElemType e;
		f.GetElem(r, e);											// ȡ�����r��Ԫ��ֵ
		cout << e;													// ��ʾ���Ԫ��ֵ
		for (int child = f.FirstChild(r); child != -1; child = f.RightSibling(child))
		{	// ������ʾ��������
			DisplayTWithConcaveShapeHelp(f, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildParentForest<ElemType> &f)
// ����������������ʾ����ʾɭ��
{
	for (int cur = 0; cur < f.NodeCount(); cur++)
	{	// ����ɭ���и������ĸ����
		if (f.Parent(cur) == -1)				
		{	// �����
			DisplayTWithConcaveShapeHelp(f, cur, 1);
				// ���ø�������ʵ�ְ������ʾ����ʾɭ�ֵĸ�����
			cout << endl;											// ����
		}
	}
}

#endif
