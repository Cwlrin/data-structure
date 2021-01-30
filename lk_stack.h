#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"										// ���

// ��ջ��ģ��
template<class ElemType>
class LinkStack 
{
protected:
//  ��ջʵ�ֵ����ݳ�Ա:
	Node<ElemType> *top;								// ջ��ָ��
	int count;											// Ԫ�ظ���

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkStack();										// �޲����Ĺ��캯��ģ��
	virtual ~LinkStack();								// ��������ģ��
	int Length() const;									// ��ջ����			 
	bool Empty() const;									// �ж�ջ�Ƿ�Ϊ��
	void Clear();										// ��ջ���
	void Traverse(void (*visit)(const ElemType &)) const ;		// ����ջ
	bool Push(const ElemType &e);						// ��ջ
	bool Top(ElemType &e) const;						// ����ջ��Ԫ��
	bool Pop(ElemType &e);								// ��ջ
	LinkStack(const LinkStack<ElemType> &copy);			// ���ƹ��캯��ģ��
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &copy); // ���ظ�ֵ�����
};


// ��ջ��ģ���ʵ�ֲ���
template<class ElemType>
LinkStack<ElemType>::LinkStack()
// �������������һ����ջ��
{
	top = NULL;				// ����ջ��ָ��
	count = 0;				// ��ջԪ�ظ���Ϊ0
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// �������������ջ
{
	Clear();
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
// �������������ջԪ�ظ���
{
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// ������������ջ
{
	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
		Pop(tmpElem);
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	Node<ElemType> *tmpPtr;		
	LinkStack<ElemType> tmpS;	// ��ʱջ,tmpS��Ԫ��˳���뵱ǰջԪ��˳���෴
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ǰջ��ÿ��Ԫ��
		tmpS.Push(tmpPtr->data);	// �Ե�ǰջ��ÿ��Ԫ����ջ��tmpS��
	}
	
	for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr��ջ����ջ������ָ��ջtmpS��ÿ��Ԫ��
		(*visit)(tmpPtr->data);		// ��ջtmpS��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Push(const ElemType &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�true,�����綯̬�ڴ��Ѻľ�
//	������false
{
	Node<ElemType> *newTop = new Node<ElemType>(e, top);
	if (newTop == NULL) 
	{	// ��̬�ڴ�ľ�
		return false;
	}
	else
	{	// �����ɹ�
		top = newTop;
		count++;					// Ԫ�ظ����Լ�1
		return true;
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Top(ElemType &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,����true,���򷵻�false
{
	if(Empty())
	{	// ջ��
		return false;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = top->data;				// ��e����ջ��Ԫ��
		return true;
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Pop(ElemType &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,����true,����
//	����false
{
	if (Empty())
	{	// ջ��
		return false;
	}
	else
	{	// �����ɹ�
		Node<ElemType> *old_top = top;	// ��ջ��
		e = old_top->data;				// ��e����ջ��Ԫ��
		top = old_top->next;			// topָ����ջ��
		count--;						// Ԫ�ظ����Լ�1
		delete old_top;					// ɾ����ջ��
		return true;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) 
// �����������ջcopy������ջ--���ƹ��캯��ģ��
{
	if (copy.Empty())
	{	// copyΪ��
		top = NULL;						// ����ջ��ָ��
		count = 0;						// ��ջԪ�ظ���Ϊ0
	}
	else 
	{	// copy�ǿ�,����ջ
		top = new Node<ElemType>(copy.top->data);	// ���ɵ�ǰջ��
		count = copy.count;							// ����ջԪ�ظ���

		Node<ElemType> *buttomPtr = top;			// ��ǰջ��ָ��
		for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{	// ��tmpPtr����ָ������Ԫ��
			buttomPtr->next = new Node<ElemType>(tmpPtr->data); // ��ջ��׷��Ԫ��	
			buttomPtr = buttomPtr->next;			// buttomPtrָ����ջ��
		}
	}
}

template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &copy)
// �����������ջcopy��ֵ����ǰջ--���ظ�ֵ�����
{
	if (&copy != this)
	{
		if (copy.Empty())
		{	// copyΪ��
		top = NULL;						// ����ջ��ָ��
		count = 0;						// ��ջԪ�ظ���Ϊ0
		}
		else 
		{	// copy�ǿ�,����ջ
			Clear();									// ��յ�ǰջ
			top = new Node<ElemType>(copy.top->data);	// ���ɵ�ǰջ��
			count = copy.count;							// ����ջԪ�ظ���

			Node<ElemType> *buttomPtr = top;			// ��ǰջ��ָ��
			for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{	// ��tmpPtr����ָ������Ԫ��
				buttomPtr->next = new Node<ElemType>(tmpPtr->data); // ��ջ��׷��Ԫ��	
				buttomPtr = buttomPtr->next;			// buttomPtrָ����ջ��
			}
		}
	}
	return *this;
}

#endif