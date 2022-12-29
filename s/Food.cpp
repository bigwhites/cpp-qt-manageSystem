#include "head/Food.h"
#include<string>
#include<iostream>

using namespace std;

long Food::maxNo = 1000000;
const array<std::string,3> Food::kindStrs={"熟食","生食","袋装食品"};
Food::Food()
{
	_no = "F" + to_string(++maxNo);
}

Food::Food(string name, string brand, string manufacturer,
	double price, double cost, int amount, bool onSale, int saleCount,
	double weight, FoodKind kind)
	:Commodity(to_string(++maxNo), name, brand, 
		manufacturer, price, cost, amount,onSale,saleCount), 
	_weight(weight), _kind(kind)
{
    _no = "F" + _no;
}

int Food::getKind()
{
    return (int)_kind;
}

double Food::getWeiOrCapa()
{
    return _weight;
}

void Food::setWeiOrCapa(double wc)
{
    _weight=wc;
}

string Food::getKindStr()
{
    return kindStrs[(int)_kind];
}

void Food::setKind(int k)
{
    _kind=(FoodKind)k;
}

ifstream& operator>>(ifstream& ifs, Food& f)
{
	int k;
	ifs >> f._no >> f._name >> f._brand >> f._manufacturer
		>> f._price >> f._cost >> f._amount
		>> f._weight >> k>>f._onSale>>f._saleCount;
	f._kind = (Food::FoodKind)k;
	return ifs;
}

std::ofstream& operator<<(std::ofstream& ofs, Food& f)
{
	ofs << f._no << " " << f._name << " " << f._brand << " " <<
		f._manufacturer << " " << f._price << " " << f._cost
		<< " " << f._amount << " " <<f._weight<<" "
        << (int)f._kind <<" " <<f._onSale<<" " << f._saleCount;
	return ofs;
}
