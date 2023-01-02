#pragma once

#include<string>
#include<array>
class Commodity
{
protected:

    std::string _no;   //商品编号
    std::string _name; //商品名称
    std::string _brand;  //品牌
    std::string _manufacturer; //厂家
    double _price;  //价格
    double _cost;  // 成本
    int _amount;    //库存数量
    bool _onSale;  //是否在售
    int _saleCount; //销量
public:
    Commodity() = default;
    Commodity(std::string no, std::string name, std::string brand,
              std::string manufacturer, double price, double cost, int amount,bool onSale,int saleCount);
    virtual ~Commodity() = default;

    int getAmount(void);
    int getSaleCount(void);
    void setSaleCount(int c);
    std::string getManufacturer();
    double getPrice(void);
    void setPrice(double p);
    double getCost(void);
    std::string getNo(void);
    std::string getName(void);
    std::string getBrand(void);
    std::string getClassStr(void);//获得商品类型
    void setName(std::string name);
    void setCost(int c);
    void setManufacturer(std::string m);
    void setAmount(int a);
    bool onSale(void); //判断是否在售
    void setOffSale(); //下架商品
    void setBrand(std::string b);
    virtual int getKind(void)=0; //返回种类
    virtual double getWeiOrCapa(void)=0;//获得重量或容量
    virtual void setWeiOrCapa(double wc)=0;
    virtual std::string getKindStr(void)=0;
    virtual void setKind(int k)=0;  //重设商品类型
};

