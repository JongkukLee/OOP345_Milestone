#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

class Task
{
	std::string taskName, taskSlots="1", taskPass, taskFail;
public:
	Task(){


	}
	Task(vector<std::string> line)
	{
		switch (line.size())
		{
		case 4:
			if(validTaskName(line[3]))
				taskFail = line[3];
			else
				throw std::string("Expected fail task name, found '") + line[3] + "'";
		case 3:
			if (validTaskSlots(line[2]))
				taskPass = line[2];
			else
				throw std::string("Expected fail task slots, found '") + line[2] + "'";
		case 2:
			if (validTaskName(line[1]))
				taskSlots = line[1];
			else
				throw std::string("Expected fail task name, found '") + line[1] + "'";
		case 1:
			if (validTaskName(line[0]))
				taskName = line[0];
			else
				throw std::string("Expected fail task name, found '") + line[0] + "'";
			break;
			throw std::string("Expected 1, 2, 3, 4 fields, found ") + to_string(line.size());
		default:
			break;
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
			gv << "[color==green]";

			gv << ";\n";
		}

		if (!taskFail.empty())
		{
			gv << '"' << taskName << '"';
			gv << "->";
			gv << '"' << taskFail << '"';
			gv << "[color==red]";
			gv << ";\n";
		}

		if (taskPass.empty() && taskFail.empty())
		{
			gv << '"' << taskName << '"';
			gv << ";\n";
		}
	}
};

class TaskManager
{
	vector< Task > taskList;
public:
	TaskManager(vector<vector<std::string> > & csvDataTask)
	{
		for (auto& line : csvDataTask)
		{
			try {
				taskList.push_back(std::move(Task(line)));
			}
			catch (std::string& e)
			{
				std::cerr << e << std::endl;

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
			gv << "digraph taskGrap {\n";
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

	try {
		vector< vector<string> > csvDataTask;
		csvRead(filename, delimiter, csvDataTask);
		csvPrint(csvDataTask);

		TaskManager tm(csvDataTask);
	}
	catch (const string& e) {
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}

}
