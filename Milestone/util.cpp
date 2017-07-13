#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
//#include "util.h"

void csvPrint(std::vector< std::vector<std::string> > & csvData)
{
	std::cout << "range-based for:\n";
	for (auto line : csvData) {
		for (auto field : line)
			std::cout << "(" << field << ")";
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "for with iterators:\n";
	for (auto line = csvData.begin(); line != csvData.end(); line++) {
		for (auto field = line->begin(); field != line->end(); field++)
			std::cout << "[" << *field << "]";
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "for with indices:\n";
	for (size_t line = 0; line < csvData.size(); line++) {
		for (size_t field = 0; field < csvData[line].size(); field++)
			std::cout << "<" << csvData[line][field] << ">";
		std::cout << "\n";
	}
	std::cout << "\n";

}

void TrimSpaces(std::string& s)
{
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1, 1);
}

void csvRead(std::string& filename, char delimiter, std::vector< std::vector<std::string> > & csvData)
{

	std::cout << "filename='" << filename << "', delimiter=<" << delimiter << ">\n";

	std::fstream in(filename, std::ios::in);
	if (in.is_open()) {

		std::string line;
		while (getline(in, line)) {
			auto cr = line.find('\r');
			if (cr != std::string::npos)
				line.erase(cr);

			std::string field;
			size_t index = 0;
			std::vector< std::string > fields;
			while (index < line.size()) {
				if (line[index] == delimiter) {
					TrimSpaces(field);
					fields.push_back(move(field));
				}
				else {
					field += line[index];
				}
				index++;
			}
			TrimSpaces(field);
			fields.push_back(move(field));

			csvData.push_back(move(fields));
		}

		in.close();
	}
	else {
		throw std::string("Cannot open file '") + filename + "'";
	}
}

bool validTaskName(std::string& s)
{
	if (s.empty())
		return false;

	for (auto c : s)
	{
		if (! (isalnum(c) || c == ' '))
			return false;
	}
	return true;
}

bool validTaskSlots(std::string& s)
{
	if (s.empty())
		return false;

	for (auto c : s)
	{
		if (! (isdigit(c) || c == ' '))
			return false;
	}
	return true;
}

bool validItemName(std::string& s)
{
	if (s.empty())
		return false;

	for (auto c : s)
	{
		if (!(isalnum(c) || c == ' '))
			return false;
	}
	return true;
}

bool validItemSequence(std::string& s)
{
	if (s.empty())
		return false;

	for (auto c : s)
	{
		if (!(isdigit(c) || c == ' '))
			return false;
	}
	return true;
}