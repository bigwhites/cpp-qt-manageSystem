#pragma once
#include "Commodity.h"
#include<string>
#include<iostream>
#include<fstream>

class Beverage :public Commodity {
public:
	enum class BeverageKind {
		JUICE, WINE, SODA
        //普通饮料，酒，碳酸饮料
	};
protected:
	int _capacity;	//容量
	BeverageKind _kind;
	static long maxNo;
    static const std::array<std::string,3> kindStrs;
public:
	Beverage();
	Beverage(std::string name, std::string brand,
		std::string manufactuer, double price,
		double cost, int amount, bool onSale, int saleCount, int _capacity, BeverageKind);
	friend std::ifstream& operator>>(std::ifstream& ifs, Beverage& b);
	friend std::ofstream& operator<<(std::ofstream& ofs, Beverage& b);
	~Beverage() = default;
    int getKind() override;
    double getWeiOrCapa() override;
    void setWeiOrCapa(double wc) override;
    std::string getKindStr(void) override;
    void setKind(int k) override;
};
