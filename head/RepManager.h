#pragma once
#include "Manager.h"
#include<fstream>
#include<list>
#include<map>
class RepManager :public Manager   //库存管理类
{
protected:
    static  map<std::string, Commodity*> _noComMap;  //编号到商品的单射
public:
	RepManager() = default;
	~RepManager() override = default;

	Commodity* searchNo(std::string no);  //寻找给定编号的在售商品  基于map寻找
	Commodity* searchNoAll(std::string no);  //寻找商品(包含不在售)
	std::list<Commodity*> searchName(std::string name);  //按照名称寻找所有符合的商品
	std::list<Commodity*> searchBrand(std::string brand);//按照品牌寻找所有符合的商品
    std::list<Commodity*> searchClass(char classCh);     //按照类型搜索所有符合的商品
	bool addFood(std::string name, std::string brand, //新增食物商品
		std::string manufacturer, double price,
		double cost, int amount, double weight,
		Food::FoodKind kind); 

	bool addCosmetic(std::string name, std::string brand,  //新增化妆品
		std::string manufacturer, double price,
		double cost, int amount, double weight, Cosmetic::CosmeticKind kind);

    bool addBeverage(std::string name, std::string brand,  //新增饮料
                     std::string manufacturer, double price,
                     double cost, int amount, int capacity,
                     Beverage::BeverageKind kind);


    bool addDaily(std::string name, std::string brand,  //新增日用品
                  std::string manufacturer, double price,
                  double cost, int amount, double weight, Daily::DailyKind kind);
	
    void setAmount(std::string no,int newAmount);  //改变某商品的库存
	void setPricre(std::string  no, int newPrice);  //改变某商品的价格
	void deleteCommodity(std::string no); //删除库存中的某件商品
	void loadRepository(void);  //读取库存商品
	void saveRepository(void); //保存商品到文件
};

