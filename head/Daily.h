#pragma once
#include "Commodity.h"
#include<iostream>
//日用品类
class Daily : public Commodity
{
public:
	enum class DailyKind {
        BEDDING,KITCHENWARE,ELECTRIC,USUAL
        //床上用品 厨房用品      电器    常用品
	};
protected:
	double _weight;  //重量
	DailyKind _kind;
	static long maxNo;
    static const std::array<std::string,4> kindStrs;
public:
	Daily();
	Daily(std::string name, std::string brand,
		std::string manufactuer, double price,
        double cost, int amount, bool onSale, int saleCount,double weight ,DailyKind kind);
    friend std::ifstream& operator>>(std::ifstream& ifs, Daily& d);
    friend std::ofstream& operator<<(std::ofstream& ofs, Daily& d);
	~Daily() = default;
    int getKind() override;
    double getWeiOrCapa() override;
    void setWeiOrCapa(double wc) override;
    std::string getKindStr(void) override;
    void setKind(int k) override;
};
