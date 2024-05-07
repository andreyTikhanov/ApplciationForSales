#define _CRT_SECURE_NO_WARNINGS	
#include <iostream>
#include"Category.h"
#include"User.h"
#include"Order.h"
#include"Market.h"
#include<SFML/Graphics.hpp>	
#include<list>



int main(){
	system("chcp 1251 | cls");
	setlocale(LC_ALL, "");
	Market market;	
	market.LoadShop();
	const int W_WIDTH = 640;
	const int W_HEIGHT =480;
	const int ROWS = 4;
	const int COLS = 5;
	sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), L"Кофейня",
		sf::Style::Default);
	//sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Full",	//для полноэкранного режима, чтобы закрыть alt+f4
		//sf::Style::Fullscreen);
	window.setFramerateLimit(30);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(font);
	int textFonSize = (W_WIDTH + W_HEIGHT) / 2 / 26;
	int coord = 0;
	//0-категории, 1-товары, 2 -корзина
	int state = 0;
	int w = W_WIDTH / COLS;
	int h = W_HEIGHT / ROWS;
	Order order;
	Category currentCategory ;
	Item currentItem;

	int currentPrice = 0;
	while (window.isOpen()) {
		sf::Color color(185, 130, 36);
		window.clear(color);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				int x = sf::Mouse::getPosition(window).x/w;
				int y = sf::Mouse::getPosition(window).y/h;
				coord = x * ROWS + y;
				window.setTitle(std::to_string(coord));
				if (coord == 17) {
					state = 2;
				}
				//window.setTitle(
					//"X= " + std::to_string(x + 1) +
					//", Y=" + std::to_string(y + 1));
				if (state == 0) {
					state += 1;
					int index = 0;
					for (auto const& cat : market.Shop) {
						if (index == coord) {
							currentCategory = cat;
							break;
						}
						index++;
					}
				}
				else if (state == 1) {
					int index = 0;
					
					for (auto const& item : currentCategory.Items) {
						if (index == coord) {
							currentItem = item;
							order.Items.push_back(item);
							break;
						}
						index++;
					}
					
				}
				else if (state == 2) {
					int x = sf::Mouse::getPosition(window).x;
					int y = sf::Mouse::getPosition(window).y;
					int lineNumber = (y / (textFonSize * 1.4))-2;
					int index = 0;
					if (lineNumber < order.Items.size()
						&& x<w*(COLS-1)) {
						std::list < Item>::iterator it = order.Items.begin();
						while (index != lineNumber) {
							it++;
							index++;
						}
						order.Items.erase(it);
					}
					//window.setTitle("line: " + std::to_string(lineNumber));
					if (x >= 0 && x < w && y >= h * 3 && y <= h * 3.5) {
						window.setTitle("button1");
						order.Status = "Card";
						order.DateTime = time(NULL);
						order.SaveOrder();
						order.Clear();
						state = 0;
					}
					else if (x > w && x <w * 2  && y >= h * 3 && y <= h * 3.5) {
						window.setTitle("button2");
						order.Status = "Cash";
						order.DateTime = time(NULL);
						order.SaveOrder();
						order.Clear();
						state = 0;
					}
					else if (x > w * 2 && x <w *3 && y>= h*3 && y <=h *3.5) {
						window.setTitle("button3");
						order.Status = "Cancel";
						order.DateTime = time(NULL);
						order.SaveOrder();
						order.Clear();
						state = 0;
					}
				}
				if (coord == 19) {
					state = 0;
				}
				//window.setTitle("Coord = " + std::to_string(coord));
			}
		}
		text.setCharacterSize(textFonSize);
		text.setFillColor(sf::Color::White);

		int x = 0, y = 0;
		if (state == 0) {
			for (auto const& cat : market.Shop) {
				sf::String title = sf::String::fromUtf8(cat.Title.begin(), cat.Title.end());
				title.replace(" ", "\n");
				text.setString(title);
				text.setPosition(x * w + 20, y++ * h +  + 35);
				if (y == ROWS) { x++;  y=0; }
				window.draw(text);
			}
		}
		else if (state == 1) {
			for (auto const& item : currentCategory.Items) {
				sf::String title = sf::String::fromUtf8(item.Title.begin(), item.Title.end());
				title.replace(" ", "\n");
				text.setString(title);
				text.setPosition(x * w + 20, y++ * h + +35);
				if (y == ROWS) { x++; y=0; }
				window.draw(text);
			}
			text.setString(L"НАЗАД");
			text.setPosition(W_WIDTH - w + 20, W_HEIGHT - h + 20);
			window.draw(text);
		}
		else if (state == 2) {
			//отрисовка корзины - заказа
			text.setString(L"Заказ: ");
			text.setPosition(w / 2, 20);
			window.draw(text);
			int index = 1;
			for (auto const& item : order.Items) {
				sf::String title = sf::String::fromUtf8(item.Title.begin(), item.Title.end());
				title = std::to_string(index) + ". " + title + " - ";
				title += std::to_string(item.Price);
				text.setString(title);
				text.setPosition(w / 2- 20, 20 + index * textFonSize * 1.4);
				window.draw(text);
				index++;
			}
			sf::RectangleShape button1(sf::Vector2f(w, h/2));
			button1.setPosition(0, h * 3);
			button1.setFillColor(sf::Color::Blue);
			text.setString(L"Картой");
			text.setPosition(textFonSize, h * 3 + textFonSize*.7);
			window.draw(button1);
			window.draw(text);

			sf::RectangleShape button2(sf::Vector2f(w, h/2));
			button2.setPosition(w, h * 3);
			button2.setFillColor(sf::Color::Green);
			text.setString(L"Наличные");
			text.setPosition( w+ textFonSize, h*3 +textFonSize*.7);
			window.draw(button2);
			window.draw(text);

			sf::RectangleShape button3(sf::Vector2f(w, h/2));
			button3.setPosition(w*2 ,h*3 );
			button3.setFillColor(sf::Color::Red);
			text.setString(L"Отмена");
			text.setPosition(w*2 +  textFonSize, h * 3 + textFonSize * .7);
			window.draw(button3);
			window.draw(text);
			text.setString(L"НАЗАД");
			text.setPosition(W_WIDTH - w + 20, W_HEIGHT - h + 20);
			window.draw(text);
		}
		if (order.Items.size() > 0) {
			text.setString(std::to_string(order.Items.size()));
			text.setPosition(W_WIDTH - 100, W_HEIGHT / ROWS + 5);
			window.draw(text);
			text.setString(std::to_string(order.GetTotalSum()) + "P");
			text.setPosition(W_WIDTH - 100, W_HEIGHT / ROWS + 35);
			window.draw(text);
		}
		if (state != 2) {
			for (int i = 0; i < W_HEIGHT; i += W_HEIGHT / ROWS) {
				sf::RectangleShape line(sf::Vector2f(W_WIDTH, 1));
				line.setPosition(0, i);
				window.draw(line);
			}
			for (int i = 0; i < W_WIDTH; i += W_WIDTH / COLS) {
				sf::RectangleShape l(sf::Vector2f(W_HEIGHT, 1));
				l.setPosition(i, 0);
				l.rotate(90);
				window.draw(l);

			}
		}
		window.display();
	}
	market.SaveShop();
	
	
	/*
	 {
		//std::cout << cat.Title << std::endl;
		for (auto const& item : cat.Items) {
			//std::cout << "|-------" << item.Title << " : " << item.Price << std::endl;
		}
	}
	Order order;
	order.Items.push_back(market.Shop.front().Items.front());
	order.Status = "Оплата наличными";
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	*/
	/*
	Item item("Кофе", 250);
	Item item2("Американо", 90);
	Item item3("Капучино", 120);
	Item item4("Лимонад", 80);
	Item item5("Сок яблочный", 110);
	Category cat1;
	cat1.Title = "Горячие напитки";
	cat1.Items.push_back(item);
	cat1.Items.push_back(item2);
	cat1.Items.push_back(item3);
	Category cat2;
	cat2.Title = "Холодные напитки";
	cat2.Items.push_back(item4);
	cat2.Items.push_back(item5);
	market.Shop.push_back(cat1);
	market.Shop.push_back(cat2);
	market.SaveShop();
	*/
	/*
	Category cat;
	Item item;
	cat.Title = "Горячие напитки";

	item.Title = "Кофе Раф Сникерс 270 мл";
	item.Price = 250;
	cat.Items.push_back(item);
	std::cout << cat.Title;
	User user;
	user.Id = 324;
	user.Login = "Ivan";
	user.Name = "Иван Иванов";
	user.Password = "1234";
	Order order;
	order.Person = user;
	order.Status = "Оплачено картой";
	order.TotalSum = 234;
	*/
}

