
#include "head/Manager.h"
#include<fstream>
#include<thread>
using namespace std;

double Manager::_sumCost = 0;
double Manager::_sumRevenue = 0;
Manager::Commodities Manager::_repository;
double Manager::_useCount = 0;

Manager::Manager()
{
    ++_useCount;
}

Manager::~Manager()
{
    --_useCount;
    if (_useCount == 0)  //资源引用计数为0时释放
    {
        for (auto& pCommodity : _repository)
        {
            if (pCommodity)
            {
                delete pCommodity;
                pCommodity = nullptr;
            }
        }
    }
}

bool Manager::comExist(string name, string brand)  //商品查重
{
    bool b=false,c=false;
    auto check = [](auto begin,auto end,const string& n,const string& b,bool* exist)
    {
        for(auto it=begin;it!=end;++it)
        {
            if((*it)->getName()==n && (*it)->getBrand()==b && (*it)->onSale())
            {
                *exist=true;
                return;
            }
        }
    };
    int half = _repository.size()/2;
    thread th(check,_repository.begin()+half
             ,_repository.end(),name,brand,&c);   //多线程查询
    check(_repository.begin(),_repository.begin()+half,name,brand,&b);
    th.join();
    return b||c;
}

double Manager::getSumRevenue()
{
    return _sumRevenue;
}

double Manager::getSumCost()
{
    return _sumCost;
}

void Manager::displayRepCom(Commodity* com, QTableWidget *bigTable)
{
    int row=bigTable->rowCount();
    bigTable->insertRow(row);
    QString qNo=com->getNo().c_str();
    bigTable->setItem(row,0,new QTableWidgetItem(qNo));
    bigTable->setItem(row,1,new QTableWidgetItem(com->getName().c_str()));
    bigTable->setItem(row,2,new QTableWidgetItem(com->getClassStr().c_str()));
    bigTable->setItem(row,3,new QTableWidgetItem(QString::number(com->getPrice())));
    bigTable->setItem(row,4,new QTableWidgetItem(QString::number(com->getAmount())));
    bigTable->setItem(row,5,new QTableWidgetItem(com->getBrand().c_str()));
    bigTable->setItem(row,6,new QTableWidgetItem(com->getManufacturer().c_str()));
    bigTable->setItem(row,7,new QTableWidgetItem(QString::number(com->getSaleCount())));
    bigTable->setItem(row,8,new QTableWidgetItem(QString::number(com->getCost())));
    bigTable->setItem(row,9,new QTableWidgetItem(com->getKindStr().c_str()));
    bigTable->setItem(row,10,new QTableWidgetItem(QString::number(com->getWeiOrCapa())));
}

void Manager::displaySaledCom(Commodity* saledCom,QTableWidget* smallTable,int amount)
{
    int row=smallTable->rowCount();
    smallTable->insertRow(row); //新增一个空行
    //插入数据
    QString qNo=saledCom->getNo().c_str();
    smallTable->setItem(row,0,new QTableWidgetItem(qNo));
    smallTable->setItem(row,1,new QTableWidgetItem(saledCom->getName().c_str()));
    smallTable->setItem(row,2,new QTableWidgetItem(saledCom->getClassStr().c_str()));
    smallTable->setItem(row,3,new QTableWidgetItem(QString::number(saledCom->getPrice())));
    smallTable->setItem(row,4,new QTableWidgetItem(QString::number(amount)));
    smallTable->setItem(row,5,new QTableWidgetItem(QString::number(amount*saledCom->getPrice())));
}
