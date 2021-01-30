#ifndef __TRI_LK_BINNARY_TREE_H__
#define __TRI_LK_BINNARY_TREE_H__

#include "lk_queue.h"				// ������
#include "tri_lk_bin_tree_node.h"	// ����������������

// ���������������ģ��
template <class ElemType>
class TriLkBinaryTree
{
protected:
//  �����������ݳ�Ա:
	TriLkBinTreeNode<ElemType> *root;

//	��������ģ��:
	TriLkBinTreeNode<ElemType> *CopyTreeHelp(const TriLkBinTreeNode<ElemType> *r);	// ���ƶ�����
	void DestroyHelp(TriLkBinTreeNode<ElemType> * &r);						// ������rΪ��������
	void PreOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	// �������
	void InOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;		// �������
	void PostOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const;	// �������
    int HeightHelp(const TriLkBinTreeNode<ElemType> *r) const;				// ���ض������ĸ�
	int NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const;			// ���ض������Ľ�����

public:
//  �������������������ر���ϵͳĬ�Ϸ�������:
	TriLkBinaryTree();											// �޲����Ĺ��캯��ģ��
	virtual ~TriLkBinaryTree();									// ��������ģ��
	TriLkBinTreeNode<ElemType> *GetRoot() const;				// ���ض������ĸ�
	bool Empty() const;											// �ж϶������Ƿ�Ϊ��
	bool GetElem(const TriLkBinTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ��Ԫ��ֵ
	bool SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void InOrder(void (*visit)(const ElemType &)) const;		// ���������������	
	void PreOrder(void (*visit)(const ElemType &)) const;		// ���������������
	void PostOrder(void (*visit)(const ElemType &)) const;		// �������ĺ������
	void LevelOrder(void (*visit)(const ElemType &)) const;		// �������Ĳ�α���
	int NodeCount() const;										// ��������Ľ�����
	TriLkBinTreeNode<ElemType> *LeftChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur������
	TriLkBinTreeNode<ElemType> *RightChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur���Һ���
	TriLkBinTreeNode<ElemType> *Parent(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur��˫��
	void InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);	// ��������
	void InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);// �����Һ���
	void DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur);		// ɾ��������
	void DeleteRightChild(TriLkBinTreeNode<ElemType> *cur);		// ɾ�����Ӵ�
	int	Height() const;											// ��������ĸ�
	TriLkBinaryTree(const ElemType &e);							// ������eΪ���Ķ�����
	TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy);		// ���ƹ��캯��ģ��
	TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r);				// ������rΪ���Ķ�����
	TriLkBinaryTree<ElemType> &operator=(const TriLkBinaryTree<ElemType>& copy);	// ���ظ�ֵ�����
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const TriLkBinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(const TriLkBinaryTree<ElemType> &bt);
	//	��״��ʽ��ʾ������ 
template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight);	
	// ��֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]������rΪ����
	// ������
template <class ElemType>
TriLkBinaryTree<ElemType> CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// ��֪������������й��������



// ��������ģ���ʵ�ֲ���
template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree()
// �������������һ���ն�����
{
	root = NULL;
}

template <class ElemType>
TriLkBinaryTree<ElemType>::~TriLkBinaryTree()
// ������������ٶ�����--���캯��ģ��
{
	DestroyHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::GetRoot() const
// ������������ض������ĸ�
{
	return root;
}

template <class ElemType>
bool TriLkBinaryTree<ElemType>::Empty() const
// ����������ж϶������Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType>
bool TriLkBinaryTree<ElemType>::GetElem(const TriLkBinTreeNode<ElemType> *cur, ElemType &e) const
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
bool TriLkBinaryTree<ElemType>::SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
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
void TriLkBinaryTree<ElemType>::PreOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &))const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		(*visit)(r->data);					// ���ʸ����
		PreOrderHelp(r->leftChild, visit);	// ����������
		PreOrderHelp(r->rightChild, visit);	// ����������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PreOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	PreOrderHelp(root, visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, visit);	// ����������
		(*visit)(r->data);					// ���ʸ����
		InOrderHelp(r->rightChild, visit);	// ����������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	InOrderHelp(root, visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrderHelp(const TriLkBinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, visit);	// ����������
		PostOrderHelp(r->rightChild, visit);// ����������
		(*visit)(r->data);					// ���ʸ����
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	PostOrderHelp(root, visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::LevelOrder(void (*visit)(const ElemType &)) const
// �����������α���������
{
	LinkQueue<TriLkBinTreeNode<ElemType> *> q;	// ����
	TriLkBinTreeNode<ElemType> *t = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (t != NULL) q.InQueue(t);				// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(t);     
		(*visit)(t->data);
		if (t->leftChild != NULL)				// ���ӷǿ�
			q.InQueue(t->leftChild);			// �������
		if (t->rightChild != NULL)				// �Һ��ӷǿ�
			q.InQueue(t->rightChild);			// �Һ������
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::HeightHelp(const TriLkBinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ������ĸ�
{
	if(r == NULL)
	{	// �ն�������Ϊ0
		return 0;
	}
	else
	{	// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// �������ĸ�
		rHeight = HeightHelp(r->rightChild);	// �������ĸ�
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::Height() const
// ������������ض������ĸ�
{
	return HeightHelp(root);
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const ElemType &e)
// ���������������eΪ���Ķ�����
{
	root = new TriLkBinTreeNode<ElemType>(e);
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ������Ľ�����
{
	if (r ==NULL) return 0;						// �ն�����������Ϊ0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// �ǿն���������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCount() const
// ������������ض������Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::LeftChild(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur������
{
	return cur->leftChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::RightChild(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur���Һ���
{
	return cur->rightChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::Parent(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur��˫��
{
	return cur->parent;
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿգ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur�����ӣ����cur�����ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// curΪ�գ�����
		return;
	}
	else 
	{	// ��������
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->leftChild != NULL)
		{	// cur�����ӷǿ�
			child->leftChild = cur->leftChild;	// curԭ����������Ϊe��������
			cur->leftChild->parent = child;		// curԭ���������ĸ���˫��Ϊe
		}
		cur->leftChild = child;					// e��Ϊcur������
		child->parent = cur;					// e��˫��Ϊcur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur���Һ��ӣ����cur���Һ��ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// curΪ�գ�����
		return;
	}
	else
	{	// �����Һ���
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->rightChild != NULL)
		{	// cur���Һ��ӷǿ�
			child->rightChild = cur->rightChild;// curԭ����������Ϊe��������
			cur->rightChild->parent = child;	// curԭ���������ɵĸ���˫��Ϊchild
		}
		cur->rightChild = child;				// e��Ϊcur���Һ���
		child->parent= cur;						// e��˫��Ϊcur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->leftChild);		// ɾ��cur������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteRightChild(TriLkBinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->rightChild);		// ɾ��cur������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DestroyHelp(TriLkBinTreeNode<ElemType> *&r)
// ���������������r�Ķ�����
{
	if(r != NULL)
	{	// r�ǿ�,ʵʩ����
		DestroyHelp(r->leftChild);			// ����������
		DestroyHelp(r->rightChild);			// ����������
		delete r;							// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::CopyTreeHelp(const TriLkBinTreeNode<ElemType> *r)
// �������������rΪ���Ķ��������Ƴ��µĶ�����,�����¶������ĸ�
{
	if (r == NULL)
	{	// ���ƿն�����
		return NULL;						// �ն�������Ϊ��	
	}
	else
	{	// ���Ʒǿն�����
		TriLkBinTreeNode<ElemType> *lChild = CopyTreeHelp(r->leftChild);	// ����������
		TriLkBinTreeNode<ElemType> *rChild = CopyTreeHelp(r->rightChild);// ����������
		TriLkBinTreeNode<ElemType> *rt = new TriLkBinTreeNode<ElemType>(r->data, lChild, rChild);
			// ���Ƹ����
		if (lChild != NULL) lChild->parent = rt;		// lChild˫��Ϊrt
		if (rChild != NULL) rChild->parent = rt;		// rChild˫��Ϊrt
		return rt;
	}
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy)
// �������������֪�����������¶������������ƹ��캯��ģ��
{
	root = CopyTreeHelp(copy.root);				// ���ƶ�����
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r)
// ���������������rΪ���Ķ�����
{	
	root = r;								// ���ƶ�����
}

template <class ElemType>
TriLkBinaryTree<ElemType> &TriLkBinaryTree<ElemType>::operator=(const TriLkBinaryTree<ElemType> &copy)
// �������������֪������copy���Ƶ���ǰ������--���ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp(root);					// �ͷ�ԭ��������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);			// ���ƶ�����
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const TriLkBinTreeNode<ElemType> *r, int level)
//	�������������״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
{
	if(r != NULL)
	{	//��������ʽ��ֻ��ʽ�ǿ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//��ʾ������
		cout << endl;						// ��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";					// ȷ���ڵ�level����ʾ���
		cout << r->data;					// ��ʾ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(const TriLkBinaryTree<ElemType> &bt)
//	�����������״��ʽ��ʾ������ 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ�����
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// �����������֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]����
//	��rΪ���Ķ�����
{
	if (preLeft > preRight || inLeft > inRight)
	{	// �������޽��,�ն�����
		r = NULL;							// �ն�������Ϊ��
	}
	else
	{	// �������н��,�ǿն�����
		r = new TriLkBinTreeNode<ElemType>(pre[preLeft]);		// ���ɸ����
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// ����pre[preLeft]��in[]�е�λ��,Ҳ�������������и���λ��
			mid++;
		}
		CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// ����������
		if (r->leftChild != NULL) r->leftChild->parent = r;		// ���ӵ�˫��Ϊr
		CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);											// ����������
		if (r->rightChild != NULL) r->rightChild->parent = r;	// �Һ��ӵ�˫��Ϊr
	}
} 

template <class ElemType>
TriLkBinaryTree<ElemType> CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// �����������֪������������й��������
{
	TriLkBinTreeNode<ElemType> *r;								// �������ĸ�
	CreateBinaryTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// ��������������й�����rΪ���Ķ����� 
	return TriLkBinaryTree<ElemType>(r);						// ������rΪ���Ķ�����
}

#endif
