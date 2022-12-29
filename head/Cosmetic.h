#pragma once
#include "Commodity.h"
#include<fstream>
#include<iostream>
class Cosmetic : public Commodity
{
public:
	enum class CosmeticKind{
        HAIRDRESS, CLEAR, CARE		//美容，清洁，护肤
	};
protected:
	double _weight;
	CosmeticKind _kind;
	static long maxNo;
    static const std::array<std::string,3> kindStrs;
public:
	Cosmetic();
	Cosmetic(std::string name, std::string brand,
		std::string manufacturer, double price,
		double cost, int amount, bool onSale, int saleCount, double weight, CosmeticKind kind);
	~Cosmetic() = default;
	friend std::ifstream &operator>>(std::ifstream &ifs, Cosmetic &c);
	friend std::ofstream &operator<<(std::ofstream &ofs, Cosmetic &c);
    int getKind()override;
    double getWeiOrCapa() override;
    void setWeiOrCapa(double wc) override;
    std::string getKindStr(void) override;
    void setKind(int k) override;
};

