#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
#include "i.h"

// customer name, product name, I1, I2, ......
class Order
{
	std::string orderCustomer, orderProduct;
	std::vector<string> itemsOrdered;
public:
	size_t count() { return itemsOrdered.size(); }
	std::string& item(size_t i) { return itemsOrdered[i]; }

	Order();
	Order(std::vector<string> line);
	void print();
	void graph(std::fstream& gv);
};

class OrderManager
{
	std::vector< Order > orderList;
public:
	OrderManager(std::vector<vector<string> > & csvDataOrder);
	void print();
	void graph(std::string& f);

	//Order* find(std::string i);
	bool validate(ItemManager& im);
};
