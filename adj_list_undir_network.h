#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "lk_list.h"							// 线性链表
#include "adj_list_network_edge.h"				// 邻接表无向网边数据类模板
#include "adj_list_network_vex_node.h"			// 邻接表无向网顶点结点
#include "lk_queue.h"							// 链队列

// 无向网的邻接表类模板
template <class ElemType, class WeightType>
class AdjListUndirNetwork
{
protected:
// 邻接表的数据成员:
	int vexNum, edgeNum;						// 顶点个数和边数
	AdjListNetWorkVexNode<ElemType, WeightType> *vexTable;	// 顶点表
	mutable bool *tag;							// 指向标志数组的指针				
	WeightType infinity;						// 无穷大

// 辅助函数模板
	void DestroyHelp();							// 销毁无向网,释放无向网点用的空间
	int IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const;
		//定位顶点v在邻接链表中的位置
	void DFS(int v, void (*visit)(const ElemType &e)) const;// 从顶点v出发进行深度优先搜索网
	void BFS(int v, void (*visit)(const ElemType &)) const;	// 从第顶点v出发进行广度优先搜索网

public:
// 抽象数据类型方法声明及重载编译系统默认方法声明:
	AdjListUndirNetwork(ElemType es[], int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 构造顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
	AdjListUndirNetwork(int vertexNum = DEFAULT_SIZE, 
		WeightType infinit = (WeightType)DEFAULT_INFINITY);
		// 构造顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
	~AdjListUndirNetwork();						// 析构函数模板
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
	bool GetTag(int v) const;					// 返回顶点v的标志		 
	void SetTag(int v, bool val) const;			// 设置顶点v的标志为val		 
	AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy);	// 复制构造函数模板
	AdjListUndirNetwork<ElemType, WeightType> &operator 
		=(const AdjListUndirNetwork<ElemType, WeightType> &copy); // 重载赋值运算符
};

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net, bool showVexElem);	// 显示邻接矩阵无向网
template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net);						// 显示邻接矩阵无向网

// 无向网的邻接表类模板的实现部分
template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DFS(int v, void (*visit)(const ElemType &e)) const
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
void AdjListUndirNetwork<ElemType, WeightType>::DFSTraverse(void (*visit)(const ElemType &e)) const
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
void AdjListUndirNetwork<ElemType, WeightType>::BFS(int v, void (*visit)(const ElemType &)) const
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
void AdjListUndirNetwork<ElemType, WeightType>::BFSTraverse(void (*visit)(const ElemType &)) const
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
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(ElemType es[], int vertexNum, WeightType infinit)
// 操作结果：构造顶点数据为es[],顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
{
	if (vertexNum < 0)	throw "顶点个数不能为负!";// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new bool[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化顶点数据
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(int vertexNum, WeightType infinit)
// 操作结果：构造顶点个数为vertexNum,infinit表示无穷大,边数为0的无向网
{
	if (vertexNum < 0)	throw "顶点个数不能为负!";// 抛出异常

	infinity = infinit;							// 无穷大
	vexNum = vertexNum;							// 顶点数为vertexNum
	edgeNum = 0;								// 边数为0

	tag = new bool[vexNum];				// 生成标志数组
	int curPos;									// 临时变量 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 初始化标志数组
		tag[curPos] = false;
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DestroyHelp()
// 操作结果：销毁无向网,释放无向网点用的空间
{
	delete []tag;								// 释放标志
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// 释放链表
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// 释放邻接表
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::~AdjListUndirNetwork()
// 操作结果：释放邻接表无向网所占用空间
{
	DestroyHelp();
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &e) const
// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;				// 元素不存在
	}
	else
	{	// v合法
		e = vexTable[v].data;		// 将顶点v的元素值赋给e
		return true;				// 元素存在
	}
}	

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &e)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时返回
//	true, 否则返回false
{
	if (v < 0 || v >= vexNum)
	{	// v范围错
		return false;				// 位置错
	}
	else
	{	// v合法
		vexTable[v].data = e;		// 顶点元素
		return true;				// 成功
	}
}


template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetInfinity() const
// 操作结果：返回无穷大
{
	return infinity;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::GetEdgeNum() const
// 操作结果：返回边数个数
{
	return edgeNum;
}		 

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第一个邻接点			 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";// 抛出异常

	if (vexTable[v].adjLink == NULL)
	{	// 空邻接链表，无邻接点
		return -1; 
	}
	else
	{	// 空邻接链表，存在邻接点
		AdjListNetworkEdge<WeightType> tmpEdgeNode;
		vexTable[v].adjLink->GetElem(1, tmpEdgeNode);
		return tmpEdgeNode.adjVex;
	}
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::IndexHelp(const LinkList<AdjListNetworkEdge<WeightType> > *la, int v) const
// 操作结果：定位顶点v在邻接链表中的位置
{
	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos; 
	curPos = la->GetCurPosition();

	la->GetElem(curPos, tmpEdgeNode);				// 取得邻接点信息
	if (tmpEdgeNode.adjVex == v) return curPos;		// v为线性链表的当前位置处 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// 循环定定
		la->GetElem(curPos, tmpEdgeNode);			// 取得边信息
		if (tmpEdgeNode.adjVex == v) break;			// 定位成功
	}
	
	return curPos;									// curPos = la.Length() + 1 表定失败
}

template <class ElemType, class WeightType>
int AdjListUndirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常
	
	if (vexTable[v1].adjLink == NULL) return -1;	// 邻接链表vexTable[v1].adjLink,不存在,返回-1

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// 取出v2在邻接链表中的位置
	if (curPos < vexTable[v1].adjLink->Length())
	{	// 存在下1个邻接点
		vexTable[v1].adjLink->GetElem(curPos + 1, tmpEdgeNode);// 取出后继
		return tmpEdgeNode.adjVex;
	}
	else
	{	// 不存在下一个邻接点
		return -1;
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::InsertEdge(int v1, int v2, WeightType w)
// 操作结果：插入顶点为v1和v2,权为w的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";	// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";			// 抛出异常
	if (w == infinity) throw "w不能为无空大!";		// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	// 插入<v1, v2>
	if (vexTable[v1].adjLink == NULL)
	{	// 空链表
		vexTable[v1].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >;
	}
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		tmpEdgeNode.weight = w;								// 设设置权值
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);	// 设置边
	}
	else
	{	// 不存在边<v1, v2>
		tmpEdgeNode.adjVex = v2; tmpEdgeNode.weight = w;	// 定义边
		vexTable[v1].adjLink->Insert(curPos, tmpEdgeNode);	// 插入<v1, v2>
		edgeNum++;											// 边数自增1
	}
	
	// 插入<v2, v1>
	if (vexTable[v2].adjLink == NULL)
	{	// 空链表
		vexTable[v2].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >;
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// 取出v1在邻接链表中的位置
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// 存在边<v2, v1>
		vexTable[v2].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		tmpEdgeNode.weight = w;								// 设设置权值
		vexTable[v2].adjLink->SetElem(curPos, tmpEdgeNode);	// 设置边
	}
	else
	{	// 不存在边<v1, v2>
		tmpEdgeNode.adjVex = v1; tmpEdgeNode.weight = w;	// 定义边
		vexTable[v2].adjLink->Insert(curPos, tmpEdgeNode);	// 插入<v2, v1>
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::DeleteEdge(int v1, int v2)
// 操作结果：删除顶点为v1和v2的边			 
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";			// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";			// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";					// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, tmpEdgeNode);	// 删除<v1, v2>
 		edgeNum--;											// 边数自减1
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// 取出v1在邻接链表中的位置
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// 存在边<v2, v1>
		vexTable[v2].adjLink->Delete(curPos, tmpEdgeNode);	// 删除<v2, v1>
	}
}

template <class ElemType, class WeightType>
WeightType AdjListUndirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// 操作结果：返回顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";			// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";			// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		return tmpEdgeNode.weight;							// 返回权值
	}
	else
	{	// 不存在边<v1, v2>
		return infinity;									// 权值为infinity表示边不存在
	}
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// 操作结果：设置顶点为v1和v2的边的权值
{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";			// 抛出异常
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";			// 抛出异常
	if (v1 == v2) throw "v1不能等于v2!";					// 抛出异常
	if (w == infinity) throw "w不能为无空大!";				// 抛出异常

	AdjListNetworkEdge<WeightType> tmpEdgeNode;
	
	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// 取出v2在邻接链表中的位置
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// 存在边<v1, v2>
		vexTable[v1].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		tmpEdgeNode.weight = w;								// 修改<v1, v2>权值
		vexTable[v1].adjLink->SetElem(curPos, tmpEdgeNode);	// 设置边
	}

	curPos = IndexHelp(vexTable[v2].adjLink, v1);			// 取出v1在邻接链表中的位置
	if (curPos <= vexTable[v2].adjLink->Length())
	{	// 存在边<v2, v1>
		vexTable[v2].adjLink->GetElem(curPos, tmpEdgeNode);	// 取出边
		tmpEdgeNode.weight = w;								// 修改<v2, v1>权值
		vexTable[v2].adjLink->SetElem(curPos, tmpEdgeNode);	// 设置边
	}
}

template <class ElemType, class WeightType>
bool AdjListUndirNetwork<ElemType, WeightType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";				// 抛出异常

	return tag[v];
}

template <class ElemType, class WeightType>
void AdjListUndirNetwork<ElemType, WeightType>::SetTag(int v, bool val) const
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum) throw "v不合法!";			// 抛出异常

	tag[v] = val;
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType>::AdjListUndirNetwork(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：由无向网的邻接矩阵copy构造新无向网的邻接矩阵copy——复制构造函数模板
{
	int curPos;									// 临时变量
	infinity =copy.infinity;					// 复制无穷大
	vexNum = copy.vexNum;						// 复制顶点数
	edgeNum = copy.edgeNum;						// 复制边数

	tag = new bool[vexNum];				// 生成标志数组
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制标志数组
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// 复制邻接链表
		vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
		vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType, class WeightType>
AdjListUndirNetwork<ElemType, WeightType> &AdjListUndirNetwork<ElemType, WeightType>::operator =(const AdjListUndirNetwork<ElemType, WeightType> &copy)
// 操作结果：将无向网的邻接矩阵copy赋值给当前无向网的邻接矩阵——重载赋值运算符
{
	if (&copy != this)
	{
		DestroyHelp();								// 释放当前无向网占用空间

		int curPos;									// 临时变量
		infinity =copy.infinity;					// 复制无穷大
		vexNum = copy.vexNum;						// 复制顶点数
		edgeNum = copy.edgeNum;						// 复制边数

		tag = new bool[vexNum];						// 生成标志数组
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制标志数组
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListNetWorkVexNode<ElemType, WeightType>[vexNum];// 生成邻接表
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// 复制邻接链表
			vexTable[curPos].data = copy.vexTable[curPos].data;	// 复制顶点数据
			vexTable[curPos].adjLink = new LinkList<AdjListNetworkEdge<WeightType> >(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net, bool showVexElem)
// 操作结果: 显示邻接矩阵无向网
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 显示第v个邻接链表
		cout << endl << v << "  ";							// 显示顶点号
		if (showVexElem)
		{	// 显示顶点元素
			ElemType e;										// 数据元素
			net.GetElem(v, e);								// 取出元素值
			cout << e << "  ";								// 显示顶点元素
		}

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// 显示第v个邻接链表的一个结点（表示一个邻接点）
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")"; 
		}
		cout << endl; 
	}
}

template <class ElemType, class WeightType>
void Display(const AdjListUndirNetwork<ElemType, WeightType> &net)
// 操作结果: 显示邻接矩阵无向网
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// 显示第v个邻接链表
		cout << endl << v << "  ";							// 显示顶点号
		ElemType e;											// 数据元素
		net.GetElem(v, e);									// 取出元素值
		cout << e << "  ";									// 显示顶点元素

		for (int u = net.FirstAdjVex(v); u != -1; u = net.NextAdjVex(v, u))
		{	// 显示第v个邻接链表的一个结点（表示一个邻接点）
			cout << "-->(" << u << "," << net.GetWeight(v, u) << ")"; 
		}
		cout << endl; 
	}
}

#endif
