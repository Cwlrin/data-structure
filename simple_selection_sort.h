#ifndef __SIMPLE_SELECT_SORT_H__
#define __SIMPLE_SELECT_SORT_H__

#include "utility.h"				// ʵ�ó��������

template <class ElemType>
void SimpleSelectionSort(ElemType elem[], int n)
// �������:������elem����ѡ������
{
	for ( int i = 0; i < n - 1; i++)
	{	// ��i+1�˼�ѡ������
		int lowIndex = i;			// ��¼elem[i .. n - 1]����СԪ��С��
		for (int j = i + 1; j < n; j++)
		{
			if (elem[j] < elem[lowIndex])
			{	// ��lowIndex�洢��ǰѰ������СԪ��С��
				lowIndex = j;
			}
		}
		Swap(elem[i], elem[lowIndex]);	// ����elem[i], elem[lowIndex]
	}
}

#endif

