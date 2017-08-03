#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "i.h"
#include "o.h"
#include "t.h"
#include "util.h"
#include "machine.h"

using namespace std;

class Factory {

	vector<Machine> machineList;
public:
	Factory()
	{


	}
	Factory(ItemManager& im, OrderManager& om, TaskManager& tm)
	{
		// STEP1. Create the factory
		// crete a machine from each task

		for (size_t m = 0; m < tm.count(); m++)
		{
			machineList.push_back(Machine(tm.task(m)));

		}
		for (auto& m : machineList)
			cout << "'" << m.name() << "'";

		cout << "\n";


		// 2. find source code
		auto findMachine = [&](string name) -> Machine* {

			for (size_t m = 0; m < machineList.size(); m++)
			{
				if (machineList[m].name() == name)
				{
					return &machineList[m];
				}
				return nullptr;

			}
		};
		


		for (auto& m : machineList)
		{
			string  pass = m.pass();
			if (!pass.empty())
			{
				findMachine(pass) -> incIncomming();
			}
			string fail = m.fail();
			if (!fail.empty())
			{
				findMachine(fail)->incIncomming();

			}
		}

		for (auto& m : machineList) {
			cout << "'" << m.name() << "'";
			if (m.isSink()) cout << " is a SINK";
			if (m.isSource()) cout << " is a SOURCE";
			cout << "\n";
		}
		int sourceNode = -1;
		for (size_t m = 0; m < machineList.size(); m++)
		{
			if (machineList[m].isSource() && machineList[m].isSink())
				continue; // ignore singletone nodes
			if (machineList[m].isSource())
			{
				if (sourceNode == -1)
				{
					sourceNode = m;
				}
				else
				{
					throw string("Multi source nodes, node ")
						+ to_string(sourceNode) + " and "
						+ to_string(m) +
						+"FIX DATA AND RESOURCE!!!";
				}
			}

		}
		cout << "sourceNode is " << sourceNode << "\n";
		if (sourceNode == -1)
			throw string("No source node FIX TASK AND RESUBMIT!!!");

		// STEP3. Add jobs to sourceNode machine's job queue
		for (size_t o = 0; o < om.count(); o++)

		{
			machineList[sourceNode].addJob(Job(om.order(o)));
		}

		for (auto& m : machineList) {
			if (m.jobSize())
				cout << " has " << m.jobSize() << " jobs in its jobQ";
			cout << "\n";
		}

		// classify all machie
		for (auto& m : machineList) {
			m.Classify(im);
		}

		// Step4. time loop
		int time = 0;

		while (true) { // time loop

			bool bAllDone = true;
			for (auto& m : machineList) {
				if (m.jobSize())
				{
					bAllDone = false;
					break;
				}
			}
			if (bAllDone) {
				cout << "All done, exiting time loop\n";
				break; // exit time loop
			}

			for (auto& m : machineList) { // machine loop
				// if jobQ is empty for this machine, nothing to do
				if (m.jobSize() == 0)
				{

					continue; // nothing for this machine to do

				}

				Job job = m.getJob();

				cout << "job" << job.customer() << "/" << job.product() << " is set machine " << m.name() << "\n";



				if (m.isSink()) {
					// if job not complete, move it to the source node
					if ( job.jobComplete())
					{
						cout << "job" << job.customer() << "/" << job.product() << " terminated machine " << m.name() << "\n";
					}
					else { // send it 
						cout << "job" << job.customer() << "/" << job.product() << " terminated machine " << m.name() << "\n";
						cout << "job is  not complete. re-routing back to source node" << sourceNode << "\n";

						machineList[sourceNode].addJob(move(job));
					}
					continue;
				}



				bool bDidSomething = false;
				// are we an installer?
				if (m.getInstaller()) {
					for (size_t i = 0; i < job.count(); i++) {
						if (job.getInstalled(i))
							continue; // 
						string itemName = job.item(i); // say, 'I7'
						string installer = im.find(itemName) -> installer(); // say, 'INSTALL CPU'

						if (m.name() == installer) {

							// install the item
							job.setInstalled(i, true);
							time++;
							bDidSomething = true;
							break;
						}
					}
				}

				// are we a remover?
				if (m.getRemover()) {
					for (int i = job.count(); i >= 0; i--) { // remove the last 'I7', not the first 'I7'
						if (!job.getInstalled(i))
							continue; // 
						string itemName = job.item(i); // say, 'I7'

						string remover = im.find(itemName) -> remover(); // say, 'REMOVE CPU'

						if (m.name() == remover) {

							// remove the item
							job.setInstalled(i, true);
							time++;
							bDidSomething = true;
							break;
						}


					}
				}

				auto movePass = [&] {
					string pass = m.pass();
					for (auto & m2 : machineList) { // machine loop
						if (m2.name() == pass) {

							m.addJob(move(job));
							break;
						}

					}
				};


				auto moveFail = [&] {
					string fail = m.fail();
					for (auto & m2 : machineList) { // machine loop
						if (m2.name() == fail) {

							m.addJob(move(job));
							break;
						}

					}
				};


				if (!bDidSomething) {
					movePass(); // move 'job' to pass
					continue; // next machine in machine loop
				}

				if (m.fail().empty()) {
					movePass(); // move 'job' to pass
					continue; // nextmachine in machine loop


					if (rand() & 1) { // add passed (1), even failed (0) 
						movePass(); // move 'job' to pass
					}
					else {
						moveFail(); // move 'job' to fail

					}
				}

			} // machine loop

		} // time loop
	}
};
int main(int argc, char* argv[])
{
	// 
	// 
	argc = 5;
	argv[0] = "M1";
	argv[1] = "WorkingItem.dat";
	argv[2] = "WorkingOrder.dat";
	argv[3] = "WorkingTask.dat";
	argv[4] = ",";


	if (argc != 5) {
		cerr << "Usage: " << argv[0] << " csv-file csv-delimiter\n";
		return 1;
	}

	string filenameItem = argv[1];
	string filenameOrder = argv[2];
	string filenameTask = argv[3];
	char   delimiter = argv[4][0];

	try
	{
		vector< vector<string> > csvDataTask;
		vector< vector<string> > csvDataOrder;
		vector< vector<string> > csvDataItem;
		csvRead(filenameTask, delimiter, csvDataTask);
		csvRead(filenameOrder, delimiter, csvDataOrder);
		csvRead(filenameItem, delimiter, csvDataItem);
		//csvPrint(csvDataTask);

		ItemManager im(csvDataItem);
		im.print();
		im.graph(filenameItem);

		OrderManager om(csvDataOrder);
		om.print();
		om.graph(filenameOrder);


		TaskManager tm(csvDataTask);
		tm.print();
		tm.graph(filenameTask);


		if (im.validate(tm) && om.validate(im) && tm.validate())
		{
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			cout << "Data has referental integraty. GOOD TO GO.\n";
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";

		}
		else
		{
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			cerr << "Data has referental integraty Problem.\n";
			cout << "++++++++++++++++++++++++++++++++++++++++++\n";
			throw string("Data has refeential integrity problem. FIX AND RE-SUBMIT!!!");
		}

		Factory f(im, om, tm);

		//im.validate(tm);
		//om.validate(im);
		//tm.validate();

	}
	catch (const string& e)
	{
		cerr << "It threw! -->" << e << "\n";
		return 2;
	}
}


