// OOP345 Milestone 4: Assembly Line
// File o.cpp
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
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
#include "o.h"

	Order::Order() {

	}
	Order::Order(std::vector<string> line)
	{
			if (line.size() < 3)
			{
				throw std::string("Expected at least 1, 2, 3 fields, found ") + to_string(line.size());
			}

			orderCustomer = line[0];
			orderProduct  = line[1];

			for (size_t item = 2; item < line.size(); item++)
			{
				if (validItemName(line[item]))
					itemsOrdered.push_back(line[item]);
				else
					throw std::string("Expected item name, found '") + line[item] + "'";
			}
	}
	void Order::print()
	{
#if 1
		std::cout << "customer=" << orderCustomer << ", ";
		std::cout << " product=" << orderProduct << ", ";

		for(auto& item: itemsOrdered)
			std::cout << " item=" << item << ", ";

		std::cout << endl;
#endif
	}

	void Order::graph(std::fstream& gv)
	{
		//if (!orderInstaller.empty())
		//{

		for (auto& item : itemsOrdered)
		{
			gv << '"' << orderCustomer << " " << orderProduct << '"';
			gv << " -> ";
			gv << '"' << "Item " << item << '"';
			gv << " [color=blue]";

			gv << ";\n";
		}
		//}
	}

	OrderManager::OrderManager(std::vector<vector<string> > & csvDataOrder)
	{
		for (auto& line : csvDataOrder)
		{
			try {
				orderList.push_back(move(line));
			}
			catch (std::string& e)
			{
				cerr << "OrderManager::OrderManager(vector<vector<string> > & csvDataOrder)" << e << endl;

			}
		}
	}

	void OrderManager::print()
	{

		for (auto& order : orderList)
			order.print();
	}

	void OrderManager::graph(std::string& f)
	{
		std::fstream gv(f + ".gv", ios::out | ios::trunc);
		if (gv.is_open())
		{
			gv << "digraph orderGraph {\n";
			for (auto& order : orderList)
				order.graph(gv);

			gv << "}\n";
			gv.close();

			std::string cmd = "dot";
			cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";

			//std::string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe";
			//cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			cout << "Running ->" + cmd << "\n";
			system(cmd.c_str());
		}

	}

	bool OrderManager::validate(ItemManager& im)
	{
		int errors = 0;

		for (auto& order : orderList)
		{
			size_t count = order.count();
			for (size_t i = 0; i < count; i++)
			{
				if (im.find(order.item(i)) == nullptr)
				{
					errors++;
					std::cerr << "[" << __FILE__ << "]\n\tcannot find ordered item '" << order.item(i) << "'\n";

				}

			}

		}
		return errors == 0;
	}
