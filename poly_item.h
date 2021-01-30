#ifndef __POLY_ITEM_H__
#define __POLY_ITEM_H__

// 多项式项类
struct PolyItem
{
// 数据成员:
	double coef;				// 系数
	int    expn;				// 指数	

// 构造函数:
    PolyItem() ;				// 无数据的构造函数
    PolyItem(double cf, int en);// 已知系数成员和指数成员建立结构
};



// 多项式项类的实现部分

PolyItem::PolyItem()
// 操作结果：构造指数成员为-1的结点
{
   expn = -1;
}


PolyItem::PolyItem(double cf, int en)
// 操作结果：构造一个系数成员为cf和指数成员为en的结点
{
   coef = cf;
   expn = en;
}

#endif
