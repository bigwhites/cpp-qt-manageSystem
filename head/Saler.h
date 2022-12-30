#pragma once
#include "Manager.h"
#include<string>
#include<tuple>
#include"ui_mainwindow.h"

class Saler : public Manager
{
protected:
	static vector<Commodities>_tradeComs;  //交易商品记录
	static vector<vector<int>>_tradeAmount;  //商品数量记录
	static vector<vector<double>>_tradePrices;  //商品成交价格记录
	static vector<double> _tradeIncome; //交易额记录
	static vector<std::string> _tradeId; //交易号

	static long long _maxId; //当前的最大交易号

	Commodities _coms; //购买的商品
	vector<int> _amount;//当前对应商品的数量
	vector<double> _price;//当前对应商品的价格
	double _income;  //当前交易金额

public:
	Saler();
    tuple<string,double> endBuy();    //结束购买
	bool buy(Commodity* com, int amount = 1);
    double locIncome(); //当前交易金额
	void saveTradeRecord(void);  //保存交易记录
	void loadTradeRecord(void);  //读取交易记录
    void clearRecord();  //清空所有交易记录
    int getPosition(std::string trid);  //获取对应订单号的下标
	void reSetTrRecord(const std::string& trid, Commodity* com = nullptr, int newAmount = 0);  //重设某商品的数量 默认全部退 和某商品全部退
    void showRecord(std::string trid,QTableWidget* table);//显示特定订单号的商品
    double getTradeIncome(const std::string& trid);
    QStringList getNoList(const string& trid);  //返回所有订单号的字符串
    std::string getLastTrid(const string& trid); //获取上一个订单号
    std::string getNextTrid(const string& trid);//获取下一个订单号
    std::string getFirstId(void);  //获得第一个id
};


