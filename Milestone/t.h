#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

class Task
{
	std::string taskName, taskSlots="1", taskPass, taskFail;
public:


	//std::name() { return taskName; }
	//std::slots() { return taskName; }
	//std::pass() { return taskName; }
	//std::fail() { return taskName; }

	std::string& name() { return taskName; }
	std::string& slots() { return taskName; }
	std::string& pass() { return taskName; }
	std::string& fail() { return taskName; }

	Task();
	Task(vector<std::string> line);
	void print();
	void graph(fstream& gv);
};

class TaskManager
{
	vector< Task > taskList;
public:
	size_t count() { return taskList.size(); }
	Task& task(size_t t) { return taskList[t]; }
	//TaskManager();
	TaskManager(vector<vector<std::string> > & csvDataTask);
	void print();
	void graph(std::string& f);

	Task* find(std::string t);
	bool validate();
};
