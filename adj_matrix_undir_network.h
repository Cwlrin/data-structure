#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

#include "lk_queue.h"							// 链队列

// 无向网的邻接矩阵类模板
template <class ElemType, class WeightType>
class AdjMatrixUndirNetwork
{
protected:
// 邻接矩阵的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	WeightType **Matrix;						// 邻接矩阵
	ElemType *elems;							// 顶点数据
	mutable bool *tag;							// 指向标志数组的指针
	WeightType infinity;						// 无穷大

// 辅助函数模板
	void DestroyHelp();							// 销毁无向网,释放无向网占用的空间
	void DFS(int v, void (*visit)(const ElemType &e)) const;	// 从顶点v出发进行深度优先搜索网
	void BFS(int v, void (*visit)(const ElemType &)) const;		// 从第顶点v出发进行广度优先搜索网

public:
// 抽象数据类型方法声明模板及重载编译系统默认方法声明模板:
	AdjMatrixUndirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);	
		// 构造顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
	AdjMatrixUndirNetwork(int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);	
		// 构造顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
	~AdjMatrixUndirNetwork();								// 析构函数模板
	void DFSTraverse(void (*visit)(const ElemType &e)) const;	// 对网进行深度优先遍历
	void BFSTraverse(void (*visit)(const ElemType &)) const;	// 对网进行广度优先遍历
	bool GetElem(int v, ElemType &e) const;// 求顶点的元素	
	bool SetElem(int v, const ElemType &e);// 设置顶点的元素值
	WeightType GetInfinity() const;				// 返回无穷大			 
	int GetVexNum() const;						// 返回顶点个数			 
	int GetEdgeNum() const;						// 返回边数个数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2, WeightType w);	// 插入顶点为v1和v2,权为w的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	WeightType GetWeight(int v1, int v2) const;	// 返回顶点为v1和v2的边的权值
	void SetWeight(int v1, int v2, WeightType w);// 设置顶点为v1和v2的边的权值
	bool GetTag(int v) const;				// 返回顶点v的标志		 
	void SetTag(int v, bool val) const;	// 设置顶点v的标志为val		 
	AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy);	// 复制构造函数模板
	AdjMatrixUndirNetwork<ElemType, WeightType> &operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy); // 重载赋值运算符
};

template <class ElemType, class WeightType>
void Display(const AdjMatrixUndirNetwork<ElemType, WeightType> &g, bool showVexElem);	// 显示邻接矩阵无向网
template <class ElemType, class WeightType>
void Display(const AdjMatrixUndirNetwork<ElemType, WeightType> &g);						// 显示邻接矩阵无向网


// 无向网的邻接矩阵类模板实现部分
template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
// 初始条件：存在网
// 操作结果：从顶点v出发进行深度优先搜索网
{	
	SetTag(v, true);						// 作访问标志
	ElemType e;								// 临时变量
	GetElem(v, e);							// 顶点v的数据元素
	(*visit)(e);							// 访问顶点v的数据元素
	for (int w = FirstAdjVex(v); w != -1; w = NextAdjVex(v, w))
	{	// 对v的尚未访问过的邻接顶点w递归调用DFS
		if (!GetTag(w))	DFS(w , visit);	
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
// 初始条件：存在网
// 操作结果：对网进行深度优先遍历
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// 对每个顶点作访问标志
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// 对尚未访问的顶点按DFS进行深度优先搜索
		if (!GetTag(v))	DFS(v, visit);
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
// 初始条件：存在网
// 操作结果：从第顶点v出发进行广度优先搜索网
{	
	SetTag(v, true);						// 作访问标志
	ElemType e;								// 临时变量
	GetElem(v, e);							// 顶点v的数据元素
	(*visit)(e);							// 记问顶点v的数据元素
	LinkQueue<int> q;						// 定义队列
	q.InQueue(v);							// v入队
	while (!q.Empty())
	{	// 队列q非空, 进行循环
		int u, w;							// 临时顶点
		q.OutQueue(u);						// 出队
		for (w = FirstAdjVex(u); w >= 0; w = NextAdjVex(u, w))
		{	// 对u尚未访问过的邻接顶点w进行访问
			if (!GetTag(w))
			{	// 对w进行访问
				SetTag(w, true);			// 作访问标志
				GetElem(w, e);				// 顶点w的数据元素
				(*visit)(e);				// 记问顶点w的数据元素
				q.InQueue(w);				// w入队
			}
		}
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
// 初始条件：存在网
// 操作结果：对网进行广度优先遍历
{
	int v;
	for (v = 0; v < GetVexNum(); v++)
	{	// 对每个顶点作访问标志
		SetTag(v, false);
	}

	for (v = 0; v < GetVexNum(); v++)
	{	// 对尚未访问的顶点按BFS进行深度优先搜索
		if (!GetTag(v)) BFS(v , visit); 
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(ElemType es[], int vertexNum, WeightType infinit)
// 操作结果：构造顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
{
	if (vertexNum < 0)	throw "顶点个数不能为负!";// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];			// 生成顶点数据标数组
	int iPos;									// 临时变量 
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 初始化标志数组
		elems[iPos] = es[iPos];
	}

	tag = new bool[vexNum];				// 生成标志数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 初始化标志数组
		tag[iPos] = false;
	}

	Matrix = (WeightType **)new WeightType *[vexNum];// 生成邻接矩阵
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 生成邻接矩阵的行
		Matrix[iPos] = new WeightType[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (int jPos = 0; jPos < vexNum; jPos++)
		{	// 为邻接矩阵元素赋值
			Matrix[iPos][jPos] = infinity;
		}
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(int vertexNum, WeightType infinit)
// 操作结果：构造顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
{
	if (vertexNum < 0)	throw "顶点个数不能为负!";// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	elems = new ElemType[vexNum];				// 生成顶点数据标数组
	int iPos;									// 临时变量 

	tag = new bool[vexNum];				// 生成标志数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 初始化标志数组
		tag[iPos] = false;
	}

	Matrix = (WeightType **)new WeightType *[vexNum];// 生成邻接矩阵
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 生成邻接矩阵的行
		Matrix[iPos] = new WeightType[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (int jPos = 0; jPos < vexNum; jPos++)
		{	// 为邻接矩阵元素赋值
			Matrix[iPos][jPos] = infinity;
		}
	}
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DestroyHelp()
// 操作结果：销毁无向网,释放无向网占用的空间
{
	delete []elems;							// 释放顶点数据
	delete []tag;								// 释放标志

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放邻接矩阵的行
		delete []Matrix[iPos];
	}
	delete []Matrix;							// 释放邻接矩阵
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::~AdjMatrixUndirNetwork()
// 操作结果：释放对象所占用空间
{
	DestroyHelp();
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;	// 元素不存在
	}
	else
	{	// v合法
		e = elems[v];		// 将顶点v的元素值赋给e
		return true;	// 元素存在
	}
}	

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;	// 位置错
	}
	else
	{	// v合法
		elems[v] = e;		// 顶点元素
		return true;		// 成功
	}
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点			 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";// 抛出异常

	for (int cur = 0; cur < vexNum; cur++)
	{	// 查找邻接点
		if (Matrix[v][cur] != infinity) return cur;
	}

	return -1;									// 返回-1表示无邻接点
}

template <class ElemType, class WeightType>
int AdjMatrixUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下1个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常

	for (int cur = v2 + 1; cur < vexNum; cur++)
	{	// 查找邻接点
		if (Matrix[v1][cur] != infinity) return cur;
	}

	return -1;									// 返回-1表示无邻接点
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常
	if (w == infinity) throw "w不能为无空大!";		// 抛出异常

	if (Matrix[v1][v2] == infinity && Matrix[v2][v1] == infinity)
	{	// 原无向网无边(v1, v2),插入后边数自增1
		edgeNum++;
	}
	Matrix[v1][v2] = w;						// 修改<v1, v2>的权值
	Matrix[v2][v1] = w;						// 修改<v2, v1>的权值
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常

	if (Matrix[v1][v2] != infinity && Matrix[v2][v1] != infinity)
	{	// 原无向网存在边(v1, v2),删除后边数自减1
		edgeNum--;
	}
	Matrix[v1][v2] = infinity;				// 修改<v1, v2>的权值
	Matrix[v2][v1] = infinity;				// 修改<v2, v1>的权值
}

template <class ElemType, class WeightType>
WeightType AdjMatrixUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常

	return Matrix[v1][v2];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常
	if (w == infinity) throw "w不能为无空大!";		// 抛出异常

	Matrix[v1][v2] = w;								// 修改<v1, v2>的权值
	Matrix[v2][v1] = w;								// 修改<v2, v1>的权值
}

template <class ElemType, class WeightType>
bool AdjMatrixUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";		// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjMatrixUndirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const 
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";		// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType>::AdjMatrixUndirNetwork(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：由无向网的邻接矩阵copy构造新无向网的邻接矩阵copy——复制构造函数模板
{
	int iPos, jPos;								// 临时变量
	infinity =copy.infinity;					// 复制无穷大
	vexNum = copy.vexNum;						// 复制顶点数
	edgeNum = copy.edgeNum;						// 复制边数

	elems = new ElemType[vexNum];				// 生成顶点数据数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 复制顶点数据数组
		elems[iPos] = copy.elems[iPos];
	}

	tag = new bool[vexNum];				// 生成标志数组
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 复制标志数组
		tag[iPos] = copy.tag[iPos];
	}

	Matrix = (WeightType **)new WeightType *[vexNum];	// 生成邻接矩阵
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// 生成邻接矩阵的行
		Matrix[iPos] = new WeightType[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (jPos = 0; jPos < vexNum; jPos++)
		{	// 复制邻接矩阵元素赋值
			Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
		}
	}
}

template <class ElemType, class WeightType>
AdjMatrixUndirNetwork<ElemType, WeightType> &AdjMatrixUndirNetwork<ElemType, WeightType>::operator =(const AdjMatrixUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：将无向网的邻接矩阵copy赋值给当前无向网的邻接矩阵——重载赋值运算符
{
	if (&copy != this)
	{
		DestroyHelp();						// 释放当前无向网占用空间
		int iPos, jPos;						// 临时变量
		infinity =copy.infinity;			// 复制无穷大
		vexNum = copy.vexNum;				// 复制顶点数
		edgeNum = copy.edgeNum;				// 复制边数

		elems = new ElemType[vexNum];		// 生成顶点数据数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制顶点数据数组
			elems[iPos] = copy.elems[iPos];
		}

		tag = new bool[vexNum];		// 生成标志数组
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 复制标志数组
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (WeightType **)new WeightType*[vexNum];	// 生成邻接矩阵
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// 生成邻接矩阵的行
			Matrix[iPos] = new WeightType[vexNum];	
		}

		for (iPos = 0; iPos < vexNum; iPos++)
		{
			for (jPos = 0; jPos < vexNum; jPos++)
			{	// 复制邻接矩阵元素赋值
				Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
			}
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, bool showVexElem)
// 操作结果: 显示邻接矩阵无向网
{
	WeightType infinity = net.GetInfinity();
	for (int iPos = 0; iPos < net.GetVexNum(); iPos++)
	{	// 显示行
		if (showVexElem)
		{	// 显示顶点元素
			ElemType e;								// 数据元素
			net.GetElem(iPos, e);					// 取出元素值
			cout << e;								// 显示元素
		}

		for (int jPos = 0; jPos < net.GetVexNum(); jPos++)
		{	// 显示元素
			if (net.GetWeight(iPos, jPos) == infinity)
			{	// 显示无穷大
				cout << "\t" << "∞";
			}
			else
			{	// 显示一般权值
				cout << "\t" << net.GetWeight(iPos, jPos);
			}
		}
		cout << endl;		// 换行 
	}
}

template <class ElemType, class WeightType>
void Display(const AdjMatrixUndirNetwork<ElemType, WeightType> &net)
// 操作结果: 显示邻接矩阵无向网
{
	WeightType infinity = net.GetInfinity();
	for (int iPos = 0; iPos < net.GetVexNum(); iPos++)
	{	// 显示行
		ElemType e;									// 数据元素
		net.GetElem(iPos, e);						// 取出元素值
		cout << e;									// 显示元素

		for (int jPos = 0; jPos < net.GetVexNum(); jPos++)
		{	// 显示元素
			if (net.GetWeight(iPos, jPos) == infinity)
			{	// 显示无穷大
				cout << "\t" << "∞";
			}
			else
			{	// 显示一般权值
				cout << "\t" << net.GetWeight(iPos, jPos);
			}
		}
		cout << endl;		// 换行 
	}
}

#endif
