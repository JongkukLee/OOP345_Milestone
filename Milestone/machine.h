#pragma once
#include <queue>
#include "t.h"
#include "job.h"

class Machine : public Task {
  int incomming = 0; // number of incoming edges to this node
  std::queue<Job> jobQ;
  bool bInstaller = false;
  bool bRemover = false;
public:
  void incIncomming() { incomming++; }
  bool isSink() { return pass().empty() && fail().empty(); }//NOTE: if pass is empty(), fail must be empty
  bool isSource() { return incomming == 0; }

  void addJob(Job&& j) { jobQ.push(j); }
  Job getJob() { Job job = jobQ.front(); jobQ.pop(); return job; }
  size_t jobSize() { return jobQ.size(); }

  bool getInstaller() { return bInstaller; }
  bool getRemover() { return bRemover; }


  void Classify(ItemManager& im)
  {
    for (size_t i = 0; i < im.count(); i++) {
      if (name() == im.item(i).installer()) bInstaller = true;
      if (name() == im.item(i).remover()) bRemover = true;
    }

//      cout << "Machine Name: " << name() << ", are we an installer?: " << bInstaller
//        << " or remover?: " << bRemover << "\n";

    if (bInstaller && bRemover)
      throw name() + " is both an installer and a remover. Fix item file data and re-submit1!";


  }



  Machine()
  {
  }

  Machine(Task& t) : Task(t)
  {



  }

};