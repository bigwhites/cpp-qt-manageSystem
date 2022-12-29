#pragma execution_character_set("utf-8")
#include "head/Saler.h"
#include"head/RepManager.h"
#include<fstream>
#include<QMessageBox>
using namespace std;


vector<Manager::Commodities> Saler::_tradeComs;  //交易记录
vector<vector<int>> Saler::_tradeAmount;  //商品数量记录
vector<double>  Saler::_tradeIncome; //交易额记录
vector<vector<double>> Saler::_tradePrices;  //商品成交价格记录
vector<std::string> Saler::_tradeId; //交易号

long long Saler::_maxId = 100000;

int Saler::getPosition(std::string trid)
{
    if(trid.size()<9) throw runtime_error("非合法订单号");
    trid.erase(trid.begin(), trid.begin() + 3);
    long long  id = stoull(trid); //转为数字
    if (id < 0 || id - 100000 - 1 >= _tradeId.size())
    {
        throw runtime_error("没有该订单");
    }
    return id - 100000 - 1;  //对应数组下标
}

Saler::Saler()
{
    static bool first = true;
    if (first){
        //读取文件 获得记录
        first = false;
    }
    _income = 0;    //金额置为0
    _coms.clear();  //清除旧的记录
}

tuple<string,double> Saler::endBuy()
{
    _tradeAmount.push_back(move(_amount));
    _amount.clear();

    _tradePrices.push_back(move(_price));
    _price.clear();

    _tradeIncome.push_back(_income);

    _tradeComs.push_back(move(_coms));  // ? 不确定能不能这么写
    _coms.clear();

    _tradeId.push_back("Tr-" + to_string(++_maxId));
    auto res=_income;
    _income=0;
    return {*(_tradeId.end()-1),res}; //返回商品的总金额
}

bool Saler::buy(Commodity* com, int amount)
{
    if (com==nullptr || amount > com->getAmount())
    {
        throw runtime_error("库存不足");
        return false;  //商品库存不足已买这么多  或不存在该商品
    }
    else
    {
        bool noSame=true;
        for(int i = 0;auto boughtCom:_coms)  //若有重复则合并
        {
            if(boughtCom==com)
            {
                _amount[i]+=amount;
                noSame=false;
            }
            i++;
        }
        if(noSame)  //无重复则新增
        {
            _coms.push_back(com);
            _amount.push_back(amount);
            _price.push_back(com->getPrice());  //购买时的价格
        }
        com->setAmount(com->getAmount() - amount); //更新库存中的数量
        com->setSaleCount(com->getSaleCount() + amount);
        _sumRevenue += (com->getPrice()) * amount; //更新总营业额
        _income += (com->getPrice()) * amount;
    }
    return  true;
}

double Saler::locIncome()
{
    return _income;
}

void Saler::saveTradeRecord(void)
{
    ofstream ofs;
    ofs.open("tradeRecord.txt", ios::out);
    for (int i = 0; i < _tradeId.size(); ++i)
    {
        ofs << _tradeId[i] << " " << _tradeIncome[i] << " " << _tradeComs[i].size() << endl;
        for (int j = 0; j < _tradeComs[i].size(); ++j)
        {
            ofs << _tradeComs[i][j]->getNo() << " " << _tradeAmount[i][j] << " " << _tradePrices[i][j] << endl;
        }
        ofs << endl;
    }
    ofs.close();
}

void Saler::loadTradeRecord(void)
{
    ifstream ifs;
    RepManager rm;
    ifs.open("tradeRecord.txt");
    if (!ifs.is_open())
    {
        // TODO
        return;
    }
    clearRecord();
    int i = 0;
    string trId, no;
    double trIncome;
    int n; //购买商品种数
    while (ifs >> trId >> trIncome >> n)
    {
        Manager::_sumRevenue += trIncome;  //总营业额增加
        _tradeComs.push_back(move(Commodities(n)));
        _tradeAmount.push_back(move(vector<int>(n)));
        _tradePrices.push_back(move(vector<double>(n)));
        _tradeId.push_back(trId);
        _tradeIncome.push_back(trIncome);
        for (int j = 0; j < n; ++j)
        {
            ifs >> no >> _tradeAmount[i][j] >> _tradePrices[i][j];
            _tradeComs[i][j] = rm.searchNoAll(no);
        }
        i++;
        ++_maxId;
    }
    ifs.close();
}

void Saler::clearRecord()
{
    //清空所有的记录
    _tradeComs.clear();
    _tradeAmount.clear();
    _tradeIncome.clear();
    _tradeId.clear();
    _tradePrices.clear();
    _maxId = 100000;
}

void Saler::reSetTrRecord(const string& trid, Commodity* com, int newAmount)
{
    int pos = getPosition(trid);
    bool noFind = true;
    for (int i = 0; i < _tradeAmount[pos].size(); ++i)//在记录中寻找
    {
        if (com == nullptr || _tradeComs[pos][i] == com) //找到该商品 或需要全部删除
        {
            noFind = false;

            int delta = newAmount - _tradeAmount[pos][i];  //新旧数量差距
            if (delta > 0 && com->getAmount() < delta)
            {
                throw("当前库存不足，无法修改");
            }
            Manager::_sumRevenue += delta * _tradePrices[pos][i]; //更新总收入
            _tradeIncome[pos] += delta * _tradePrices[pos][i];  //更新交易额
            if (newAmount != 0)  //新数量不为零时更新数量
            {
                _tradeAmount[pos][i] = newAmount;
            }
            _tradeComs[pos][i]->setAmount(_tradeComs[pos][i]->getAmount() - delta);  //更新库存数量
            _tradeComs[pos][i]->setSaleCount(_tradeComs[pos][i]->getSaleCount() + delta);//更新商品的销量记录
            if (newAmount == 0) ///等于0时清除数据
            {
                _tradeComs[pos].erase(_tradeComs[pos].begin() + i);
                _tradePrices[pos].erase(_tradePrices[pos].begin() + i);
                _tradeAmount[pos].erase(_tradeAmount[pos].begin() + i);
                --i;//有数据删除时指针不移动
            }
        }
    }
    if (com != nullptr && noFind) throw runtime_error("未购买该商品");
}

void Saler::showRecord(string trid, QTableWidget *table)
{
    int pos;
    pos = getPosition(trid);
    while(table->rowCount()>=1)  //清空原行
    {
        table->removeRow(table->rowCount()-1);
    }
    int row=table->rowCount();
    if(_tradeComs[pos].size()==0)
    {
        throw runtime_error("没有该订单");
    }
    for(int i=0;i<_tradeComs[pos].size();++i)
    {
        auto com=_tradeComs[pos][i];
        table->insertRow(row);
        QString qNo=com->getNo().c_str();
        table->setItem(row,0,new QTableWidgetItem(qNo));
        table->setItem(row,1,new QTableWidgetItem(com->getName().c_str()));
        table->setItem(row,2,new QTableWidgetItem((qNo[0])));
        table->setItem(row,3,new QTableWidgetItem(QString::number(_tradePrices[pos][i])));
        table->setItem(row,4,new QTableWidgetItem(QString::number(_tradeAmount[pos][i])));
        double totalPrice = _tradePrices[pos][i]*_tradeAmount[pos][i];
        table->setItem(row,5,new QTableWidgetItem(QString::number(totalPrice)));
        ++row;
    }
}

double Saler::getTradeIncome(const string &trid)
{
    return _tradeIncome[getPosition(trid)];
}

QStringList Saler::getNoList(const string &trid)
{
    QStringList noList;
    int pos=getPosition(trid);
    for(auto com:_tradeComs[pos])
    {
        noList<<com->getNo().c_str();
    }
    return move(noList);
}

string Saler::getLastTrid(const string &trid)
{
    int pos = this->getPosition(trid);
    --pos;
    for(;pos>=0;--pos)
    {
       if(_tradeComs[pos].size()!=0)
       {
           return _tradeId[pos];
       }
    }
    throw runtime_error("没有上一条！");
}

string Saler::getNextTrid(const string &trid)
{
    int pos = this->getPosition(trid);
    ++pos;
    for(;pos<_tradeComs.size();++pos)
    {
       if(_tradeComs[pos].size()!=0)
       {
           return _tradeId[pos];
       }
    }
    throw runtime_error("没有下一条！");
}


