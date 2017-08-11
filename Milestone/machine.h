// OOP345 Milestone 5: Factory Simulation
// File machine.h
// Version 1.0
// Date 2017-08-10
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  represent the machine in the assembly lines of factory
//  derive from Task class
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef MACHINE_H
#define MACHINE_H

#include <queue>
#include "t.h"
#include "job.h"

class Machine : public Task {
  int incommingCnt;// number of incoming edges to this node
  std::queue<Job> jobQ; // customer order queue
  bool bInstaller; // flag about whether the machine is an installer or not
  bool bRemover;   // flag about whether the machine is a remover or not
public:
  // default contructor
  // set the safe state
  Machine()
  {
    incommingCnt = 0;
    bInstaller = false;
    bRemover = false;
  }
  // one paramater constructor
  // set the safe state
  Machine(Task& t) : Task(t)
  {
    incommingCnt = 0;
    bInstaller = false;
    bRemover = false;
  }
  // get the number of the incomming edges of the node 
  void getIncIncommingCnt() { incommingCnt++; }
  // check whether it is a sink or not
  bool isSink() { return pass().empty() && fail().empty(); }//NOTE: if pass is empty(), fail must be empty
  // check whether it is a source or not
  bool isSource() { return incommingCnt == 0; }
  // add the job (customer order) to machine
  void addJob(Job&& j) { jobQ.push(j); }
  // get the job (customer order) from a machine
  Job getJob() { Job job = jobQ.front(); jobQ.pop(); return job; }
  // get the the number of job 
  size_t getJobSize() { return jobQ.size(); }
  // get whether the machine is an installer or not
  bool getInstaller() { return bInstaller; }
  // get whether the machine is an remover or not
  bool getRemover() { return bRemover; }

  // set true or false in all machines 
  // according to what the installer flag or a remover flag is
  void classifyMachine(ItemManager& im)
  {
    for (size_t i = 0; i < im.count(); i++) {
      if (name() == im.item(i).installer()) bInstaller = true;
      if (name() == im.item(i).remover()) bRemover = true;
    }
    // it is error
    if (bInstaller && bRemover)
      throw name() + " is both an installer and a remover. Fix item file data and re-submit1!";

  }

};
#endif
