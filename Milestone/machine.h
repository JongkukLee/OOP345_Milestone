#pragma once
#include <queue>
#include "t.h"
#include "job.h"

class Machine : public Task {
	int incomming = 0; // number of incoming edges to this node
	std::queue<Job> jobQ;
public:
	void incIncomming() { incomming++; }
	bool isSink() { return pass().empty() && fail().empty(); }//NOTE: if pass is empty(), fail must be empty
	bool isSource() { return incomming == 0;  }

	void addJob(Job&& j) {
		jobQ.push(j);

	}
	size_t jobSize() { return jobQ.size(); }

	Machine()
	{
	}

	Machine(Task& t) : Task(t)
	{



	}

};