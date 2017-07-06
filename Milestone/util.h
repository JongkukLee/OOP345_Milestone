#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//class util
//{

//public:
	void csvPrint(vector< vector<string> > & csvData);

	void TrimSpaces(string& s);

	void csvRead(string& filename, char delimiter, vector< vector<string> > & csvData);
	bool validTaskName(std::string&);
	bool validTaskSlots(std::string&);

//};