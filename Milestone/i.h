#pragma once
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
	ItemManager(std::vector<vector<string> > & csvDataItem);
	void print();
	void graph(std::string& f);


	Item* find(std::string t);
	bool validate(TaskManager& tm);
};
