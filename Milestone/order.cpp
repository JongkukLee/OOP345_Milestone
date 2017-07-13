#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

// customer name, product name, I1, I2, ......
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
			gv << '"' << orderCustomer << "\n" << orderProduct << '"';
			gv << " -> ";
			gv << '"' << "Item\n" << item << '"';
			gv << " [color=blue]";

			gv << ";\n";
		}
		//}
	}
};

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

			string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe";
			cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			cout << "Running ->" + cmd << "\n";
			system(cmd.c_str());
		}

	}

};


int main(int argc, char* argv[])
{
	// 
	// 
	argc = 3;
	argv[0] = "M1";
	argv[1] = "CustomerOrders.dat";
	argv[2] = "|";
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filename = argv[1];
	char   delimiter = argv[2][0];

	try
	{
		vector< vector<string> > csvDataOrder;
		csvRead(filename, delimiter, csvDataOrder);
		csvPrint(csvDataOrder);

		OrderManager im(csvDataOrder);
		im.print();
		im.graph(filename);
	}
	catch (const string& e)
	{
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}
}
