#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"				// ������
#include "bin_tree_node.h"			// ���������

// ��������ģ��
template <class ElemType>
class BinaryTree
{
protected:
//  �����������ݳ�Ա:
	BinTreeNode<ElemType> *root;

//	��������ģ��:
	BinTreeNode<ElemType> *CopyTreeHelp(const BinTreeNode<ElemType> *r);// ���ƶ�����
	void DestroyHelp(BinTreeNode<ElemType> * &r);						// ������rΪ��������
	void PreOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const ;	// �������
	void InOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const ;	// �������
	void PostOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const ;	// �������
    int HeightHelp(const BinTreeNode<ElemType> *r) const;	// ���ض������ĸ�
	int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// ���ض������Ľ�����
	BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *cur) const;			// ����cur��˫��

public:
//  �������������������ر���ϵͳĬ�Ϸ�������:
	BinaryTree();											// �޲����Ĺ��캯��ģ��
	virtual ~BinaryTree();									// ��������ģ��
	BinTreeNode<ElemType> *GetRoot() const;					// ���ض������ĸ�
	bool Empty() const;										// �ж϶������Ƿ�Ϊ��
	bool GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ��Ԫ��ֵ
	bool SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);
		// �����cur��ֵ��Ϊe
	void InOrder(void (*visit)(const ElemType &)) const;	// ���������������	
	void PreOrder(void (*visit)(const ElemType &)) const;	// ���������������
	void PostOrder(void (*visit)(const ElemType &)) const;	// �������ĺ������
	void LevelOrder(void (*visit)(const ElemType &)) const;	// �������Ĳ�α���
	int NodeCount() const;									// ��������Ľ�����
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;
		// ���ض��������cur������
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;
		// ���ض��������cur���Һ���
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;
		// ���ض��������cur��˫��
	void InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e);// ��������
	void InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e);// �����Һ���
	void DeleteLeftChild(BinTreeNode<ElemType> *cur);		// ɾ��������
	void DeleteRightChild(BinTreeNode<ElemType> *cur);		// ɾ�����Ӵ�
	int	Height() const;										// ��������ĸ�
	BinaryTree(const ElemType &e);							// ������eΪ���Ķ�����
	BinaryTree(const BinaryTree<ElemType> &copy);			// ���ƹ��캯��ģ��
	BinaryTree(BinTreeNode<ElemType> *r);					// ������rΪ���Ķ�����
	BinaryTree<ElemType> &operator=(const BinaryTree<ElemType>& copy);	// ���ظ�ֵ�����
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(const BinaryTree<ElemType> &bt);
	//	��״��ʽ��ʾ������ 
template <class ElemType>
void CreateBinaryTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// ��֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]������rΪ����
	// ������
template <class ElemType>
BinaryTree<ElemType> CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// ��֪������������й��������



// ��������ģ���ʵ�ֲ���
template <class ElemType>
BinaryTree<ElemType>::BinaryTree()
// �������������һ���ն�����
{
	root = NULL;
}

template <class ElemType>
BinaryTree<ElemType>::~BinaryTree()
// ������������ٶ�����--���캯��ģ��
{
	DestroyHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::GetRoot() const
// ������������ض������ĸ�
{
	return root;
}

template <class ElemType>
bool BinaryTree<ElemType>::Empty() const
// ����������ж϶������Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType>
bool BinaryTree<ElemType>::GetElem(const BinTreeNode<ElemType> *cur, ElemType &e) const
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
bool BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
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
void BinaryTree<ElemType>::PreOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::PreOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	PreOrderHelp(root, visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::InOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::InOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	InOrderHelp(root, visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::PostOrderHelp(const BinTreeNode<ElemType> *r, void (*visit)(const ElemType &)) const
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
void BinaryTree<ElemType>::PostOrder(void (*visit)(const ElemType &)) const
// ����������������������
{
	PostOrderHelp(root, visit);	
}	

template <class ElemType>
void BinaryTree<ElemType>::LevelOrder(void (*visit)(const ElemType &)) const
// �����������α���������
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// ����
	BinTreeNode<ElemType> *t = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (t != NULL) q.InQueue(t);			// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(t);     
		(*visit)(t->data);
		if (t->leftChild != NULL)			// ���ӷǿ�
			q.InQueue(t->leftChild);		// �������
		if (t->rightChild != NULL)			// �Һ��ӷǿ�
			q.InQueue(t->rightChild);		// �Һ������
	}
}

template <class ElemType>
int BinaryTree<ElemType>::HeightHelp(const BinTreeNode<ElemType> *r) const
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
		return (lHeight > rHeight ? lHeight : rHeight) + 1;
			// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType>
int BinaryTree<ElemType>::Height() const
// ������������ض������ĸ�
{
	return HeightHelp(root);
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType &e)
// ���������������eΪ���Ķ�����
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ������Ľ�����
{
	if (r ==NULL) return 0;			// �ն�����������Ϊ0
	else return NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild) + 1;
		// �ǿն���������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType>
int BinaryTree<ElemType>::NodeCount() const
// ������������ض������Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType> *cur) const
// ������������ض��������cur������
{
	return cur->leftChild;
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType> *cur) const
// ������������ض��������cur���Һ���
{
	return cur->rightChild;
}

template <class ElemType>
BinTreeNode<ElemType> * BinaryTree<ElemType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
// ���������������rΪ���Ķ�����, ���cur��˫��
{
	if (r == NULL) return NULL;		// �ն�����
	else if (r->leftChild == cur || r->rightChild == cur) return r; // rΪcur��˫��
	else
	{	// ����������˫��
		BinTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������

		tmp = ParentHelp(r->rightChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������
		else return NULL;						// ��ʾcur��˫��
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType> *cur) const
// ������������ض��������cur��˫��
{
	return ParentHelp(root, cur);
}

template <class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿգ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur�����ӣ����cur�����ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// cur�գ�����
		return;
	}
	else 
	{	// ��������
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->leftChild != NULL)
		{	// cur�����ӷǿ�
			child->leftChild = cur->leftChild;	// curԭ����������Ϊe��������
		}
		cur->leftChild = child;					// e��Ϊcur������
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur���Һ��ӣ����cur���Һ��ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// curΪ�գ�����
		return;
	}
	else
	{	// �����Һ���
		BinTreeNode<ElemType> *child =  new BinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->rightChild != NULL)
		{	// cur���Һ��ӷǿ�
			child->rightChild = cur->rightChild;	// curԭ����������Ϊe��������
		}
		cur->rightChild = child;					// e��Ϊcur���Һ���
		return;
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->leftChild);	// ɾ��cur������
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->rightChild);	// ɾ��cur������
	}
}

template <class ElemType>
void BinaryTree<ElemType>::DestroyHelp(BinTreeNode<ElemType> *&r)
// ���������������r�Ķ�����
{
	if(r != NULL)
	{	// r�ǿ�,ʵʩ����
		DestroyHelp(r->leftChild);		// ����������
		DestroyHelp(r->rightChild);		// ����������
		delete r;						// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
BinTreeNode<ElemType> *BinaryTree<ElemType>::CopyTreeHelp(const BinTreeNode<ElemType> *r)
// �������������rΪ���Ķ��������Ƴ��µĶ�����,�����¶������ĸ�
{
	if (r == NULL)
	{	// ���ƿն�����
		return NULL;					// �ն�������Ϊ��	
	}
	else
	{	// ���Ʒǿն�����
		BinTreeNode<ElemType> *lChild = CopyTreeHelp(r->leftChild);	// ����������
		BinTreeNode<ElemType> *rChild = CopyTreeHelp(r->rightChild);// ����������
		BinTreeNode<ElemType> *rt = new BinTreeNode<ElemType>(r->data, lChild, rChild);
			// ���Ƹ����
		return rt;
	}
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType> &copy)
// �������������֪�����������¶������������ƹ��캯��ģ��
{
	root = CopyTreeHelp(copy.root);	// ���ƶ�����
}

template <class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType> *r)
// ���������������rΪ���Ķ�����
{	
	root = r;	// ���ƶ�����
}

template <class ElemType>
BinaryTree<ElemType> &BinaryTree<ElemType>::operator=(const BinaryTree<ElemType> &copy)
// �������������֪������copy���Ƶ���ǰ�������������ظ�ֵ�����
{
	if (&copy != this)
	{
		DestroyHelp(root);				// �ͷ�ԭ��������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);	// ���ƶ�����
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level)
// �������������״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
{
	if(r != NULL)
	{	// ��������ʽ��ֻ��ʽ�ǿ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//��ʾ������
		cout << endl;					//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//ȷ���ڵ�level����ʾ���
		cout << r->data;				//��ʾ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(const BinaryTree<ElemType> &bt)
// �����������״��ʽ��ʾ������ 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ�����
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(BinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// �����������֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]����
//	��rΪ���Ķ�����
{
	if (preLeft > preRight || inLeft > inRight)
	{	// �������޽��,�ն�����
		r = NULL;			// �ն�������Ϊ��
	}
	else
	{	// �������н��,�ǿն�����
		r = new BinTreeNode<ElemType>(pre[preLeft]);// ���ɸ����
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// ����pre[preLeft]��in[]�е�λ��,Ҳ�������������и���λ��
			mid++;
		}
		CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// ����������
		CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);								// ����������
	}
} 

template <class ElemType>
BinaryTree<ElemType> CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// �����������֪������������й��������
{
	BinTreeNode<ElemType> *r;						// �������ĸ�
	CreateBinaryTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// ��������������й�����rΪ���Ķ����� 
	return BinaryTree<ElemType>(r);					// ������rΪ����������
}

#endif
