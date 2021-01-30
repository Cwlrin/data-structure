#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

// ˳�����ģ��
template <class ElemType>
class SqList 
{
protected:
// ˳���ʵ�ֵ����ݳ�Ա:
	int count;					// Ԫ�ظ���
	int maxSize;				// ˳������Ԫ�ظ���
	ElemType *elems;			// Ԫ�ش洢�ռ�

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqList(int size = DEFAULT_SIZE);	// ���캯��ģ��
	virtual ~SqList();			// ��������ģ��
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*visit)(const ElemType &)) const;		// �������Ա�
	bool GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	bool Insert(int position, const ElemType &e);	// ����Ԫ��
	SqList(const SqList<ElemType> &copy);			// ���ƹ��캯��ģ��
	SqList<ElemType> &operator =(const SqList<ElemType> &copy); // ���ظ�ֵ�����
};


// ˳�����ģ���ʵ�ֲ���

template <class ElemType>
SqList<ElemType>::SqList(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�˳���
{
	maxSize = size;						// ���Ԫ�ظ���
	elems = new ElemType[maxSize];		// ����洢�ռ�
	count = 0;							// �����Ա�Ԫ�ظ���Ϊ0
}

template <class ElemType>
SqList<ElemType>::~SqList()
// ����������������Ա�
{
	delete []elems;						// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

template <class ElemType>
void SqList<ElemType>::Clear()
// ���������������Ա�
{
	count = 0;
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int pos = 1; pos <= Length(); pos++)
	{	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(elems[pos - 1]);
	}
}

template <class ElemType>
bool SqList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true,
//	���򷵻�false
{
	if(position < 1 || position > Length())
	{	// position��Χ��
		return false;			// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		e = elems[position - 1];
		return true;			// Ԫ�ش���
	}
}

template <class ElemType>
bool SqList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe, position��ȡֵ��Χ
//	Ϊ1��position��Length(), position�Ϸ�ʱ����true,���򷵻�false
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;			// λ�ô�
	}
	else
	{	// position�Ϸ�
		elems[position - 1] = e;
		return true;			// �ɹ�
	}
}

template <class ElemType>
bool SqList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ��ǰ��e������ֵ,
//	position�ĵ�ȡֵ��ΧΪ1��position��Length(),position�Ϸ�ʱ����
//	����true,���򷵻�false
{
	ElemType tmp;

	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;
	}
	else
	{	// position�Ϸ�
		GetElem(position, e);	// ��e���ر�ɾ��Ԫ�ص�ֵ
		for (int pos = position + 1; pos <= Length(); pos++)
		{	// ��ɾ��Ԫ��֮���Ԫ����������
			GetElem(pos, tmp); SetElem(pos - 1, tmp); 
		}
		count--;				// ɾ����Ԫ�ظ������Լ�1
		return true;
	}
}

template <class ElemType>
bool SqList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e, position�ĵ�ȡֵ
//	��ΧΪ1��position��Length()+1, �����Ա�����,�򷵻�false, ��
//	position�Ϸ�, �򷵻�true, ���򷵻�false
{
	ElemType tmp;
	if (count == maxSize)
	{	// ���Ա�����
		return false;	
	}
	else if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return false;
	}
	else
	{	// �ɹ�
		count++;				// �����Ԫ�ظ���������1
		for (int pos = Length(); pos >= position; pos--)
		{	// ����λ��֮���Ԫ������
			GetElem(pos, tmp); SetElem(pos + 1, tmp); 
		}

		SetElem(position, e);	// ��e��ֵ��positionλ�ô�	
		return true;			// ����ɹ�
	}
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
	maxSize = copy.maxSize;					// ���Ԫ�ظ���
	elems = new ElemType[maxSize];			// ����洢�ռ�
	count = copy.count;						// �������Ա�Ԫ�ظ���

	for (int pos = 1; pos <= Length(); pos++)
	{	// ��������Ԫ��
		elems[pos - 1] = copy.elems[pos - 1];
	}
}

template <class ElemType>
SqList<ElemType> &SqList<ElemType>::operator =(const SqList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա������ظ�ֵ�����
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;				// ���Ԫ�ظ���
		if (elems != NULL) delete []elems;	// �ͷŴ洢�ռ�
		elems = new ElemType[maxSize];		// ����洢�ռ�
		count = copy.count;					// �������Ա�Ԫ�ظ���

		for (int pos = 1; pos <= Length(); pos++)
		{	// ��������Ԫ��
			elems[pos - 1] = copy.elems[pos - 1];	
		}
	}
	return *this;
}

#endif