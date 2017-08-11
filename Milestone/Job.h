// OOP345 Milestone 5: Factory Simulation
// File job.h
// Version 1.0
// Date 2017-08-10
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//   the job that will be installed on the machine
//  derive from Order class
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
//
///////////////////////////////////////////////////////////
#ifndef JOB_H
#define JOB_H

#include "o.h"

class Job : public Order {
  // flags whether product is installed or not
  std::vector<bool> installedPerItem;
public:
  // check whether the item of the job is installed or not 
  bool isInstalled(size_t i) { return installedPerItem[i]; }
  // flags true in the product that is not installed if the 
  void setInstalledFlag(size_t i, bool v) { installedPerItem[i] = v; }
  // check whether all job completed or not
  bool isJobComplete()
  {
    for (size_t i = 0; i < count(); i++)
      if (installedPerItem[i] == false)
        return false;
    return true;
  }
  // defualt constructor
  Job()
  {

  }

  // one paremeter constructor
  Job(Order& o) : Order(o)
  {
    // initialize all order item in false
    for (size_t i = 0; i < count(); i++)
      installedPerItem.push_back(false);
  }
};
#endif