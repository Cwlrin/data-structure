#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__

// ˳��ջ��ģ��
template<class ElemType>
class SqStack 
{
protected:
//  ˳��ջ�����ݳ�Ա:
	int count;										// Ԫ�ظ���
	int maxSize;									// ջ���Ԫ�ظ���
	ElemType *elems;								// Ԫ�ش洢�ռ�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqStack(int size = DEFAULT_SIZE);				// ���캯��ģ��
	virtual ~SqStack();								// ��������ģ��
	int Length() const;								// ��ջ����			 
	bool Empty() const;								// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse(void (*visit)(const ElemType &)) const;	// ����ջ
	bool Push(const ElemType &e);					// ��ջ
	bool Top(ElemType &e) const;					// ����ջ��Ԫ��
	bool Pop(ElemType &e);							// ��ջ
	SqStack(const SqStack<ElemType> &copy);			// ���ƹ��캯��ģ��
	SqStack<ElemType> &operator =(const SqStack<ElemType> &copy); // ���ظ�ֵ�����
};


// ˳��ջ��ģ���ʵ�ֲ���

template<class ElemType>
SqStack<ElemType>::SqStack(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	maxSize = size;						// ���Ԫ�ظ���
	elems = new ElemType[maxSize];		// ����洢�ռ�
	count = 0;							// ��ջԪ�ظ���Ϊ0
}

template<class ElemType>
SqStack<ElemType>::~SqStack()
// �������������ջ
{
	delete []elems;					// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqStack<ElemType>::Length() const
// �������������ջԪ�ظ���
{
	return count;
}

template<class ElemType>
bool SqStack<ElemType>::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

template<class ElemType>
void SqStack<ElemType>::Clear()
// ������������ջ
{
	count = 0;
}

template <class ElemType>
void SqStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int pos = 1; pos <= Length(); pos++)
	{	// ��ջ�׵�ջ����ջ��ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(elems[pos - 1]);
	}
}

template<class ElemType>
bool SqStack<ElemType>::Push(const ElemType &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�true,��ջ����������false
{
	if (count == maxSize) 
	{	// ջ����
		return false;
	}
	else
	{	// �����ɹ�
		elems[count++] = e;	// ��Ԫ��e׷�ӵ�ջ�� 
		return true;
	}
}

template<class ElemType>
bool SqStack<ElemType>::Top(ElemType &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,����true,���򷵻�false
{
	if(Empty())
	{	// ջ��
		return false;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
		return true;
	}
}

template<class ElemType>
bool SqStack<ElemType>::Pop(ElemType &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,����true,����
//	����false
{
	if (Empty())
	{	// ջ��
		return false;
	}
	else
	{	// �����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
		count--;	
		return true;
	}
}

template<class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy) 
// �����������ջcopy������ջ--���ƹ��캯��ģ��
{
	maxSize = copy.maxSize;					// ���Ԫ�ظ���
	elems = new ElemType[maxSize];			// ����洢�ռ�
	count = copy.count;						// ����ջԪ�ظ���

	for (int pos = 1; pos <= Length(); pos++)
	{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
		elems[pos - 1] = copy.elems[pos - 1];
	}
}

template<class ElemType>
SqStack<ElemType> &SqStack<ElemType>::operator = (const SqStack<ElemType> &copy)
// �����������ջcopy��ֵ����ǰջ--���ظ�ֵ�����
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;				// ���Ԫ�ظ���
		delete []elems;						// �ͷŴ洢�ռ�
		elems = new ElemType[maxSize];		// ����洢�ռ�
		count = copy.count;					// ����ջԪ�ظ���

		for (int pos = 1; pos <= Length(); pos++)
		{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
			elems[pos - 1] = copy.elems[pos - 1];
		}
	}
	return *this;
}

#endif