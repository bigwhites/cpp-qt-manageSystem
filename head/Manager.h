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
    static double _useCount;  //资源的使用计数
public:
	Manager();
	virtual ~Manager(); 
    bool comExist(std::string name,std::string brand);  //检验商品是否存在
    double getSumRevenue();
    double getSumCost();
    static void displayRepCom(Commodity* com, QTableWidget* bigTable);  //大表格展示库存中的商品
    static void displaySaledCom(Commodity* saledCom,QTableWidget* samllTable,int amount);    //小表格展示已经购买的商品

};
