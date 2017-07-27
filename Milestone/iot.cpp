#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "i.h"
#include "o.h"
#include "t.h"
#include "util.h"
/*
int main(int argc, char* argv[])
{
	// 
	// 
	argc = 5;
	argv[0] = "M1";
	argv[1] = "ItemList.dat";
	argv[2] = "CustomerOrders.dat";
	argv[3] = "FishTankTasks.dat";
	argv[4] = ",";


	if (argc != 5) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filenameItem = argv[1];
	string filenameOrder = argv[2];
	string filenameTask = argv[3];
	char   delimiter = argv[4][0];

	try 
	{
		vector< vector<string> > csvDataTask;
		vector< vector<string> > csvDataOrder;
		vector< vector<string> > csvDataItem;
		csvRead(filenameTask, delimiter, csvDataTask);
		csvRead(filenameOrder, delimiter, csvDataOrder);
		csvRead(filenameItem, delimiter, csvDataItem);
		//csvPrint(csvDataTask);

		ItemManager im(csvDataItem);
		im.print();
		im.graph(filenameItem);

		OrderManager om(csvDataOrder);
		om.print();
		om.graph(filenameOrder);
		

		TaskManager tm(csvDataTask);
		tm.print();
		tm.graph(filenameTask);
		
		
		if (im.validate(tm) && om.validate(im) && tm.validate())
		{
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			cout << "Data has referental integraty. GOOD TO GO.\n";
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";

		}
		else
		{
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			cerr << "Data has referental integraty Problem.\n";
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			throw string("Data has refeential integrity problem. FIX AND RE-SUBMIT!!!");
		}

		//im.validate(tm);
		//om.validate(im);
		//tm.validate();

	}
	catch (const string& e) 
	{
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}
}

*/
