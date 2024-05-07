#pragma once
#include<iostream>
#include<list>
#include"Category.h"
#include"User.h"
#include"Order.h"
class Market {
public:
	std::list<Category>Shop;
	std::list<User>Persons;
	std::list<Order>Orders;
	bool SavePersons();
	bool SaveOrders();
	bool SaveShop();
	bool LoadPersons();
	bool LoadOrders();
	bool LoadShop();

};
