#ifndef __CHILD_SIBLING_TREE_H__
#define __CHILD_SIBLING_TREE_H__

#include "lk_queue.h"						// ������
#include "child_sibling_tree_node.h"		// �����ֵܱ�ʾ�����

// �����ֵܱ�ʾ����ģ��
template <class ElemType>
class ChildSiblingTree
{
protected:
//  �������ݳ�Ա:
	ChildSiblingTreeNode<ElemType> *root;			// ��

//	��������ģ��:
	void DestroyHelp(ChildSiblingTreeNode<ElemType> * &r);		// ������rΪ������
	void PreRootOrderHelp(const ChildSiblingTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	
		// �ȸ������
	void PostRootOrderHelp(const ChildSiblingTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;
		// ��������
	int NodeCountHelp(const ChildSiblingTreeNode<ElemType> *r) const;	// ������rΪ�������Ľ�����
	int HeightHelp(const ChildSiblingTreeNode<ElemType> *r) const;	// ������rΪ�������ĸ�
	int DegreeHelp(const ChildSiblingTreeNode<ElemType> *r) const;	// ������rΪ�������Ķ�
	void DeleteHelp(ChildSiblingTreeNode<ElemType> *r);		// ɾ����rΪ������
	ChildSiblingTreeNode<ElemType> *ParentHelp(const ChildSiblingTreeNode<ElemType> *r, 
		const ChildSiblingTreeNode<ElemType> *cur) const;	// ����cur��˫��
	ChildSiblingTreeNode<ElemType> *CopyTreeHelp(const ChildSiblingTreeNode<ElemType> *r);	
		// ������
	ChildSiblingTreeNode<ElemType> *CreateTreeGhelp(ElemType items[], int parents[], int r, int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn��
		// �������������ĸ�

public:
//  ���������������ر���ϵͳĬ�Ϸ�������:
	ChildSiblingTree();									// �޲����Ĺ��캯��ģ��
	virtual ~ChildSiblingTree();						// ��������ģ��
	ChildSiblingTreeNode<ElemType> * GetRoot() const;	// �������ĸ�
	bool Empty() const;									// �ж����Ƿ�Ϊ��
	bool GetElem(const ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ��Ԫ��ֵ
	bool SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void PreRootOrder(void (*visit)(const ElemType &)) const;		// �����ȸ������
	void PostRootOrder(void (*visit)(const ElemType &)) const;		// ���ĺ�������
	void LevelOrder(void (*visit)(const ElemType &)) const;			// ���Ĳ�α���
	int NodeCount() const;								// �������Ľ�����
	int NodeDegree(const ChildSiblingTreeNode<ElemType> *cur) const;	// ���ؽ��cur�Ķ�
	int Degree() const;									// �������Ķ�
	ChildSiblingTreeNode<ElemType> *FirstChild(const ChildSiblingTreeNode<ElemType> *cur) const;	
		// ���������cur�ĵ�һ������
	ChildSiblingTreeNode<ElemType> *RightSibling(const ChildSiblingTreeNode<ElemType> *cur) const;				
		// ���������cur�����ֵ�
	ChildSiblingTreeNode<ElemType> *Parent(const ChildSiblingTreeNode<ElemType> *cur) const;
		// ���������cur��˫��
	bool InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);	
		// ������Ԫ�ز���Ϊcur�ĵ�i������
	bool DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);// ɾ��cur�ĵ�i��������
	int	Height() const;									// �������ĸ�
	ChildSiblingTree(const ElemType &e);				// ����������Ԫ��eΪ������
	ChildSiblingTree(const ChildSiblingTree<ElemType> &copy);	// ���ƹ��캯��ģ��
	ChildSiblingTree(ElemType items[], int parents[], int r, int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
	ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r);// ������rΪ������
	ChildSiblingTree<ElemType> &operator=(const ChildSiblingTree<ElemType>& copy);	
		// ���ظ�ֵ�����
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingTree<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
	// �������ʾ����ʾ����levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t);
	// �������ʾ����ʾ��

// �����ֵܱ�ʾ����ģ���ʵ�ֲ���

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
// �������������һ������
{
	root = NULL;					// ��ʾ��Ϊ��
}

template <class ElemType>
void ChildSiblingTree<ElemType>::DestroyHelp(ChildSiblingTreeNode<ElemType> * &r)
// ���������������rΪ������
{
	if (r != NULL)
	{	// r�ǿ�,ʵʩ����
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// ��������
			DestroyHelp(child);		// ��������
		}
		delete r;					// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
// ���������������--���캯��
{
	DestroyHelp(root);				// ������
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::GetRoot() const
// ����������������ĸ�
{
	return root;					// ����
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::Empty() const
// ����������ж����Ƿ�Ϊ��
{
	return root == NULL;			// rootΪ�ձ�ʾ��Ϊ��
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::GetElem(const ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,����false,���򷵻�true
{
	if (cur == NULL)	
	{	// �����ڽ��cur
		return false;			// ����false
	}
	else
	{	// ���ڽ��cur
		e = cur->data;				// ��e����Ԫ��ֵ
		return true;			// ����true
	}
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�false,���򷵻�true,�������cur��ֵ����Ϊe
{
	if (cur == NULL)	
	{	// �����ڽ��cur
		return false;				// ����false
	}
	else
	{	// ���ڽ��cur
		cur->data = e;				// �����cur��ֵ����Ϊe
		return true;				// ����true
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrderHelp(const ChildSiblingTreeNode<ElemType> *r, 
	void (*visit)(const ElemType &)) const
// ������������ȸ������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)
{
	if (r != NULL)	
	{	// r�ǿ�
		(*visit)(r->data);			// ���ʸ����
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// �����ȸ������ÿ������
			PreRootOrderHelp(child, visit);
		}
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(void (*visit)(const ElemType &)) const
// ������������ȸ������ζ�����ÿ��Ԫ�ص��ú���(*visit)
{
	PreRootOrderHelp(GetRoot(), visit);				// ���ø�������ģ��ʵ�������ȸ�����
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrderHelp(const ChildSiblingTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// �������������������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)
{
	if (r != NULL)	
	{	// r�ǿ�
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// ���κ�������ÿ������
			PostRootOrderHelp(child, visit);
		}
		(*visit)(r->data);					// ���ʸ����
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(void (*visit)(const ElemType &)) const
// �������������������ζ�����ÿ��Ԫ�ص��ú���(*visit)
{
	PostRootOrderHelp(GetRoot(), visit);			// ���ø�������ģ��ʵ�ֺ�������
}

template <class ElemType>
void ChildSiblingTree<ElemType>::LevelOrder(void (*visit)(const ElemType &)) const
// �����������α�����
{
	LinkQueue<ChildSiblingTreeNode<ElemType> *> q;	// ����
	ChildSiblingTreeNode<ElemType> *cur = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (cur != NULL) q.InQueue(cur);			// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(cur);						// ����
		(*visit)(cur->data);					// ���ʵ�ǰ���
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
			child = RightSibling(child))
		{	// ���ν�cur�ĺ�������
			q.InQueue(child);					// �������
		}
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCountHelp(const ChildSiblingTreeNode<ElemType> *r) const
// ���������������rΪ�������Ľ�����
{
	if (r == NULL) return 0;			// ����������Ϊ0
	else
	{	// �������Ľ�����֮��
		int subTreeNodeCountSum = 0;	// ����������֮��
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// ������r�������������������ۼ�
			subTreeNodeCountSum += NodeCountHelp(child);// �ۼ�����������
		}
		return 1 + subTreeNodeCountSum;	// �ǿ�������Ϊ�����Ľ�����֮���ټ�1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCount() const
// ����������������Ľ�����
{
	return NodeCountHelp(root);			// �ø�������ʵ������������
}


template <class ElemType>
int ChildSiblingTree<ElemType>::HeightHelp(const ChildSiblingTreeNode<ElemType> *r) const
// ���������������rΪ�������ĸ�
{
	if (r == NULL)
	{	// ����,��Ϊ0
		return 0;
	}
	else
	{
		int maxSubTreeHeight = 0;
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// ��������ߵ����ֵ
			int h = HeightHelp(child);			// ��ʱ�����洢��
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// ���������ߵ����ֵ
		}
		return maxSubTreeHeight + 1;			// ����Ϊ�����������ֵ�ټ�1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Height() const
// ����������������ĸ�
{
	return HeightHelp(root);					// ���ø�������ʵ�ַ������ĸ�
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(const ChildSiblingTreeNode<ElemType> *cur) const
// ������������ؽ��cur�Ķ�
{
	int d = 0;					// ��ʱ����,���ڶԺ��Ӹ������м���
	for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
		child = RightSibling(child))
	{	// �Ҳ�cur�ĺ���
		d++;					// �Ժ��Ӹ������м���
	}
	return d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::DegreeHelp(const ChildSiblingTreeNode<ElemType> *r) const
// ���������������rΪ�������Ķ�
{

	int d = 0;					// ��ʱ����,���ڽ��ĺ��Ӹ���
	int maxSubTreeDegree = 0;	// �����ȵ����ֵ
	for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
		child = RightSibling(child))
	{	// �Ҳ�r�ĺ���
		d++;					// �Ժ��Ӹ������м���
		int subTreeDegree = DegreeHelp(child);	// �����Ķ�
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// �����������ֵ
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
// ����������������Ķ�
{
	return DegreeHelp(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::FirstChild(const ChildSiblingTreeNode<ElemType> *cur) const
// �����������cur�޺���,�򷵻�NULL,���򷵻������cur�ĵ�һ������,
{
	if (cur == NULL)
	{	// curΪ��
		return NULL;				// �ս���޺���		
	}
	else
	{	// cur�ǿ�
		return cur->firstChild;			// firstChildΪ��һ������
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::RightSibling(const ChildSiblingTreeNode<ElemType> *cur) const
// ���������������cur�����ֵ�,�򷵻�NULL,���򷵻�cur�����ֵ�
{
	if (cur == NULL)
	{	// curΪ��
		return NULL;				// �ս�����ֵ�
	}
	else
	{	// cur�ǿ�
		return cur->rightSibling;			// rightSiblingΪ���ֵ�
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::ParentHelp(const ChildSiblingTreeNode<ElemType> *r, 
	const ChildSiblingTreeNode<ElemType> *cur) const
// ���������������rΪ������, ���cur��˫��
{
	if (r == NULL) return NULL;					// �ն�����
	
	ChildSiblingTreeNode<ElemType> *child;		// ���� 
	for (child = FirstChild(r); child != NULL;
		child = RightSibling(child))
	{	// �Ҳ�r�ĺ���
		if (child == cur) return (ChildSiblingTreeNode<ElemType> *)r;				// cur˫��Ϊr
	}
	
	for (child = FirstChild(r); child != NULL; child = RightSibling(child))
	{	// ����������˫��
		ChildSiblingTreeNode<ElemType> *tmp;
		tmp = ParentHelp(child, cur);			// ����������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫����������
	}
	
	return NULL;								// δ�ҵ�˫��
}



template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(const ChildSiblingTreeNode<ElemType> *cur) const
// ������������ؽ��cur��˫��
{
	return ParentHelp(root, cur);				// �ø������������н���˫��
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// ���������������Ԫ�ز���Ϊcur�ĵ�i������,�������ɹ�,�򷵻�true,���򷵻�false
{
	if (cur == NULL) return false;								// cur������
	if (i <= 0 || i > NodeDegree(cur) + 1) return false;		// iλ�ô�

	ChildSiblingTreeNode<ElemType> *newNodePtr = new ChildSiblingTreeNode<ElemType>(e);	// �½��
	if (i == 1)
	{	// ��������׺���
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// �ݴ�cur���׺���
		cur->firstChild = newNodePtr;							// newNodePtr����Ϊcur���׺���
		newNodePtr->rightSibling = tmp;							// ԭcur���׺��ӱ�ΪnewNodePtr�����ֵ�
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;					// ���� 
		for (child = FirstChild(cur); n < i - 1; child = RightSibling(child), n++);
			// ���ҵ�i-1������
		newNodePtr->rightSibling = child->rightSibling; child->rightSibling = newNodePtr;
			// ��tmp������Ϊ��i������
	}
	return true;
}

template <class ElemType>
void ChildSiblingTree<ElemType>::DeleteHelp(ChildSiblingTreeNode<ElemType> *r)
// ���������ɾ����rΪ������
{
	if (r != NULL)
	{	// r�ǿ�
		ChildSiblingTreeNode<ElemType> *child = FirstChild(r);	// r���׺���
		while (child != NULL)
		{	// ���ں���child
			ChildSiblingTreeNode<ElemType> *nextChild = RightSibling(child);				// r����һ����
			DeleteHelp(child);									// ɾ����child��������
			child = nextChild;									// ��nextChildΪr�ĵ�ǰ����
		}
		delete r;												// �ͷ�r
		r = NULL;
	}
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// ���������ɾ��cur�ĵ�i��������,���ɾ���ɹ�,�򷵻�true,���򷵻�false
{
	if (cur == NULL) return false;								// cur������
	if (i <= 0 && i > NodeDegree(cur)) return false;			// ����ʧ��
	if (i == 1)
	{
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// �ݴ��1�������ĸ�
		cur->firstChild = tmp->rightSibling;					// ���߼���ɾ����1������
		DeleteHelp(tmp);										// ������ɾ����1������
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;					// ���� 
		for (child = FirstChild(cur); n < i - 1; child = RightSibling(child), n++);
			// ���ҵ�i - 1������
		ChildSiblingTreeNode<ElemType> *tmp = child->rightSibling;	// �ݴ��i�������ĸ�
		child->rightSibling = tmp->rightSibling;				// ������ɾ����i��������
		DeleteHelp(tmp);										// ������ɾ����i������
	}
	return true;									// �����ɹ�
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType &e)
// �������������������Ԫ��eΪ������
{
	root = new ChildSiblingTreeNode<ElemType>(e);	// ���ɸ����
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CopyTreeHelp(const ChildSiblingTreeNode<ElemType> *r)
// �������������rΪ���������Ƴ��µ���,���������ĸ�
{
	if (r == NULL)
	{	// ���ƿն�����
		return NULL;					// �ն�������Ϊ��	
	}
	else
	{	// ���Ʒǿն�����
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(r->data);	// ���Ƹ����
		ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;
		for (ChildSiblingTreeNode<ElemType> *child = FirstChild(r); child != NULL;
			child = RightSibling(child))
		{	// ��������
			subTreeRoot = CopyTreeHelp(child);	// ��������
			if (rt->firstChild == NULL)
			{	// subTreeRootΪ�׺���
				rt->firstChild = subTreeRoot;	// subTreeRootΪ�׺���	
				cur = subTreeRoot;				// cur���¸��Ƶ������ĸ�
			}
			else
			{	// subTreeRootΪcur�����ֵ�
				cur->rightSibling = subTreeRoot;// subTreeRootΪ���ֵ�
				cur = subTreeRoot;				// cur���¸��Ƶ������ĸ�
			}
		}
		return rt;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ChildSiblingTree<ElemType> &copy)
// �������������֪�����������������ƹ��캯��ģ��
{
	root = CopyTreeHelp(copy.GetRoot());
}
  
template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CreateTreeGhelp(ElemType items[], int parents[], int r, int n)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn���������������ĸ�
{
	if (r >= 0 && r < n)
	{	// r�Ϸ�
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(items[r]);	// ���Ƹ����
		ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;

		for (int pos = 0; pos < n; pos++)
		{	// ����r�ĺ���
			if (parents[pos] == r)
			{	// ������posΪ��������
				subTreeRoot = CreateTreeGhelp(items, parents, pos, n);
				if (rt->firstChild == NULL)
				{	// subTreeRootΪ��һ�������ĸ�
					rt->firstChild = subTreeRoot;		// subTreeRootΪ�׺���	
					cur = subTreeRoot;					// cur���½����������ĸ�
				}
				else
				{	// subTreeRootΪcur�����ֵ�
					cur->rightSibling = subTreeRoot;	// subTreeRootΪ���ֵ�
					cur = subTreeRoot;					// cur���¸��Ƶ������ĸ�
				}
			}
		}
		return rt;
	}
	else return NULL;									// r�Ƿ�����������
}


template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ElemType items[], int parents[], int r, int n)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
{
	root = CreateTreeGhelp(items, parents, r, n);	// �ø�������������
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r)
// ���������������rΪ������
{
	root = r;
}


template <class ElemType>
ChildSiblingTree<ElemType> &ChildSiblingTree<ElemType>::operator=(const ChildSiblingTree<ElemType> &copy)
// �������������֪��copy���Ƶ���ǰ��--���ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp(root);							// ������
		root = CopyTreeHelp(copy.GetRoot());
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingTree<ElemType> &t, 
	ChildSiblingTreeNode<ElemType> *r, int level)
// ����������������ʾ����ʾ����levelΪ���������������Ĳ����Ϊ1
{
	if (r != NULL)
	{	// �ǿո�r
		cout<<endl;									//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout<<" ";								//ȷ���ڵ�level����ʾ���
		ElemType e;
		t.GetElem(r, e);							// ȡ�����r��Ԫ��ֵ
		cout << e;									// ��ʾ���Ԫ��ֵ
		for (ChildSiblingTreeNode<ElemType> *child = t.FirstChild(r); child != NULL;
			child = t.RightSibling(child))
		{	// ������ʾ��������
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t)
// ����������������ʾ����ʾ��
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);// ���ø�������ģ��ʵ�ְ������ʾ����ʾ��
	cout << endl;									// ����
}

#endif
