#include "head/Commodity.h"
#include<iostream>

using namespace std;


Commodity::Commodity(string no, string name, string brand, string manufacturer, double price, double cost, int amount,bool onSale, int saleCount)
    :_no(no), _name(name), _brand(brand), _manufacturer(manufacturer), _price(price), _cost(cost), _amount(amount),_onSale(onSale),_saleCount(saleCount)
{
}


int Commodity::getAmount(void)
{
    return _amount;
}

int Commodity::getSaleCount(void)
{
    return _saleCount;
}
void Commodity::setSaleCount(int c)
{
    _saleCount = c;
}

string Commodity::getManufacturer()
{
    return _manufacturer;
}

double Commodity::getPrice(void)
{
    return _price;
}

void Commodity::setPrice(double p)
{
    _price = p;
}

double Commodity::getCost(void)
{
    return _cost;
}


std::string Commodity::getNo(void)
{
    return _no;
}

std::string Commodity::getName(void)
{
    return _name;
}

std::string Commodity::getBrand(void)
{
    return _brand;
}

string Commodity::getClassStr()
{
    switch(_no[0])
    {
    case'F': return move("食品");
    case'C': return move("化妆品");
    case'B': return move("饮料");
    case'D': return move("日用品");
    }
}

void Commodity::setName(std::string name)
{
    _name=move(name);
}

void Commodity::setCost(int c)
{
    _cost=c;
}

void Commodity::setManufacturer(std::string m)
{
    _manufacturer=move(m);
}

void Commodity::setAmount(int a)
{
    _amount = a;
}

bool Commodity::onSale(void)
{
    return _onSale;
}

void Commodity::setOffSale()
{
    _onSale = false;
}

void Commodity::setBrand(std::string b)
{
    _brand=move(b);
}
