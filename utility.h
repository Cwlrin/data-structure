#ifndef __UTILITY_H__					// 如果没有定义__UTILITY_H__
#define __UTILITY_H__					// 那么定义__UTILITY_H__

// 实用程序软件包

// ANSI C++标准库头文件
#include <string>						// 标准串和操作
#include <iostream>						// 标准流操作
#include <limits>						// 极限
#include <cmath>						// 数学函数
#include <fstream>						// 文件输入输出
#include <cctype>						// 字符处理
#include <ctime>       					// 日期和时间函数
#include <cstdlib>						// 标准库
#include <cstdio>       				// 标准输入输出
#include <iomanip>						// 输入输出流格式设置	
#include <cstdarg> 						// 支持变长函数参数	
#include <cassert>						// 支持断言
using namespace std;					// 标准库包含在命名空间std中

// 宏定义
#define DEFAULT_SIZE 1000				// 缺省元素个数
#define DEFAULT_INFINITY 1000000		// 缺省无穷大


// 实用函数(模板)声明
static bool UserSaysYes();				// 当用户肯定回答(yes)时, 返回true, 用户否定回答(no)时,返回false
template <class ElemType >
void Swap(ElemType &e1, ElemType &e2);	// 交换e1, e2之值
template<class ElemType>
void Show(ElemType elem[], int n);		// 显示数组elem的各数据元素值
template <class ElemType>
void Show(const ElemType &e);			// 显示数据元素

// 实用类
class Timer;							// 定时器类Timer
class Rand;								// 随机数类

static bool UserSaysYes()
// 操作结果: 当用户肯定回答(yes)时, 返回true, 用户否定回答(no)时,返回false
{
	char ch;									// 用户回答字符
	bool initialResponse = true;				// 初始回答

	do
	{	// 循环直到用户输入恰当的回答为止
		if (initialResponse) cout << "(y, n)?";	// 初始回答
		else cout << "用y或n回答:";				// 非初始回答
		while ((ch = cin.get()) == ' ' || ch == '\t' || ch == '\n');	// 跳过空格,制表符及换行符获取一字符
		while (cin.get() != '\n');				// 跳过当前行后面的字符
		initialResponse = false;
	} while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');
	
	if (ch == 'y' || ch == 'Y') return true;	// 肯定回答
	else return false;							// 否定回答
}

// 定时器类Timer
class Timer
{
private:
// 数据成员
	clock_t startTime;							// 起始时间

public:
//  方法声明
	Timer() { startTime = clock(); }			// 构造函数
	~Timer() {};								// 析构函数	
	double ElapsedTime()						// 返回已过的时间
	{
		clock_t endTime = clock();				// 结束时间
		return (double)(endTime - startTime) / (double)CLK_TCK;	
			// 返回从Timer对象启动或最后一次调用Reset()后所使用的CPU时间
	}
	void Reset() { startTime = clock(); }		// 重置开始时间
};

// 随机数类Rand
class Rand
{
public:
// 静态成员函数
	static void SetRandSeed() {srand( (unsigned)time(NULL)); }	// 设置当前时间为随机数种子
	static int GetRand(int n) { return rand() % (n); }			// 生成0 ~ n-1之间的随机数
	static int GetRand() { return rand(); }						// 生成随机数
};

template <class ElemType >
void Swap(ElemType &e1, ElemType &e2)
// 操作结果: 交换e1, e2之值
{
	ElemType temp = e1; e1 = e2; e2 = temp;						// 循环赋值实现交换e1, e2
}

template<class ElemType>
void Show(ElemType elem[], int n)
// 操作结果: 显示数组elem的各数据元素值
{
	for (int i = 0; i < n; i++)
		cout << elem[i] << "  ";	// 显示数组elem
	cout << endl;					// 换行
}

template <class ElemType>
void Show(const ElemType &e)
// 操作结果: 显示数据元素
{
    cout << e << "  ";				// 输出e
}

#endif
