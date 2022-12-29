#include "head/Cosmetic.h"
#include<string>
#include<iostream>

using namespace std;

long Cosmetic::maxNo = 1000000;
const array<std::string,3> Cosmetic::kindStrs={"美容","清洁","护肤"};

Cosmetic::Cosmetic()
{
	_no = "C" + to_string(++maxNo);
}

Cosmetic::Cosmetic(std::string name, std::string brand,
	              std::string manufacturer, double price,
	              double cost, int amount, bool onSale, int saleCount,double weight,
	              CosmeticKind kind)
	:Commodity(to_string(++maxNo), name, brand, 
		manufacturer, price, cost, amount,onSale,saleCount),_weight(weight), _kind(kind)
{
    _no = "C" + _no;
}

int Cosmetic::getKind()
{
    return (int)_kind;
}

double Cosmetic::getWeiOrCapa()
{
    return _weight;
}

void Cosmetic::setWeiOrCapa(double wc)
{
    _weight=wc;
}

string Cosmetic::getKindStr()
{
    return kindStrs[(int)_kind];
}

void Cosmetic::setKind(int k)
{
    _kind = (CosmeticKind)k;
}


std::ifstream &operator>>(std::ifstream &ifs, Cosmetic &c)
{
	int k;
	ifs >> c._no >> c._name >> c._brand >>
		c._manufacturer >> c._price >> c._cost >>
		c._amount >> c._weight >> k >> c._onSale>>c._saleCount;
	c._kind = (Cosmetic::CosmeticKind)k;
	return ifs;
}

std::ofstream &operator<<(std::ofstream &ofs, Cosmetic &c)
{
	ofs << c._no << " " << c._name << " " << c._brand << " " <<
		c._manufacturer << " " << c._price << " " << c._cost
		<< " " << c._amount << " " << c._weight << " " << (int)c._kind << " " << c._onSale<<" " << c._saleCount;
	return ofs;
}

