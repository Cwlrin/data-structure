#ifndef __CIRC_LK_LIST_H__
#define __CIRC_LK_LIST_H__

#include "node.h"				// ���

// ѭ��������ģ��
template <class ElemType>
class CircLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *head;		// ͷ���ָ��
	mutable int curPosition;			// ��ǰλ�õ����
	mutable Node<ElemType> * curPtr;	// ָ��ǰλ�õ�ָ��
	int count;							// Ԫ�ظ���

// ��������ģ��:
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	CircLinkList();				// �޲����Ĺ��캯��ģ��
	virtual ~CircLinkList();	// ��������ģ��
	int Length() const;			// �����Ա�����			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;	// �������Ա�
	int GetCurPosition() const;								// ���ص�ǰλ��
	bool GetElem(int position, ElemType &e) const;			// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);			// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);					// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);			// ����Ԫ��
	CircLinkList(const CircLinkList<ElemType> &copy);		// ���ƹ��캯��ģ��
	CircLinkList<ElemType> &operator =(const CircLinkList<ElemType> &copy); // ���ظ�ֵ�����
};


// ������ģ���ʵ�ֲ���

template<class ElemType>
Node<ElemType> *CircLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	while (curPosition != position)
	{
		curPosition = (curPosition + 1) % (Length() + 1);	// �����0 ~ length()֮��
		curPtr = curPtr->next;				// curPtrָ����
	}
	return curPtr;
}

template <class ElemType>
CircLinkList<ElemType>::CircLinkList()
// �������������һ��������
{
	head = new Node<ElemType>;		// ����ͷָ��
	head->next = head;				// ��ѭ��������ͷ�����Ϊͷ��㱾��
	curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
	count = 0;						// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
CircLinkList<ElemType>::~CircLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int CircLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool CircLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void CircLinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
	{	// ���Ա��ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void CircLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա���ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);	// �����Ա���ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
int CircLinkList<ElemType>::GetCurPosition() const
// ������������ص�ǰλ��
{
	return curPosition;
}

template <class ElemType>
bool CircLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա����ڵ�position��Ԫ��ʱ����e������ֵ������true,
//	���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;					// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return true;
	}
}

template <class ElemType>
bool CircLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա��ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return true;
	}
}

template <class ElemType>
bool CircLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա��ĵ�position��λ�õ�Ԫ��, ����e������ֵ,position��ȡֵ
//	��ΧΪ1��position��Length(),position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
		tmpPtr->next = nextPtr->next;			// ɾ�����
		e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
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
		delete nextPtr;							// �ͷű�ɾ���
		return true;
	}
}

template <class ElemType>
bool CircLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա��ĵ�position��λ��ǰ����Ԫ��e, position��ȡֵ��Χ
//	Ϊ1��position��Length()+1,position�Ϸ�ʱ����true, ���򷵻�false
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false;						// λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		Node<ElemType> *newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
		tmpPtr->next = newPtr;				// ��tmpPtr���뵽������
		curPosition = position;				// ���õ�ǰλ�õ����
		curPtr = newPtr;					// ����ָ��ǰλ�õ�ָ��
		count++;							// ����ɹ���Ԫ�ظ�����1 
		return true;
	}
}

template <class ElemType>
CircLinkList<ElemType>::CircLinkList(const CircLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա��������ƹ��캯��ģ��
{
	int copyLength = copy.Length();		// copy�ĳ���
	ElemType e;

	head = new Node<ElemType>;			// ����ͷָ��
	head->next = head;					// ��ѭ��������ͷ�����Ϊͷ��㱾��
	curPtr = head;	curPosition = 0;	// ��ʼ����ǰλ��
	count = 0;							// ��ʼ��Ԫ�ظ���

	for (int pos = 1; pos <= copyLength; pos++)
	{	// ��������Ԫ��
		copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
CircLinkList<ElemType> &CircLinkList<ElemType>::operator =(const CircLinkList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա��������ظ�ֵ�����
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		ElemType e;
		Clear();							// ��յ�ǰ���Ա�

		for (int pos = 1; pos <= copyLength; pos++)
		{	// ��������Ԫ��
			copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif