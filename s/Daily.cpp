
#include"head/Daily.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

long Daily::maxNo = 1000000;
const array<std::string,4>Daily::kindStrs={"床上用品","厨房用品","电器","常用品"};

Daily::Daily() {
	_no = "D" + to_string(++maxNo);
}

Daily::Daily(string name, string brand, string manufacturer,
    double price, double cost, int amount, bool onSale, int saleCount,double weight ,DailyKind kind) :
	Commodity(to_string(++maxNo), name, brand, manufacturer, price,
        cost, amount,onSale,saleCount),_weight(weight), _kind(kind) {
    _no = "D" + _no;
}

int Daily::getKind()
{
    return (int)_kind;
}

double Daily::getWeiOrCapa()
{
    return _weight;
}

void Daily::setWeiOrCapa(double wc)
{
    _weight=wc;
}

string Daily::getKindStr()
{
    return kindStrs[(int)_kind];
}

void Daily::setKind(int k)
{
    _kind = (DailyKind)k;
}


ifstream& operator>>(ifstream& ifs, Daily& d)
{
	int k;
	ifs >> d._no >> d._name >> d._brand >> d._manufacturer
		>> d._price >> d._cost >> d._amount
		>> d._weight >> k >> d._onSale>>d._saleCount;
	d._kind = (Daily::DailyKind)k;
	return ifs;
}

ofstream& operator<<(ofstream& ofs, Daily& d)
{
	ofs << d._no << " " << d._name << " " << d._brand << " " <<
		d._manufacturer << " " << d._price << " " << d._cost
		<< " " << d._amount << " " << d._weight << " "
        << (int)d._kind << " " << d._onSale<<" " << d._saleCount;
    return ofs;
}
