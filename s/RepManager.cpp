
#include "head/RepManager.h"
#include<stdexcept>
#include<map>
#include<qdebug.h>

map<string,Commodity*> RepManager::_noComMap;

Commodity* RepManager::searchNo(std::string no)
{
    if (_noComMap.count(no) == 0)
    {
        throw runtime_error("不存在该商品");
    }
    return _noComMap[no];
}

Commodity* RepManager::searchNoAll(std::string no)
{
    for (auto& com : _repository)
    {
        if (no == com->getNo())
        {
            return com;
        }
    }
    return nullptr;
}

std::list<Commodity*> RepManager::searchName(std::string name)
{
    std::list<Commodity*> resList;//符合条件的商品
    auto check = [&](Commodity* c)
    {

        return c->getName().find(name) != string::npos;
    };
    for (auto com : _repository)
    {
        if (check(com)&&com->onSale())
        {
            resList.push_back(com);
        }
    }
    return resList;
}

std::list<Commodity*> RepManager::searchBrand(std::string brand)
{
    std::list<Commodity*> resList;
    for (auto com : _repository)
    {
        if (brand==com->getBrand()&&com->onSale())
        {
            resList.push_back(com);
        }
    }
    return resList;
}

std::list<Commodity *> RepManager::searchClass(char classCh)
{
    list<Commodity*> resList;
    for_each(_repository.begin(),_repository.end(),
             [&](Commodity* com)
    {
        if(com->onSale()&&com->getNo()[0]==classCh)
        {
            resList.push_back(com);
        }
    } );
    return resList;
}


bool RepManager::addFood(std::string name, std::string brand, 
                         std::string manufacturer, double price,
                         double cost, int amount, double weight, Food::FoodKind kind)
{

    Commodity* f = new Food(name, brand, manufacturer,
                            price, cost, amount, true, 0, weight, kind);
    _repository.push_back(f);
    _noComMap.insert(make_pair(f->getNo(), f));
    _sumCost+=amount*cost;
    return true;
}

bool RepManager::addCosmetic(std::string name, std::string brand, 
                             std::string manufacturer, double price, double cost, int amount,
                             double weight,Cosmetic::CosmeticKind kind)
{
    Commodity* c = new Cosmetic(name, brand, manufacturer,
                                price, cost, amount, true, 0, weight, kind);
    _repository.push_back(c);
    _noComMap.insert(make_pair(c->getNo(), c));
    _sumCost+=amount*cost;
    return true;
}

bool RepManager::addBeverage(string name, string brand, string manufacturer,
                             double price, double cost, int amount,
                             int capacity, Beverage::BeverageKind kind)
{

    Commodity* b = new Beverage(name, brand, manufacturer,
                                price, cost, amount, true, 0, capacity, kind);
    _repository.push_back(b);
    _noComMap.insert(make_pair(b->getNo(), b));
    _sumCost+=amount*cost;
    return true;

}

bool RepManager::addDaily(string name, string brand, string manufacturer,
                          double price, double cost, int amount,
                          double weight, Daily::DailyKind kind)
{

    Commodity* d = new Daily(name, brand, manufacturer,
                             price, cost, amount, true, 0, weight, kind);
    _repository.push_back(d);
    _noComMap.insert(make_pair(d->getNo(), d));
    _sumCost+=amount*cost;
    return true;
}

void RepManager::setAmount(std::string no, int newAmount)
{
    auto pCom = this->searchNo(no);
    int  oriAmount = pCom->getAmount();
    int delta = newAmount-oriAmount;
    pCom->setAmount(newAmount);
    _sumCost +=  delta*pCom->getCost();  //更新总成本
}

void RepManager::setPricre(std::string no, int newPrice)
{
    auto com = this->searchNo(no);
    com->setPrice(newPrice);
}

void RepManager::deleteCommodity(std::string no)
{
    auto com = this->searchNo(no);
    com->setOffSale();
    _sumCost-=com->getCost()*com->getAmount();
    _noComMap.erase(com->getNo());
}

void RepManager::loadRepository(void)
{
    ifstream ifs;
    ifs.open("food.txt");
    if (ifs.is_open())
    {
        Food* f;
        while (!ifs.eof())
        {
            f = new Food;
            ifs >> *f;
            _repository.push_back((Commodity*)f);
            if(f->onSale()) _noComMap.insert(make_pair(f->getNo(), (Commodity*)f));
            _sumCost+=f->getCost()*f->getAmount();
        }
    }
    ifs.close();
    
    ifs.open("cosmetic.txt");
    if (ifs.is_open())
    {
        Cosmetic* c;
        while (!ifs.eof())
        {
            c = new Cosmetic;
            ifs >> *c;
            _repository.push_back((Commodity*)c);
            if(c->onSale()) _noComMap.insert(make_pair(c->getNo(), (Commodity*)c));
            _sumCost+=c->getCost()*c->getAmount();

        }
    }
    ifs.close();

    ifs.open("beverage.txt");
    if (ifs.is_open())
    {
        Beverage* b;
        while (!ifs.eof())
        {
            b = new Beverage;
            ifs >> *b;
            _repository.push_back((Commodity*)b);
            if(b->onSale()) _noComMap.insert(make_pair(b->getNo(), (Commodity*)b));
            _sumCost+=b->getCost()*b->getAmount();
        }
    }
    ifs.close();

    ifs.open("daily.txt");
    if (ifs.is_open())
    {
        Daily* d;
        while (!ifs.eof())
        {
            d = new Daily;
            ifs >> *d;
            _repository.push_back((Commodity*)d);
            if(d->onSale()) _noComMap.insert(make_pair(d->getNo(), (Commodity*)d));
            _sumCost+=d->getCost()*d->getAmount();
        }
    }
    ifs.close();


    
}

void RepManager::saveRepository(void)
{
    if(_repository.size()==0)
    {
        return ;
    }
    map<char, ofstream*> files;  //商品种类和文件流的映射
    files['F'] = new ofstream;
    files['C'] = new ofstream;
    files['B'] = new ofstream;
    files['D'] = new ofstream;
    int nf = 0, nc = 0, nb = 0, nd = 0;
    for (auto& com : _repository)
    {
        auto& pFileStream = (files[com->getNo()[0]]);    //确定输出文件
        if (Food* f = dynamic_cast<Food*>(com); f)
        {
            if (nf++ != 0) *pFileStream<< endl; //不是第一个数据才 输出换行
            else pFileStream->open("food.txt", ios::out);  //真有数据写才打开文件
            *pFileStream << *f;
        }

        if (Cosmetic* c = dynamic_cast<Cosmetic*>(com); c)
        {
            if (nc++ != 0) *pFileStream << endl;
            else pFileStream->open("cosmetic.txt", ios::out);
            *pFileStream << *c;
        }

        if(Beverage * b = dynamic_cast<Beverage*>(com);b)
        {
            if(nb++!=0) *pFileStream << endl;
            else pFileStream->open("beverage.txt",ios::out);
            *pFileStream << *b;
        }

        if(Daily * d = dynamic_cast<Daily*>(com);d)
        {
            if(nd++!=0) *pFileStream << endl;
            else pFileStream->open("daily.txt",ios::out);
            *pFileStream << *d;
        }
    }
    for (auto& [k, f] : files)  //关闭所有文件
    {

        f->close();
        delete f;
    }
    
}
