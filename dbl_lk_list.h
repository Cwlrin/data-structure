#ifndef __DBL_LK_LIST_H__
#define __DBL_LK_LIST_H__

#include "dbl_node.h"				// ˫��������

// ˫��������ģ��
template <class ElemType>
class DblLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	DblNode<ElemType> *head;			// ͷ���ָ��
	mutable int curPosition;			// ��ǰλ�õ����
	mutable DblNode<ElemType> * curPtr;	// ָ��ǰλ�õ�ָ��
	int count;							// Ԫ�ظ���

// ��������ģ��:
	DblNode<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	DblLinkList();				// �޲����Ĺ��캯��ģ��
	virtual ~DblLinkList();		// ��������ģ��
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;	// �������Ա�
	int GetCurPosition() const;								// ���ص�ǰλ��
	bool GetElem(int position, ElemType &e) const;			// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);			// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);					// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);			// ����Ԫ��
	DblLinkList(const DblLinkList<ElemType> &copy);			// ���ƹ��캯��ģ��
	DblLinkList<ElemType> &operator =(const DblLinkList<ElemType> &copy); // ���ظ�ֵ�����
};


// ������ģ���ʵ�ֲ���

template<class ElemType>
DblNode<ElemType> *DblLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (curPosition < position)
	{	// ��ǰλ����������λ��֮ǰ,������
		for (; curPosition < position; curPosition++)
			curPtr = curPtr->next;			// ����λ��position
	}
	else if (curPosition > position)
	{	// ��ǰλ����������λ��֮��,��ǰ����
		for (; curPosition > position; curPosition--)
			curPtr = curPtr->back;			// ����λ��position
	}

	return curPtr;

}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList()
// �������������һ��������
{
	head = new DblNode<ElemType>;	// ����ͷָ��
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
	head->back = head;				// ��˫��ѭ�������ͷ���ǰ��Ϊͷ��㱾��
	curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
	count = 0;						// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
DblLinkList<ElemType>::~DblLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int DblLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool DblLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void DblLinkList<ElemType>::Clear()
// ���������������Ա�
{
	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void DblLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
int DblLinkList<ElemType>::GetCurPosition() const
// ������������ص�ǰλ��
{
	return curPosition;
}

template <class ElemType>
bool DblLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true,
//	���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;					// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return true;
	}
}

template <class ElemType>
bool DblLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,position��ȡֵ��Χ
//	Ϊ1��position��Length(),position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return true;
	}
}

template <class ElemType>
bool DblLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,position��ȡֵ
//	��ΧΪ1��position��Length(),position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position - 1������ָ��
		tmpPtr = tmpPtr->next;					// tmpPtrָ���position �����
		tmpPtr->back->next = tmpPtr->next;		// �޸����ҵ�ָ��
		tmpPtr->next->back = tmpPtr->back;		// �޸������ָ��
		e = tmpPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ
		if (position == Length())
		{	// ɾ��β���,��ǰ����Ϊͷ���
			curPosition = 0;					// ���õ�ǰλ�õ����
			curPtr = head;						// ����ָ��ǰλ�õ�ָ��
		}
		else
		{	// ɾ����β���,��ǰ����Ϊ��position�����
			curPosition = position;				// ���õ�ǰλ�õ����
			curPtr = tmpPtr->next;				// ����ָ��ǰλ�õ�ָ��
		}
		count--;								// ɾ���ɹ���Ԫ�ظ�����1 
		delete tmpPtr;							// �ͷű�ɾ���
		return true;
	}
}

template <class ElemType>
bool DblLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e,position��ȡֵ��Χ
//	Ϊ1��position��Length()+1,position�Ϸ�ʱ����true, ���򷵻�false
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		nextPtr = tmpPtr->next;				// nextPtrָ���position�����	
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);// �����½��
		tmpPtr->next = newPtr;				// �޸����ҵ�ָ��
		nextPtr->back = newPtr;				// �޸������ָ��
		curPosition = position;				// ���õ�ǰλ�õ����
		curPtr = newPtr;					// ����ָ��ǰλ�õ�ָ��
		count++;							// ����ɹ���Ԫ�ظ�����1 
		return true;
	}
}

template <class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
	ElemType e;

	head = new DblNode<ElemType>;		// ����ͷָ��
	head->next = head;					// ��ѭ�������ͷ�����Ϊͷ��㱾��
	head->back = head;					// ��˫��ѭ�������ͷ���ǰ��Ϊͷ��㱾��
	curPtr = head;	curPosition = 0;	// ��ʼ����ǰλ��
	count = 0;							// ��ʼ��Ԫ�ظ���

	for (int pos = 1; pos <= copy.Length(); pos++)
	{	// ��������Ԫ��
		copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
DblLinkList<ElemType> &DblLinkList<ElemType>::operator =(const DblLinkList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա������ظ�ֵ�����
{
	if (&copy != this)
	{
		ElemType e;
		Clear();							// ��յ�ǰ���Ա�

		for (int pos = 1; pos <= copy.Length(); pos++)
		{	// ��������Ԫ��
			copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif