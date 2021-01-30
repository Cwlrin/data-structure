#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

// ѭ��������ģ��

template<class ElemType>
class SqQueue 
{
protected:
	int front, rear;									// ��ͷ��β
	int count;											// Ԫ�ظ���
	int maxSize;										// �������Ԫ�ظ���
	ElemType *elems;									// Ԫ�ش洢�ռ�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqQueue(int size = DEFAULT_SIZE);					// ���캯��ģ��
	virtual ~SqQueue();									// ��������ģ��
	int Length() const;									// ����г���			 
	bool Empty() const;									// �ж϶����Ƿ�Ϊ��
	void Clear();										// ���������
	void Traverse(void (*visit)(const ElemType &)) const;	// ��������
	bool OutQueue(ElemType &e);							// ���Ӳ���
	bool GetHead(ElemType &e) const;					// ȡ��ͷ����
	bool InQueue(const ElemType &e);					// ��Ӳ���
	SqQueue(const SqQueue<ElemType> &copy);				// ���ƹ��캯��ģ��
	SqQueue<ElemType> &operator =(const SqQueue<ElemType> &copy);// ���ظ�ֵ�����
};


// ѭ��������ģ���ʵ�ֲ���
template<class ElemType>
SqQueue<ElemType>::SqQueue(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ѭ������
{
	maxSize = size;							// ���Ԫ�ظ���
	elems = new ElemType[maxSize];			// ����洢�ռ�
	rear = front = 0;						// �ն��ж�ͷ���β���
	count = 0;								// �ն���Ԫ�ظ���Ϊ0;
}

template <class ElemType>
SqQueue<ElemType>::~SqQueue()
// ������������ٶ���
{
	delete []elems;							// �ͷŴ洢�ռ�
}

template<class ElemType>
int SqQueue<ElemType>::Length() const
// ������������ض��г���			 
{
	return count;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return count == 0;
}

template<class ElemType>
void SqQueue<ElemType>::Clear() 
// �����������ն���
{
	rear = front = 0;
	count = 0;								// �ն���Ԫ�ظ���Ϊ0;
}

template <class ElemType>
void SqQueue<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(elems[pos]);
	}
}

template<class ElemType>
bool SqQueue<ElemType>::OutQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ������true,
//	���򷵻�false��
{
	if (!Empty()) 
	{	// ���зǿ�
		e = elems[front];					// ��e���ض�ͷԪ��
		front = (front + 1) % maxSize;		// frontָ����һԪ��
		count--;							// Ԫ�ظ����Լ�1
		return true;
	}
	else
	{	// ����Ϊ��
		return false;
	}
}

template<class ElemType>
bool SqQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ�����true,
//	���򷵻�false��
{
	if (!Empty()) 
	{	// ���зǿ�
		e = elems[front];				// ��e���ض�ͷԪ��
		return true;
	}
	else
	{	// ����Ϊ��
		return false;
	}
}

template<class ElemType>
bool SqQueue<ElemType>::InQueue(const ElemType &e)
// ��������������������������false, �������Ԫ��eΪ�µĶ�β������true
{
	if (count == maxSize)
	{	// ��������
		return false;
	}
	else
	{	// ����δ������ӳɹ�
		elems[rear] = e;				// ����eΪ�¶�β
		rear = (rear + 1) % maxSize;	// rearָ���¶�β
		count++;						// Ԫ�ظ����Լ�1
		return true;
	}
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy)
// ����������ɶ���copy�����¶��С������ƹ��캯��ģ��
{
	maxSize = copy.maxSize;				// �������Ԫ�ظ���
	elems = new ElemType[maxSize];		// ����洢�ռ�
	front = copy.front;					// ���ƶ�ͷλ��	
	rear = copy.rear;					// ���ƶ�βλ��
	count = copy.count;					// ���ƶ���Ԫ�ظ���

	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
	{	// ����ѭ������Ԫ��
		elems[pos] = copy.elems[pos];
	}
}

template<class ElemType>
SqQueue<ElemType> &SqQueue<ElemType>::operator =(const SqQueue<ElemType> &copy)
// ���������������copy��ֵ����ǰ����--���ظ�ֵ�����
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;				// �������Ԫ�ظ���
		delete []elems;						// �ͷŴ洢�ռ�
		elems = new ElemType[maxSize];		// ����洢�ռ�
		front = copy.front;					// ���ƶ�ͷλ��	
		rear = copy.rear;					// ���ƶ�βλ��
		count = copy.count;					// ���ƶ���Ԫ�ظ���

		for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
		{	// ����ѭ������Ԫ��
			elems[pos] = copy.elems[pos];
		}
	}
	return *this;
}

#endif
