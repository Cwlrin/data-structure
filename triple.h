#ifndef __TRIPLE_H__
#define __TRIPLE_H__

// ��Ԫ����ģ��
template<class ElemType>
struct Triple
{
// ���ݳ�Ա:
	int row, col;						// ����Ԫ�ص����±������±�
	ElemType value;						// ����Ԫ�ص�ֵ

// ���캯��ģ��:
	Triple();							// �޲����Ĺ��캯��ģ��
	Triple(int r, int c, ElemType v);	// ��֪���ݳ�Ա������Ԫ��
};

// ��Ԫ����ģ���ʵ�ֲ���
template<class ElemType>
Triple<ElemType>::Triple()
// ����������������Ԫ��
{
}

template<class ElemType>
Triple<ElemType>::Triple(int r, int c, ElemType v)
// �������������֪�����ݳ�Ա������Ԫ��
{
	row = r;							// �к�
	col = c;							// �к�
	value = v;							// ����Ԫ��ֵ
}

#endif

