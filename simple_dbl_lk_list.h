#ifndef __SIMPLE_DBL_LK_LIST_H__
#define __SIMPLE_DBL_LK_LIST_H__

#include "dbl_node.h"				// ˫��������

// ��˫��ѭ��������ģ��
template <class ElemType>
class SimpleDblLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	DblNode<ElemType> *head;		// ͷ���ָ��

// ��������ģ��:
	DblNode<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleDblLinkList();			// �޲����Ĺ��캯��ģ��
	virtual ~SimpleDblLinkList();	// ��������ģ��
	int Length() const;				// �����Ա���			 
	bool Empty() const;				// �ж����Ա��Ƿ�Ϊ��
	void Clear();					// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;		// �������Ա�
	bool GetElem(int position, ElemType &e) const;		// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);		// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);				// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);		// ����Ԫ��
	SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy); // ���ƹ��캯��ģ��
	SimpleDblLinkList<ElemType> &operator =(const SimpleDblLinkList<ElemType> &copy); 
		// ���ظ�ֵ�����
};


// ��������ģ���ʵ�ֲ���

template<class ElemType>
DblNode<ElemType> *SimpleDblLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (position == 0)
	{	// ͷ�������Ϊ0
		return head;
	}

	DblNode<ElemType> *tmpPtr = head->next;	// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int pos = 1;							// tmpPtr��ָ����λ�� 

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
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
// �������������һ��������
{
	head = new DblNode<ElemType>;	// ����ͷָ��
	head->next = head;				// ��˫��ѭ�������ͷ�����Ϊͷ��㱾��
	head->back = head;				// ��˫��ѭ�������ͷ���ǰ��Ϊͷ��㱾��
}

template <class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int SimpleDblLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

template <class ElemType>
bool SimpleDblLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void SimpleDblLinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
bool SimpleDblLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true,����
//	����f
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
bool SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,position��ȡֵ��ΧΪ
//	1��position��Length(), position�Ϸ�ʱ����true,���򷵻�false
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
bool SimpleDblLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,position
//	��ȡֵ��ΧΪ1��position��Length(),position�Ϸ�ʱ����true,����
//	������false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);			// ȡ��ָ���position������ָ��
		tmpPtr->back->next = tmpPtr->next;		// �޸����ҵ�ָ��
		tmpPtr->next->back = tmpPtr->back;		// �޸������ָ��
		e = tmpPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
		delete tmpPtr;							// �ͷű�ɾ���
		return true;
	}
}

template <class ElemType>
bool SimpleDblLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e,position��ȡֵ��ΧΪ
//	1��position��Length()+1, position�Ϸ�ʱ����true, ���򷵻�false
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
		return true;
	}
}

template <class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
	ElemType e;

	head = new DblNode<ElemType>;		// ����ͷָ��
	head->next = head;					// ��˫��ѭ�������ͷ�����Ϊͷ��㱾��
	head->back = head;					// ��˫��ѭ�������ͷ���ǰ��Ϊͷ��㱾��

	for (int pos = 1; pos <= copy.Length(); pos++)
	{	// ��������Ԫ��
		copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
SimpleDblLinkList<ElemType> &SimpleDblLinkList<ElemType>::operator =(const SimpleDblLinkList<ElemType> &copy)
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