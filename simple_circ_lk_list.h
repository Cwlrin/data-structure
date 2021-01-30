#ifndef __SIMPLE_CIRC_LK_LIST_H__
#define __SIMPLE_CIRC_LK_LIST_H__

#include "node.h"					// ���

// ��ѭ��������ģ��
template <class ElemType>
class SimpleCircLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *head;			// ͷ���ָ��

// ��������ģ��:
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleCircLinkList();			// �޲����Ĺ��캯��ģ��
	virtual ~SimpleCircLinkList();	// ��������ģ��
	int Length() const;				// �����Ա���			 
	bool Empty() const;				// �ж����Ա��Ƿ�Ϊ��
	void Clear();					// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;	// �������Ա�
	bool GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);		// ����Ԫ��
	SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy); // ���ƹ��캯��ģ��
	SimpleCircLinkList<ElemType> &operator =(const SimpleCircLinkList<ElemType> &copy); // ���ظ�ֵ�����
};


// ��������ģ���ʵ�ֲ���
template<class ElemType>
Node<ElemType> *SimpleCircLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (position == 0)
	{	// ͷ�������Ϊ0
		return head;
	}

	Node<ElemType> *tmpPtr = head->next;// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int pos = 1;						// tmpPtr��ָ����λ�� 

	while (tmpPtr != head && pos < position)
	{	// ˳ָ�������ң�ֱ��tmpPtrָ���position�����
		tmpPtr = tmpPtr->next;
		pos++;
	}

	if (tmpPtr != head && pos == position)
	{	// ���ҳɹ�
		return tmpPtr;	
	}
	else
	{	// ����ʧ��
		return NULL;	
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList()
// �������������һ��������
{
	head = new Node<ElemType>;		// ����ͷ���
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
}

template <class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;			// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;		// ��ʱԪ��ֵ
	while (!Empty())
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);			// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true, ����
//	������false
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
bool SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe, position��ȡֵ��Χ
//	Ϊ1��position��Length(), position�Ϸ�ʱ����true,���򷵻�false
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
bool SimpleCircLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ, position
//	��ȡֵ��ΧΪ1��position��Length(), position�Ϸ�ʱ����true,����
//	������false
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
		delete nextPtr;							// �ͷű�ɾ���
		return true;
	}
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e, position��ȡֵ��ΧΪ
//	1��position��Length()+1, position�Ϸ�ʱ����true, ���򷵻�false
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false;							// λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node<ElemType> *newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
		tmpPtr->next = newPtr;					// ��tmpPtr���뵽������
		return true;
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
	ElemType e;
	head = new Node<ElemType>;			// ����ͷ���
	head->next = head;					// ��ѭ�������ͷ�����Ϊͷ��㱾��

	for (int pos = 1; pos <= copy.Length(); pos++)
	{	// ��������Ԫ��
		copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType> &SimpleCircLinkList<ElemType>::operator =(const SimpleCircLinkList<ElemType> &copy)
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
