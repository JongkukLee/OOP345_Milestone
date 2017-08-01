// OOP345 Milestone 3: Order and Item
// File item.cpp
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

// Item class
class Item
{
	string itemName, itemInstaller, itemRemover, itemSequence, itemDecription;
public:
	Item() {

	}
	Item(vector<string> line)
	{
		switch (line.size())
		{
		case 5:
			itemDecription = line[4];
		case 4:
			if (validItemSequence(line[3]))
				itemSequence = line[3];
			else
				throw string("Expected fail item sequence, found '") + line[3] + "'";
		case 3:
			if (validItemName(line[2]))
				itemRemover = line[2];
			else
				throw string("Expected fail item name, found '") + line[2] + "'";
		case 2:
			if (validItemName(line[1]))
				itemInstaller = line[1];
			else
				throw string("Expected fail item slots, found '") + line[1] + "'";
		case 1:
			if (validItemName(line[0]))
				itemName = line[0];
			else
				throw string("Expected fail item name, found '") + line[0] + "'";
			break;
		default:
			throw string("Expected 1, 2, 3, 4 fields, found ") + to_string(line.size());
		}
	}
	void print()
	{
		cout << "item=" << itemName << "";
		cout << "installer=" << itemInstaller << "";
		cout << "remover=" << itemRemover << "";
		cout << "sequence=" << itemSequence << "";
		cout << "decription=" << itemDecription << "";
		cout << endl;
	}

	void graph(fstream& gv)
	{
		//if (!itemInstaller.empty())
		//{
			gv << '"' << "Item " << itemName << '"';
			gv << " -> ";
			gv << '"' << "Installer " << itemInstaller << '"';
			gv << " [color=green]";

			gv << ";\n";
		//}

		//if (!itemRemover.empty())
		//{
			gv << '"' << "Item " << itemName << '"';
			gv << " -> ";
			gv << '"' << "Remover " << itemRemover << '"';
			gv << " [color=red]";
			gv << ";\n";
		//}

		//if (itemInstaller.empty() && itemRemover.empty())
		//{
		//	gv << '"' << itemName << '"';
		//	gv << " [shape=box]";
		//	gv << ";\n";
		//}
	}
};

// Item Manager class
class ItemManager
{
	vector< Item > itemList;
public:
	ItemManager(vector<vector<string> > & csvDataItem)
	{
		for (auto& line : csvDataItem)
		{
			try {
				itemList.push_back(move(line));
			}
			catch (string& e)
			{
				cerr << "ItemManager::ItemManager(vector<vector<string> > & csvDataItem)" << e << endl;

			}
		}
	}

	void print()
	{

		for (auto& item : itemList)
			item.print();
	}

	void graph(string& f)
	{
		fstream gv(f + ".gv", ios::out | ios::trunc);
		if (gv.is_open())
		{
			gv << "digraph itemGraph {\n";
			for (auto& item : itemList)
				item.graph(gv);

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
