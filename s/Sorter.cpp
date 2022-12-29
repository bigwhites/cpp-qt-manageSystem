#include "head/Sorter.h"
#include<algorithm>
#include<iostream>
#include<functional>
using namespace std;

void Sorter::operator()(SortKey key,QTableWidget* comTab)
{
	copyComs();
	_sort(key);
    while(comTab->rowCount()>=1)
    {
        comTab->removeRow(comTab->rowCount()-1);
    }
    for(auto& com:_onSalecoms)//显示排序结果
    {
        Manager::displayRepCom(com,comTab);
    }
}

void Sorter::copyComs()
{
	for (auto& com : _repository)
	{
		if (com->onSale())
		{
			_onSalecoms.push_back(com);
		}
	}
}

void Sorter::_sort(SortKey key)
{
	function<bool(Commodity* c1, Commodity* c2)> cmp;

	if ((int)key == 0 || (int)key == 1)
	{
		cmp = [](Commodity* c1, Commodity* c2)
		{
			return c1->getPrice() < c2->getPrice();
		};
	}
	else if ((int)key == 2 || (int)key == 3)
	{
		cmp = [](Commodity* c1, Commodity* c2)
		{
			return c1->getAmount() < c2->getAmount();
		};
	}
	else if ((int)key == 4 || (int)key == 5) 
	{

		cmp = [](Commodity* c1, Commodity* c2)
		{
			return c1->getName() < c2->getName();
		};
	}
	else
	{
		cmp = [](Commodity* c1, Commodity* c2)
		{
			return c1->getSaleCount() < c2->getSaleCount();
		};
	}

	if ((int)key % 2 == 0)  //升序
	{
		sort(_onSalecoms.begin(), _onSalecoms.end(), cmp);
	}
	else  //降序
	{
		sort(_onSalecoms.rbegin(), _onSalecoms.rend(), cmp);
	}
}

