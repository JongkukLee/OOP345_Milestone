// OOP345 Milestone 4: Assembly Line
// File t.h
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
#ifndef T_H
#define T_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

class Task
{
	std::string taskName, taskSlots, taskPass, taskFail;
public:


	//std::name() { return taskName; }
	//std::slots() { return taskName; }
	//std::pass() { return taskName; }
	//std::fail() { return taskName; }

	std::string& name() { return taskName; }
	std::string& slots() { return taskSlots; }
	std::string& pass() { return taskPass; }
	std::string& fail() { return taskFail; }

	Task();
	Task(vector<std::string> line);
	void print();
	void graph(fstream& gv);
  void setName(std::string name) { taskName = name; }
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
#endif
