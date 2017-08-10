// OOP345 Milestone 4: Assembly Line
// File t.cpp
// Version 1.0
// Date 2017-08-04
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  splitting (code factoring) the task.cpp files into t.h/t.cpp files
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
#include "t.h"
#include "util.h"

	Task::Task(){

	}
	Task::Task(vector<std::string> line)
	{
      size_t size = line.size();

      size_t index = size == 3 ? size + 1 : size == 2 ? size + 2 : size == 1 ? size + 3 : size;
      
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
	void Task::print()
	{
		std::cout << "name="  << taskName << ", ";
		std::cout << "slots=" << taskSlots << ", ";
		std::cout << "pass="  << taskPass << ", ";
		std::cout << "fail="  << taskFail << "\n";
		std::cout << std::endl;
	}

	void Task::graph(fstream& gv)
	{
		if (! taskPass.empty())
		{
			gv << '"' << taskName << '"';
			gv << " -> ";
			gv << '"' << taskPass << '"';
			gv << " [color=green]";

			gv << ";\n";
		}

		if (!taskFail.empty())
		{
			gv << '"' << taskName << '"';
			gv << " -> ";
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



	TaskManager::TaskManager(vector<vector<std::string> > & csvDataTask)
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

	void TaskManager::print()
	{

		for (auto& task : taskList)
			task.print();
	}

	void TaskManager::graph(std::string& f)
	{
		fstream gv(f + ".gv", std::ios::out | std::ios::trunc);
		if (gv.is_open())
		{
			gv << "digraph taskGraph {\n";
			for (auto& task : taskList)
				task.graph(gv);

			gv << "}\n";
			gv.close();

			//std::string cmd = "dot";
			//cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";

			std::string cmd = "C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe";
			cmd += "  -Tpng " + f + ".gv" + " > " + f + ".gv.png";
			std::cout << "Running ->" + cmd << "\n";
			system(cmd.c_str());
		}

	}

	// find task name
	Task* TaskManager::find(std::string t)
	{
		for (size_t i = 0; i < taskList.size(); i++)
		{

			//std::cout << "test:::::::::-->" << taskList[i].name() << "<--, -->" << t << "<-- " << (taskList[i].name() == t) << std::endl;
			if (taskList[i].name() == t)
				return &taskList[i];
		}
		return nullptr;
	}
	// 
	bool TaskManager::validate()
	{
		int errors = 0;
		for (auto& task : taskList)
		{
			std::string pass = task.pass();
			if (!pass.empty() && find(pass) == nullptr)
			{
				errors++;
				std::cerr << "[" << __FILE__ << "]\n\tCannot find pass [" << pass << "]\n";
			}
			std::string fail = task.fail();
			if (!fail.empty() && find(fail) == nullptr)
			{
				errors++;
				std::cerr << "[" << __FILE__ << "]\n\tCannot find fail [" << fail << "]\n";
			}
		}
		//return errors === 0;
		return errors == 0;
	}
