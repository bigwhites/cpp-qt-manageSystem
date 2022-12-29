#pragma once

#include<vector>
#include"commodities.h"
#include"ui_mainwindow.h"
using namespace std;

class Manager
{
protected:
	using Commodities = vector<Commodity*>;
protected:
	static Commodities _repository;  //当前库存
    static double _sumRevenue; //营业额
    static double _sumCost;    //成本
	static int _useCount;  //资源的使用计数
public:
	Manager();
	virtual ~Manager(); 
    bool ComExist(std::string name,std::string brand);  //检验商品是否存在
    double getSumRevenue();
    double getSumCost();
    static void displayRepCom(Commodity* com, QTableWidget* bigTable);  //大表格展示库存中的商品
    static void displaySaledCom(Commodity* saledCom,QTableWidget* samllTable,int amount);    //小表格展示已经购买的商品

};

/*
管理类
{
	总营业额 所有商品信息
	 存储商品数据到文件以 及从 文件中读取库存（构造函数中自动调用）

		（子类）库存管理类 负责增删商品 修改属性 进货（修改库存量） 查找特定商品（按照...查找并显示）

		（子类）库存统计类 对库存按照不同的方式进行排序

		（子类）销售类 
		{
			购买商品 ， 退货 
	
			销售统计  ： 记录每次消费内容（购买的产品的数量 价格 ） 统计单次销售的数据  并读写入文件  ？？？
		}
}
*/  


//引入shared_ptr  删除时，只有当购买记录中无该商品才会析构，否则不会析构 只会移到已下架商品中
