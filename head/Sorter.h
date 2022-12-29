#pragma once
#include "Manager.h"
#include"ui_mainwindow.h"
class Sorter :public Manager
{
public:
	Sorter() = default;
	~Sorter() = default;
	enum class SortKey
	{
		PRICE_UP, PRICE_DOWN,
		AMOUNT_UP, AMOUNT_DOWN,
		NAME_UP, NAME_DOWN,
		SALE_CNT_UP,SALE_CNT_DOWN
	};
    void operator()(SortKey key,QTableWidget* comTab);  //排序并显示
protected:
    Commodities _onSalecoms; //当前在售的商品（未被删除的）
	void copyComs();  //拷贝一份商品数据
	void _sort(SortKey key);  //按照指定的规则排序
};

