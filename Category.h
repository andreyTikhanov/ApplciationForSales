#pragma once
#include<iostream>
#include<list>
#include"Item.h"
class Category {
public:
	std::string Title;
	std::list<Item>Items;
	Category();
	Category(std::string title) :Title{ title } {};

};
