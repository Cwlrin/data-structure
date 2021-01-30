#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

#include "utility.h"			// ʵ�ó��������

template <class ElemType>
void BubbleSort(ElemType elem[], int n)
// �������:������elem�������������������
{
	for (int i = 1; i < n; i++)
	{	// ��i����������
		for (int j = 0; j < n - i; j++)
		{	// �Ƚ�elem[j]��elem[j + 1]
			if (elem[j] > elem[j + 1])
			{	// ���������,�򽻻�elem[j]��elem[j + 1]
				Swap(elem[j], elem[j + 1]);
			}
		}
	}
}

#endif

