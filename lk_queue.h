#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// ���

// ��������ģ��

template<class ElemType>
class LinkQueue 
{
protected:
//  ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *front, *rear;					// ��ͷ��βָָ
	int count;											// Ԫ�ظ���

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkQueue();									// �޲����Ĺ��캯��ģ��
	virtual ~LinkQueue();							// ��������ģ��
	int Length() const;								// ����г���			 
	bool Empty() const;								// �ж϶����Ƿ�Ϊ��
	void Clear();									// ���������
	void Traverse(void (*visit)(const ElemType &)) const ;	// ��������
	bool OutQueue(ElemType &e);						// ���Ӳ���
	bool GetHead(ElemType &e) const;				// ȡ��ͷ����
	bool InQueue(const ElemType &e);				// ��Ӳ���
	LinkQueue(const LinkQueue<ElemType> &copy);		// ���ƹ��캯��ģ��
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// ���ظ�ֵ�����
};

// ��������ģ���ʵ�ֲ���
template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// �������������һ���ն���
{
	rear = front = new Node<ElemType>;	// ����ͷ���
	count = 0;							// �ն���Ԫ�ظ���Ϊ0
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// ������������ٶ���
{
	Clear();		
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// ������������ض��г���			 
{
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return count == 0;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// �����������ն���
{
	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
	{	// ���зǿգ������
		OutQueue(tmpElem);
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*visit)(const ElemType &)) const 
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::OutQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ������true,
//	���򷵻�false��
{
	if (!Empty()) 
	{	// ���зǿ�
		Node<ElemType> *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		front->next = tmpPtr->next;				// frontָ����һԪ��
		if (rear == tmpPtr)
		{	// ��ʾ����ǰ������ֻ��һ��Ԫ�أ����Ӻ�Ϊ�ն���
			rear = front;
		}
		delete tmpPtr;							// �ͷų��ӵĽ��
		count--;								// Ԫ�ظ����Լ�1
		return true;
	}
	else
	{	// ����Ϊ��
		return false;
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ�����true,
//	���򷵻�false��
{
	if (!Empty()) 
	{	// ���зǿ�
		Node<ElemType> *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		return true;
	}
	else
	{	// ����Ϊ��
		return false;
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType &e)
// �������������Ԫ��eΪ�µĶ�β������true
{
	Node<ElemType> *tmpPtr = new Node<ElemType>(e);	// �����½��
	rear->next = tmpPtr;							// �½��׷���ڶ�β
	rear = tmpPtr;									// rearָ���¶�β
	count++;										// Ԫ�ظ����Լ�1
	return true;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// ����������ɶ���copy�����¶���--���ƹ��캯��ģ��
{
	rear = front = new Node<ElemType>;	// ����ͷ���
	count = 0;							// �ն���Ԫ�ظ���Ϊ0
	for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
		InQueue(tmpPtr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// ���������������copy��ֵ����ǰ����--���ظ�ֵ�����
{
	if (&copy != this)
	{
		Clear();
		for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
			tmpPtr = tmpPtr->next)
		{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}

#endif
