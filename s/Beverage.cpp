#include "head/Beverage.h"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;
long Beverage::maxNo = 1000000;
const array<std::string,3> Beverage::kindStrs={"普通饮料","酒","碳酸饮料"};

Beverage::Beverage()
{
	_no = "B" + to_string(++maxNo);

}

Beverage::Beverage(std::string name, std::string brand,
	std::string manufactuer, double price, double cost,
	int amount, bool onSale, int saleCount, int capacity, BeverageKind kind):
	Commodity(to_string(++maxNo), name, brand,
		manufactuer, price, cost, amount,onSale,saleCount), _capacity(capacity), _kind(kind)
{
    _no = "B" + _no;
}

int Beverage::getKind()
{
    return (int)_kind;
}

double Beverage::getWeiOrCapa()
{
    return _capacity;
}

void Beverage::setWeiOrCapa(double wc)
{
    _capacity=(int)wc;
}

string Beverage::getKindStr()
{
    return kindStrs[(int)_kind];
}

void Beverage::setKind(int k)
{
    _kind=(BeverageKind)k;
}


std::ifstream& operator>>(std::ifstream& ifs, Beverage& b)
{
	int k;
	ifs >> b._no >> b._name >> b._brand >> b._manufacturer
		>> b._price >> b._cost >> b._amount
		>> b._capacity >> k >> b._onSale>>b._saleCount;
	b._kind = (Beverage::BeverageKind)k;
	return ifs;
}

std::ofstream& operator<<(std::ofstream& ofs, Beverage& b)
{
	ofs << b._no << " " << b._name << " " << b._brand << " " <<
		b._manufacturer << " " << b._price << " " << b._cost
		<< " " << b._amount << " " << b._capacity << " "
        << (int)b._kind << " " << b._onSale<<" " << b._saleCount;
	return ofs;
}
