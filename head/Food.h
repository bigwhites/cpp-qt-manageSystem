#pragma once

#include "Commodity.h"
#include<fstream>

class Food :public Commodity
{
public:
	enum class FoodKind
	{
        COOKED,UN_COOKED,PACKAGED  //熟食,生食，袋装食品
	};
	
protected:
	double _weight;  //重量
	FoodKind _kind;  //食品类型
	static long maxNo;//当前的最大编号
    static const std::array<std::string,3> kindStrs;
public:
	Food();
	Food(std::string name, std::string brand,
		std::string manufacturer, double price,
		double cost, int amount, bool onSale, int saleCount,double weight, FoodKind kind);
	friend std::ifstream& operator>>(std::ifstream& ifs, Food& f);
	friend std::ofstream& operator<<(std::ofstream& ofs, Food& f);
	~Food() = default;
    int getKind() override;
    double getWeiOrCapa() override;
    void setWeiOrCapa(double wc) override;
    std::string getKindStr(void) override;
    void setKind(int k) override;
};




