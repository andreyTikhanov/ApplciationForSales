#pragma once
#include<iostream>
#include"Category.h"
#include"User.h"
class Order {
private:
	int TotalSum;
public:
	time_t DateTime;
	std::string Person;
	std::string Status;
	std::list<Item>Items;
	int GetTotalSum();
	void Clear();
	bool SaveOrder();
};
