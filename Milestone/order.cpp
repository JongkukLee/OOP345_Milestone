// OOP345 Milestone 3: Order and Item
// File order.cpp
// Version 1.0
// Date 2017-07-28
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  1. Verify each of the item, and order data files from the project website are read successfully 
//     by your CSV file reader..
//  2. Copy Task.cpp to Item.cpp.
//  3. Hack Item.cpp to process item data : read it, parse it, print it, graph it.
//  4. Copy Item.cpp to Order.cpp
//  5. Hack Order.cpp to process order data : read it, parse it, print it, graph it.
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

using namespace std;

// Order class
class Order
{
	string orderCustomer, orderProduct;
	vector<string> itemsOrdered;
public:
	Order() {

	}
	Order(vector<string> line)
	{
			if (line.size() < 3)
			{
				throw string("Expected at least 1, 2, 3 fields, found ") + to_string(line.size());
			}

			orderCustomer = line[0];
			orderProduct  = line[1];

			for (size_t item = 2; item < line.size(); item++)
			{
				if (validItemName(line[item]))
					itemsOrdered.push_back(line[item]);
				else
					throw string("Expected item name, found '") + line[item] + "'";
			}
	}
	void print()
	{
#if 1
		cout << "customer='" << orderCustomer << "'";
		cout << " product='" << orderProduct << "'";

		for(auto& item: itemsOrdered)
			cout << " item='" << item << "'";

		cout << endl;
#endif
	}

	void graph(fstream& gv)
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
};

// Order Manager Class
class OrderManager
{
	vector< Order > orderList;
public:
	OrderManager(vector<vector<string> > & csvDataOrder)
	{
		for (auto& line : csvDataOrder)
		{
			try {
				orderList.push_back(move(line));
			}
			catch (string& e)
			{
				cerr << "OrderManager::OrderManager(vector<vector<string> > & csvDataOrder)" << e << endl;

			}
		}
	}

	void print()
	{

		for (auto& order : orderList)
			order.print();
	}

	void graph(string& f)
	{
		fstream gv(f + ".gv", ios::out | ios::trunc);
		if (gv.is_open())
		{
			gv << "digraph orderGraph {\n";
			for (auto& order : orderList)
				order.graph(gv);

			gv << "}\n";
			gv.close();

			std::string cmd = "dot";
			cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";

			//string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe";
			//cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			cout << "Running ->" + cmd << "\n";
			system(cmd.c_str());
		}

	}

};
