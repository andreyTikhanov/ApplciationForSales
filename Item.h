#pragma once
#include<iostream>
class Item {
public:
	std::string Title;
	unsigned int Price;		
	Item();
	Item(std::string title,unsigned int price) : Title{ title }, Price{ price }{}


};
