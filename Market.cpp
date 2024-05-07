#include"Market.h"
#include<fstream>
#include<string>
bool Market::LoadOrders() {
	return false;
}
bool Market::LoadPersons() {
	return false;
}
bool Market::LoadShop() {
	std::ifstream inFile;
	inFile.open("shop.csv");
	std::string input;

	if (inFile.is_open()) {
		while (std::getline(inFile, input)) {
			std::string ch = "";
			std::string str[3];
			int j = 0;
			int i = 0;
			while (j < input.length()) {
				ch = input[j];
				if (ch == ";") {
					i++;
				}
				else {
					str[i] += input[j];
				}
				j++;
			}
			Item item;
			item.Title = str[1];
			item.Price = std::atoi(str[2].c_str());
			bool isFind = false;
			std::list<Category>::iterator cat = Shop.begin();
			for (; cat != Shop.end(); cat++) {
				if (cat->Title == str[0]) {
					cat->Items.push_back(item);
					isFind = true;
					break;
				}
			}
			if (!isFind) {
				Category cat;
				cat.Title = str[0];
				cat.Items.push_back(item);
				Shop.push_back(cat);
			}
		}
			
	}
	inFile.close();
	return true;
}
bool Market::SaveOrders() {
	return false;
}
bool Market::SavePersons() {
	return false;
}
bool Market::SaveShop() {
	//сохранение ассортимента магазина
	std::ofstream outFile;
	outFile.open("Shop.csv");
	Category category;
	for(auto const& category: Shop) {
		for (auto const& item : category.Items) {
			outFile << category.Title << ";" << item.Title << ";" << item.Price << std::endl;
		}
	}
	outFile.close();
	return true;
}