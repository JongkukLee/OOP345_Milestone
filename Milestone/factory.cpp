// OOP345 Milestone 5: Factory Simulation
// File factory.h
// Version 1.0
// Date 2017-08-10
// Author Jongkuk Lee ( jlee465@myseneca.ca, 127730158 )
// Description
//  represent the assembly line of factory
//  load the machine
//  intall the items that are order by customers
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
#include "i.h"
#include "o.h"
#include "t.h"
#include "util.h"
#include "machine.h"
#define VERBOSE 0
using namespace std;

class Factory 
{
  // member data to load the machine in the assembly line
  vector<Machine> machineList;
public:
  // defaulat constructor
  Factory()
  {

  }
  Factory(ItemManager& im, OrderManager& om, TaskManager& tm)
  {
    // STEP1. Create the factory /////////////////////////////////////////////
    // create a factory consisting of a network of machines, one machine per task.
    // A machine has an input job queue which is a queue of jobs waiting to be
    // processed by the machine. The item data file entries state whether a machine
    // is an installer or remover.
    for (size_t m = 0; m < tm.count(); m++) // count() can get the number of task
    {
      // After the object is created as a parameter for a push_back function, 
      // it has been copied in a push_back function again.After parameters were 
      // detoryed when they leave a push_back function, the object has been 
      // destroyed.We just want to add only one object in std::vector 
      // but the object has been copied and destoyed twice.
      // C++11 compiler finds out the constructor that can get value as a parameter 
      // without creating object among constructors and create it its own way.
      // Besides, it is even more efficient that the construtor and destructor 
      // were called just once because the compiler creates and add an object
      // without copy an object and moving it. Its one way is to use 'emplace_back' function

      //machineList.push_back(Machine(tm.task(m)));
      machineList.emplace_back(tm.task(m));
    }
    // display the all machines
    for (auto& m : machineList)
      cout << "'" << m.name() << "'\n";

    // 2. STEP2. Find the 'source' node for the machine network. //////////////

    // define the lambda function to find and return machine that 
    // matches with pass and fail node name 
    auto findMachine = [&](string name) -> Machine* 
    {

      for (size_t i = 0; i < machineList.size(); i++)
      {
        if (machineList[i].name() == name)
        {
          return &machineList[i];
        }
      }
      return nullptr;
    };

    // increase the incomming number of the matching machine
    // if incomming number is 0, the node is a source
    for (auto& m : machineList)
    {
      string pass = m.pass();
      if (!pass.empty())
      {
        findMachine(pass)->getIncIncommingCnt();
      }
      string fail = m.fail();
      if (!fail.empty())
      {
        findMachine(fail)->getIncIncommingCnt();
      }
    }

    // display the machine to comfirm if it is a source or sink node
    for (auto& m : machineList)
    {
      cout << "'" << m.name() << "'";
      if (m.isSink()) cout << " is a SINK";
      if (m.isSource()) cout << " is a SOURCE";
      cout << "\n";
    }

    // assign the index of the source node
    int sourceNode = -1;
    for (size_t i = 0; i < machineList.size(); i++)
    {
      // if singletone nodes (without incomming or outcomming edges), 
      // ignore and keep looping until finding a source node
      if (machineList[i].isSource() && machineList[i].isSink())
        continue;

      // if it is a source node
      if (machineList[i].isSource())
      {
        // assign the index value of the source node
        if (sourceNode == -1)
        {
          sourceNode = i;
        }
        // if more than one source nodes are found
        else
        {
          throw string("Multi source nodes, node ")
            + to_string(sourceNode) + " and "
            + to_string(i) +
            +"FIX DATA AND RESOURCE!!!";
        }
      }
    }
    // display the index of the source node
    cout << "sourceNode is " << sourceNode << "\n";

    // if it cannot find any source node, need to check data file 
    if (sourceNode == -1)
      throw string("No source node FIX TASK AND RESUBMIT!!!");

    // STEP3. Load jobs to sourceNode machine's Job queue
    // Each order is a job. A job has a data element that 
    // flags whether an item has been installed (see the order (o.h) file).
    // Load all the orders into the input queue for the 'source' node.
    for (size_t o = 0; o < om.count(); o++) // count() can get the number of items in an order
    {
      machineList[sourceNode].addJob(Job(om.order(o)));
    }

    // display the number of job (customer order) in queue of the source node
    for (auto& m : machineList) 
    {
      cout << "'" << m.name() << "'";
      if (m.getJobSize())
        cout << " has " << m.getJobSize() << " jobs in its jobQ";
      cout << "\n";
    }

    // set true or false in all machines according 
    // to what the installer flag or a remover flag is
    for (auto& m : machineList) 
    {
      m.classifyMachine(im);
    }

    // Step4. time loop
    int time = 0;

    while (true) { // loop untile completing all jobs

                   // display the loop time 
      cout << "TOP OF TIME LOOP time=" << time << "\n";

      // if all jobs are completed, the loop will be finished
      // else keep looping until completing all jobs
      bool bAllDone = true;
      for (auto& m : machineList) {
        if (m.getJobSize())
        {
          bAllDone = false;
          break;
        }
      }
      // if all jobs are completed, stop the loop completly
      if (bAllDone) {
        cout << "All done, exiting time loop\n";
        break; // exit time loop
      }

      // over all machines
      for (auto& m : machineList) { // machine loop

        // loop until meeting the source node that have at least one job
        if (m.getJobSize() == 0)
        {
          continue; // if nothing for this machine to do, go to next machine
        }

        // when finding the job (customer order)
        Job job = m.getJob();

        // display the information of product installed in the machine
        cout << "job " << job.customer() << "/" << job.product() << " is set machine " << m.name() << "\n";

        // if sink and the job is completed
        // mark job completed and ship it
        if (m.isSink()) {
          // // if job complete, it is finished, all done, game over, exists, the system
          if (job.isJobComplete())
          {
            cout << "job " << job.customer() << "/" << job.product() << " terminated machine " << m.name() << "\n";
          }
          // job not complete, move it to the source node
          else { // send it back to the source node
            cout << "job " << job.customer() << "/" << job.product() << " terminated machine " << m.name() << "\n";
            cout << "job is  not complete. re-routing back to source node" << sourceNode << "(" << machineList[sourceNode].name() << ") \n";

            // move the job to the source node
            machineList[sourceNode].addJob(move(job));
          }
          continue; // go to next machine
        }

        // check that this machine did install or remove
        bool bDidSomething = false;
        // are we an installer?
        // if this machine is installer, flags true in the product that is not installed 
        if (m.getInstaller()) { // already set in Classify(ItemManager& im) function
          for (size_t i = 0; i < job.count(); i++) {
            if (job.isInstalled(i))
              continue; // 

            // set product name
            string itemName = job.item(i); // say, 'I7'
            // set machine name
            string installer = im.find(itemName)->installer(); // say, 'INSTALL CPU'

            // set true in intalled flag
            if (m.name() == installer) {

              // install the item
              job.setInstalledFlag(i, true);
              time++;
              bDidSomething = true;
              break;
            }
          }
        }

        // are we a remover?
        // if this machine is remover, flags true in the product that is not removered 
        if (m.getRemover()) {
          for (int i = job.count() - 1; i >= 0; i--) { // remove the last 'I7', not the first 'I7'
            if (!job.isInstalled(i))
              continue; // 

            // set product name
            string itemName = job.item(i); // say, 'I7'
            // set machine name
            string remover = im.find(itemName)->remover(); // say, 'REMOVE CPU'

            // set false in intalled flag
            if (m.name() == remover) {

              // remove the item
              job.setInstalledFlag(i, false);
              time++;
              bDidSomething = true;
              break;
            }
          }
        }

        // move to the next machine that matches with pass node name
        // add the job to the passed machine input queue
        auto movePass = [&] 
        {
          string pass = m.pass();
          for (auto & m2 : machineList) 
          { // machine loop
            if (m2.name() == pass) {

              m2.addJob(move(job));
              break;
            }
          }
        };

        // move to the next machine that matches with fail node name
        // add the job to the passed machine input queue
        auto moveFail = [&] 
        {
          string fail = m.fail();
          for (auto & m2 : machineList) 
          { // machine loop
            if (m2.name() == fail) {
              m2.addJob(move(job));
              break;
            }
          }
        };

        // if there was no work in this machine
        if (!bDidSomething) {
          movePass(); // move 'job' to the pass node
          continue; // next machine in machine loop
        }

        // If the machine has only a 'passed'
        if (m.fail().empty()) {
          movePass(); // move 'job' to the pass node
          continue; // nextmachine in machine loop
        }

        // inspector
        // flip a coin: calculate a random number to 'inspect' the job.
        // if the inspection failed
        if (rand() & 1) { // add passed (1), even failed (0) 
          movePass(); // move 'job' to pass
        }
        else {
          moveFail(); // move 'job' to fail
        }
      } // machine loop
    } // time loop
  }
};

// Milestone 5 testing file
int main(int argc, char* argv[])
{
  // 
  // 
  argc = 5;
  argv[0] = "M1";
  argv[1] = "WorkingItem.dat";
  argv[2] = "WorkingOrder.dat";
  argv[3] = "WorkingTask.dat";
  argv[4] = "|";

  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
    return 1;
  }
  // set CVS file names
  string filenameItem = argv[1];
  string filenameOrder = argv[2];
  string filenameTask = argv[3];
  char   delimiter = argv[4][0];

  try
  {
    // load the data from CVS data file
    vector< vector<string> > csvDataTask;
    vector< vector<string> > csvDataOrder;
    vector< vector<string> > csvDataItem;
    csvRead(filenameTask, delimiter, csvDataTask);
    csvRead(filenameOrder, delimiter, csvDataOrder);
    csvRead(filenameItem, delimiter, csvDataItem);

    // load, print and draw the graph of item data file
    ItemManager im(csvDataItem);
    im.print();
    im.graph(filenameItem);
    // load, print and draw the graph of customer order data file
    OrderManager om(csvDataOrder);
    om.print();
    om.graph(filenameOrder);
    // load, print and draw the graph of task data file
    TaskManager tm(csvDataTask);
    tm.print();
    tm.graph(filenameTask);

    if (im.validate(tm) && om.validate(im) && tm.validate())
    {
      cout << "++++++++++++++++++++++++++++++++++++++++++\n";
      cout << "Data has referental integraty. GOOD TO GO.\n";
      cout << "++++++++++++++++++++++++++++++++++++++++++\n";
      Factory f(im, om, tm);
    }
    else
    {
      cout << "++++++++++++++++++++++++++++++++++++++++++\n";
      cerr << "Data has referental integraty Problem.\n";
      cout << "++++++++++++++++++++++++++++++++++++++++++\n";
      throw string("Data has refeential integrity problem. FIX AND RE-SUBMIT!!!");
    }
  }
  // exception occurs
  catch (const string& e)
  {
    cerr << "It threw! -->" << e << "\n";
    return 2;
  }
}
