#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "t.h"
#include "util.h"
/*
int main(int argc, char* argv[])
{
	// 
	// 
	argc = 3;
	argv[0] = "M1";
	argv[1] = "FishTankTasks.dat";
	argv[2] = ",";
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filename = argv[1];
	char   delimiter = argv[2][0];

	try 
	{
		vector< vector<string> > csvDataTask;
		csvRead(filename, delimiter, csvDataTask);
		//csvPrint(csvDataTask);

		TaskManager tm(csvDataTask);
		tm.print();
		tm.graph(filename);
	}
	catch (const string& e) 
	{
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}
}
*/
