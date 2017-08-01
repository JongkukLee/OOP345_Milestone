// OOP345 Milestone 4: Assembly Line
// File o.h
// Version 1.0
// Date 2017-08-04
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  splitting (code factoring) the order.cpp files into o.h/o.cpp files
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef O_H
#define O_H

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
	size_t count() { return orderList.size(); }
	Order& order(size_t o) { return orderList[o]; }
	OrderManager() {


	}

	OrderManager(std::vector<vector<string> > & csvDataOrder);
	void print();
	void graph(std::string& f);

	//Order* find(std::string i);
	bool validate(ItemManager& im);
};
#endif