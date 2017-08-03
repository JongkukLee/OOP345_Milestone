// OOP345 Milestone 4: Assembly Line
// File i.h
// Version 1.0
// Date 2017-08-04
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  splitting (code factoring) the item.cpp files into i.h/i.cpp files.
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef I_H
#define I_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
#include "t.h"

class Item
{
	std::string itemName, itemInstaller, itemRemover, itemSequence, itemDecription;
public:
	std::string& name() { return itemName; }
	std::string& installer() { return itemInstaller; }
	std::string& remover() { return itemRemover; }

	Item();
	Item(std::vector<string> line);
	void print();
	void graph(std::fstream& gv);
};

class ItemManager
{
	std::vector< Item > itemList;
public:
	size_t count() { return itemList.size(); }
	Item& item(size_t i) { return itemList[i]; }

	ItemManager(std::vector<vector<string> > & csvDataItem);
	void print();
	void graph(std::string& f);


	Item* find(std::string t);
	bool validate(TaskManager& tm);
};
#endif