// OOP345 Milestone 2: Tasks
// File Tasks.cpp
// Version 1.0
// Date 2017-07-14
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//	1. Using the CSV reader, read the task data files from the project website.  
//	2. Create a file Task.cpp that defines a pair of classes to hold the task data. 
//	3. The task data type requires a 'manager' which contains (composition) a list of all task instances.
//	4. The task class is the instance of a task, parsing, printing, graphing, and other functions as required.
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

// Task class
class Task
{
	std::string taskName, taskSlots, taskPass, taskFail;
public:
	Task(){

	}
	Task(vector<std::string> line)
	{
      int size = line.size();

      int index = size == 3 ? size + 1 : size == 2 ? size + 2 : size == 1 ? size + 3 : size;
      
      switch (index)
      {
      case 4:
        if (validTaskName(line[index - 4]))
          taskName = line[index - 4];
        else
          throw std::string("Expected fail task name, found '") + line[index - 4] + "'";
        if (size == 1) break;
      case 3:
        if (validTaskSlots(line[index - 3]))
          taskSlots = line[index - 3];
        else
          throw std::string("Expected fail task slots, found '") + line[index - 3] + "'";
        if (size == 2) break;
      case 2:
        if (validTaskName(line[index - 2]))
          taskPass = line[index - 2];
        else
          throw std::string("Expected fail task name, found '") + line[index - 2] + "'";
        if (size == 3) break;
      case 1:
        if (validTaskName(line[index - 1]))
          taskFail = line[index - 1];
        else
          throw std::string("Expected fail task name, found '") + line[index - 1] + "'";
        break;
      default:
        break;
        throw std::string("Expected 1, 2, 3, 4 fields, found ") + to_string(line.size());
      }
	}
	void print()
	{
		std::cout << "name="  << taskName << "";
		std::cout << "slots=" << taskSlots << "";
		std::cout << "pass="  << taskPass << "";
		std::cout << "fail="  << taskFail << "";
		std::cout << std::endl;
	}

	void graph(fstream& gv)
	{
		if (! taskPass.empty())
		{
			gv << '"' << taskName << '"';
			gv << "->";
			gv << '"' << taskPass << '"';
			gv << " [color=green]";

			gv << ";\n";
		}

		if (!taskFail.empty())
		{
			gv << '"' << taskName << '"';
			gv << "->";
			gv << '"' << taskFail << '"';
			gv << " [color=red]";
			gv << ";\n";
		}

		if (taskPass.empty() && taskFail.empty())
		{
			gv << '"' << taskName << '"';
      gv << " [shape=box]";
			gv << ";\n";
		}
	}
};

// Task Manager Class
class TaskManager
{
	vector< Task > taskList;
public:
	TaskManager(vector<vector<std::string> > & csvDataTask)
	{
		for (auto& line : csvDataTask)
		{
			try {
				taskList.push_back(std::move(line));
			}
			catch (std::string& e)
			{
				std::cerr << "TaskManager::TaskManager(vector<vector<std::string> > & csvDataTask)" << e << std::endl;

			}
		}
	}

	void print()
	{

		for (auto& task : taskList)
			task.print();
	}

	void graph(std::string& f)
	{
		fstream gv(f + ".gv", std::ios::out | std::ios::trunc);
		if (gv.is_open())
		{
			gv << "digraph taskGraph {\n";
			for (auto& task : taskList)
				task.graph(gv);

			gv << "}\n";
			gv.close();

			std::string cmd = "dot";
			cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			std::cout << "Running ->" + cmd << "\n";
			system(cmd.c_str());
		}

	}

};

/*
int main(int argc, char* argv[])
{
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filename = argv[1];
	char   delimiter = argv[2][0];

	try {
		vector< vector<string> > csvDataTask;
		csvRead(filename, delimiter, csvDataTask);
		//csvPrint(csvDataTask);

		TaskManager tm(csvDataTask);
		tm.print();
		tm.graph(filename);

	}
	catch (const string& e) {
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}

}
*/