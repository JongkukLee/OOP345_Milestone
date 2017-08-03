#pragma once
#include "o.h"

class Job : public Order {
	std::vector<bool> installed;
public:

	bool getInstalled(size_t i) { return installed[i]; }
	void setInstalled(size_t i, bool v) { installed[i] == v; } //<-- I don't know
	
	bool jobComplete()
	{
		for (size_t i = 0; i < count(); i++)
			if (installed[i] == false)
				return false;
		return true;

	}
	
	Job()
	{

	}

	Job(Order& o) : Order(o)
	{
		for (size_t i = 0; i < count(); i++)
			installed.push_back(false);

	}




};