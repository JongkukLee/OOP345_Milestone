#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"
#include "i.h"

using namespace std;

/*
int main(int argc, char* argv[])
{
	// 
	// 
	argc = 3;
	argv[0] = "M1";
	argv[1] = "ItemList.dat";
	argv[2] = "|";
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filename = argv[1];
	char   delimiter = argv[2][0];

	try
	{
		vector< vector<string> > csvDataItem;
		csvRead(filename, delimiter, csvDataItem);
		csvPrint(csvDataItem);

		ItemManager im(csvDataItem);
		im.print();
		im.graph(filename);
	}
	catch (const string& e)
	{
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}
}
*/
