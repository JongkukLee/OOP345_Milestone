// OOP345 Milestone 2: Tasks
// File util.h
// Version 1.0
// Date 2017-07-14
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//      read and print CSV file
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

using namespace std;

void csvPrint(vector< vector<string> > & csvData);

void TrimSpaces(string& s);

void csvRead(string& filename, char delimiter, vector< vector<string> > & csvData);
bool validTaskName(std::string&);
bool validTaskSlots(std::string&);

bool validItemName(std::string&);
bool validItemSequence(std::string&);
