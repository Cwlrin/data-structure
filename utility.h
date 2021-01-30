#ifndef __UTILITY_H__					// ���û�ж���__UTILITY_H__
#define __UTILITY_H__					// ��ô����__UTILITY_H__

// ʵ�ó��������

// ANSI C++��׼��ͷ�ļ�
#include <string>						// ��׼���Ͳ���
#include <iostream>						// ��׼������
#include <limits>						// ����
#include <cmath>						// ��ѧ����
#include <fstream>						// �ļ��������
#include <cctype>						// �ַ�����
#include <ctime>       					// ���ں�ʱ�亯��
#include <cstdlib>						// ��׼��
#include <cstdio>       				// ��׼�������
#include <iomanip>						// �����������ʽ����	
#include <cstdarg> 						// ֧�ֱ䳤��������	
#include <cassert>						// ֧�ֶ���
using namespace std;					// ��׼������������ռ�std��

// �궨��
#define DEFAULT_SIZE 1000				// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000		// ȱʡ�����


// ʵ�ú���(ģ��)����
static bool UserSaysYes();				// ���û��϶��ش�(yes)ʱ, ����true, �û��񶨻ش�(no)ʱ,����false
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2);	// ����e1, e2ֵ֮
template<class ElemType>
void Show(ElemType elem[], int n);		// ��ʾ����elem�ĸ�����Ԫ��ֵ
template <class ElemType>
void Show(const ElemType &e);			// ��ʾ����Ԫ��

// ʵ����
class Timer;							// ��ʱ����Timer
class Rand;								// �������

static bool UserSaysYes()
// �������: ���û��϶��ش�(yes)ʱ, ����true, �û��񶨻ش�(no)ʱ,����false
{
	char ch;									// �û��ش��ַ�
	bool initialResponse = true;				// ��ʼ�ش�

	do
	{	// ѭ��ֱ���û�����ǡ���Ļش�Ϊֹ
		if (initialResponse) cout << "(y, n)?";	// ��ʼ�ش�
		else cout << "��y��n�ش�:";				// �ǳ�ʼ�ش�
		while ((ch = cin.get()) == ' ' || ch == '\t' || ch == '\n');	// �����ո�,�Ʊ�������з���ȡһ�ַ�
		while (cin.get() != '\n');				// ������ǰ�к�����ַ�
		initialResponse = false;
	} while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');
	
	if (ch == 'y' || ch == 'Y') return true;	// �϶��ش�
	else return false;							// �񶨻ش�
}

// ��ʱ����Timer
class Timer
{
private:
// ���ݳ�Ա
	clock_t startTime;							// ��ʼʱ��

public:
//  ��������
	Timer() { startTime = clock(); }			// ���캯��
	~Timer() {};								// ��������	
	double ElapsedTime()						// �����ѹ���ʱ��
	{
		clock_t endTime = clock();				// ����ʱ��
		return (double)(endTime - startTime) / (double)CLK_TCK;	
			// ���ش�Timer�������������һ�ε���Reset()����ʹ�õ�CPUʱ��
	}
	void Reset() { startTime = clock(); }		// ���ÿ�ʼʱ��
};

// �������Rand
class Rand
{
public:
// ��̬��Ա����
	static void SetRandSeed() {srand( (unsigned)time(NULL)); }	// ���õ�ǰʱ��Ϊ���������
	static int GetRand(int n) { return rand() % (n); }			// ����0 ~ n-1֮��������
	static int GetRand() { return rand(); }						// ���������
};

template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
// �������: ����e1, e2ֵ֮
{
	ElemType temp = e1; e1 = e2; e2 = temp;						// ѭ����ֵʵ�ֽ���e1, e2
}

template<class ElemType>
void Show(ElemType elem[], int n)
// �������: ��ʾ����elem�ĸ�����Ԫ��ֵ
{
	for (int i = 0; i < n; i++)
		cout << elem[i] << "  ";	// ��ʾ����elem
	cout << endl;					// ����
}

template <class ElemType>
void Show(const ElemType &e)
// �������: ��ʾ����Ԫ��
{
    cout << e << "  ";				// ���e
}

#endif
