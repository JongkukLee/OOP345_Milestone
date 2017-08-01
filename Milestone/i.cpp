// OOP345 Milestone 4: Assembly Line
// File i.cpp
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
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
#include "i.h"

	Item::Item() {

	}
	Item::Item(std::vector<string> line)
	{
		switch (line.size())
		{
		case 5:
			itemDecription = line[4];
		case 4:
			if (validItemSequence(line[3]))
				itemSequence = line[3];
			else
				throw std::string("Expected fail item sequence, found '") + line[3] + "'";
		case 3:
			if (validItemName(line[2]))
				itemRemover = line[2];
			else
				throw std::string("Expected fail item name, found '") + line[2] + "'";
		case 2:
			if (validItemName(line[1]))
				itemInstaller = line[1];
			else
				throw std::string("Expected fail item slots, found '") + line[1] + "'";
		case 1:
			if (validItemName(line[0]))
				itemName = line[0];
			else
				throw std::string("Expected fail item name, found '") + line[0] + "'";
			break;
		default:
			throw std::string("Expected 1, 2, 3, 4 fields, found ") + to_string(line.size());
		}
	}
	void Item::print()
	{
		std::cout << "item=" << itemName << ", ";
		std::cout << "installer=" << itemInstaller << ", ";
		std::cout << "remover=" << itemRemover << ", ";
		std::cout << "sequence=" << itemSequence << ", ";
		std::cout << "decription=" << itemDecription << "\n";
		std::cout << endl;
	}

	void Item::graph(fstream& gv)
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

	ItemManager::ItemManager(std::vector<vector<string> > & csvDataItem)
	{
		for (auto& line : csvDataItem)
		{
			try {
				itemList.push_back(move(line));
			}
			catch (std::string& e)
			{
				cerr << "ItemManager::ItemManager(vector<vector<string> > & csvDataItem)" << e << endl;

			}
		}
	}

	void ItemManager::print()
	{

		for (auto& item : itemList)
			item.print();
	}

	void ItemManager::graph(std::string& f)
	{
		std::fstream gv(f + ".gv", std::ios::out | std::ios::trunc);
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

	// find task name
	Item* ItemManager::find(std::string item)
	{
		for (size_t i = 0; i < itemList.size(); i++)
		{
			if (itemList[i].name() == item)
				return &itemList[i];
		}
		return nullptr;
	}
	// 
	bool ItemManager::validate(TaskManager& tm)
	{
		int errors = 0;
		for (auto& item : itemList)
		{
			std::string installer = item.installer();
			if (!installer.empty() && tm.find(installer) == nullptr)
			{
				errors++;
				std::cerr << "[" << __FILE__ << "]\n\tCannot find an intaller task [" << installer << "]\n";
			}
			std::string remover = item.remover();
			if (!remover.empty() && tm.find(remover) == nullptr)
			{
				errors++;
				std::cerr << "[" << __FILE__ << "]\n\tCannot find a remover [" << remover << "]\n";
			}
		}
		//return errors === 0;
		return errors == 0;
	}
